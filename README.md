# CS2 TriggerBot

[![GitHub license](https://img.shields.io/badge/license-AGPLv3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)
![Compatibility](https://img.shields.io/badge/CS2_Version-2024.02.1-brightgreen)

# The most basic TriggerBot

```mermaid
graph TD
    A[GetEntityList] --> B{entitylistbase?}
    B -->|Null| C[安全终止]
    B -->|Valid| D{localplayer_pawn}
    D -->|Invalid| C
    D -->|Valid| E{localplayer_team?}
    E -->|Friendly| C
    E -->|Enemy| F{localplayer_health?}
    F -->|≤0| C
    F -->|>0| G{entity_Maxhealth ≤80}
    G -->|False| C
    G -->|True| H[shoot]
