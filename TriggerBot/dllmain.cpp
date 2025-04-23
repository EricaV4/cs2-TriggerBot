#include <Windows.h>
#include <iostream>
#include "client_dll.hpp"
#include "offsets.hpp"
#include "buttons.hpp"

uintptr_t GetBaseEntityFromHandle(uint32_t uHandle, uintptr_t client) {
	auto entListBase = *reinterpret_cast<std::uintptr_t*>(client + cs2_dumper::offsets::client_dll::dwEntityList);
	if (entListBase == 0) {
		return 0;
	}
	const int nIndex = uHandle & 0x7FFF;

	auto entitylistbase = *reinterpret_cast<std::uintptr_t*>(entListBase + 8 * (nIndex >> 9) + 16);
	if (entitylistbase == 0) {
		return 0;
	}

	return *reinterpret_cast<std::uintptr_t*>(entitylistbase + 0x78 * (nIndex & 0x1FF));
}

static DWORD Main(void*) {

	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);

	const auto client = reinterpret_cast<uintptr_t>(GetModuleHandle(L"client.dll"));

	while (1) {

		auto localplayer_pawn = *reinterpret_cast<uintptr_t*>(client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);

		if (!localplayer_pawn)
		{
			continue;
		}

		auto localplayer_team = *reinterpret_cast<uintptr_t*>(localplayer_pawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

		if (!localplayer_team)
		{
			continue;
		}
		
		auto localplayer_health = *reinterpret_cast<uintptr_t*>(localplayer_pawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);
		
		if (localplayer_health <= 0)
		{
			continue;
		}

		auto corsshair_entity_handle = *reinterpret_cast<uint32_t*>(localplayer_pawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex);

		if (corsshair_entity_handle != 0)
		{
			auto entity_pawn = GetBaseEntityFromHandle(corsshair_entity_handle, client);
			if (!entity_pawn)
				continue;

			auto entity_team = *reinterpret_cast<uintptr_t*>(entity_pawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

			if (!entity_team)
			{
				continue;
			}

			auto entity_health = *reinterpret_cast<uintptr_t*>(entity_pawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);

			if (entity_health <= 0)
			{
				continue;
			}

			auto entity_Maxhealth = *reinterpret_cast<uintptr_t*>(entity_pawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iMaxHealth);

			if (entity_Maxhealth <= 80)
			{
				continue;
			}

			if ((GetAsyncKeyState(VK_XBUTTON1) & 0x8000))//mouse4
			{
				auto set_force_attack = reinterpret_cast<int*>(client + cs2_dumper::buttons::attack);
				std::cout << "player_health" << localplayer_health << std::endl;
				std::cout << "entity_health" << entity_health << std::endl;
				Sleep(20);
				*set_force_attack = 65537;
				Sleep(20);
				*set_force_attack = 256;
				Sleep(40);
			}
		}
	}
	return 1;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)//cmd
{
	if (ul_reason_for_call == 1)
	{
		CreateThread(nullptr, 0, Main, NULL, 0, NULL);
	}

}
