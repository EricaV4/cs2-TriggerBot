# CS2 TriggerBot

[Cs2 Dumper](https://github.com/a2x/cs2-dumper)

# The most basic TriggerBot

If the game is updated, replace "client_dll.hpp" and "offsets.hpp"

```mermaid
graph TD
    A[GetEntityList] --> B{entitylistbase?}
    B -->|Null| C[continue]
    B -->|Valid| D{localplayer_pawn}
    D -->|Invalid| C
    D -->|Valid| E{localplayer_team?}
    E -->|Friendly| C
    E -->|Enemy| F{localplayer_health?}
    F -->|≤0| C
    F -->|>0| G{entity_Maxhealth ≤80}
    G -->|False| C
    G -->|True| H[shoot]
