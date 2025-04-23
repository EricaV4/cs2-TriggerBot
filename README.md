graph TD
    A[获取实体列表] --> B{entitylistbase?}
    B -->|No| C
    B -->|Yes| D{localplayer_pawn}
    D -->|No| C
    D -->|Yes| E{localplayer_team?}
    E -->|No| C
    E -->|Yes| F{localplayer_health?}
    F -->|No| C
    F -->|Yes| G{entity_Maxhealth <= 80}
    G -->|No| C
    G -->|Yes|[shoot]
