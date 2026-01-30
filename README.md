# Pokemon Battle Game

一个类似宝可梦的精灵对战游戏，使用 C++ 实现核心战斗逻辑，使用 Python 脚本定义技能效果。

A Pokemon-like sprite battle game with C++ core battle logic and Python scripts for skill effects.

## Features

- **核心战斗系统 (Core Battle System)**: 完整的回合制战斗逻辑
- **Python 技能集成 (Python Skill Integration)**: 使用 Python 脚本定义精灵技能，方便扩展复杂效果
- **可扩展架构 (Extensible Architecture)**: 模块化设计，易于添加新功能
- **无 UI 设计 (No UI)**: 专注于核心逻辑，便于后期集成任何 UI 框架

## Architecture

### C++ Core Components

- **Pokemon**: 精灵类，包含属性（HP, Attack, Defense, Speed）和技能
- **Move**: 技能类，支持从 Python 脚本加载效果函数
- **Battle**: 战斗类，管理回合制战斗流程
- **PythonSkillLoader**: Python 集成层，加载和执行 Python 技能脚本

### Python Skill Scripts

技能脚本位于 `scripts/` 目录，每个技能定义一个 `calculate_damage` 函数：

```python
def calculate_damage(attacker, defender):
    """
    Args:
        attacker: dict with keys: name, current_hp, max_hp, attack, defense, speed
        defender: dict with keys: name, current_hp, max_hp, attack, defense, speed
    Returns:
        int: damage amount
    """
    # Your skill logic here
    damage = calculate_your_damage(attacker, defender)
    return damage
```

## Building

### Requirements

- C++14 compatible compiler (g++ 7+, clang 5+, MSVC 2017+)
- Python 3.x development headers
- CMake 3.10+

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build .

# Run
./pokemon_battle
```

## Usage Example

```cpp
// Create Pokemon
auto pikachu = std::make_shared<Pokemon>("Pikachu", 100, 55, 40, 90);
auto charmander = std::make_shared<Pokemon>("Charmander", 110, 52, 43, 65);

// Create moves with Python scripts
auto thunderbolt = std::make_shared<Move>("Thunderbolt", "thunderbolt.py", 90, 100, "Electric");

// Load Python skill
auto skillFunc = PythonSkillLoader::loadSkill("thunderbolt", "calculate_damage");
thunderbolt->setEffectFunction(skillFunc);

// Add moves to Pokemon
pikachu->addMove(thunderbolt);
charmander->addMove(flamethrower);

// Start battle
Battle battle(pikachu, charmander);
auto winner = battle.start();
```

## Extending the System

### Adding New Pokemon

```cpp
auto newPokemon = std::make_shared<Pokemon>(
    "Name",      // Name
    100,         // Max HP
    50,          // Attack
    45,          // Defense
    70           // Speed
);
```

### Adding New Skills

1. Create a Python script in `scripts/` directory:

```python
# scripts/new_skill.py
def calculate_damage(attacker, defender):
    # Your custom logic
    base_power = 80
    damage = (attacker['attack'] * base_power) / defender['defense']
    return int(damage)
```

2. Create the move in C++ and load the script:

```cpp
auto newSkill = std::make_shared<Move>("NewSkill", "new_skill.py", 80, 100, "Type");
auto skillFunc = PythonSkillLoader::loadSkill("new_skill", "calculate_damage");
newSkill->setEffectFunction(skillFunc);
```

## Future Extensions

- 状态效果 (Status effects): 中毒、麻痹、睡眠等
- 属性克制 (Type effectiveness): 属性相克系统
- 多只精灵战斗 (Multi-Pokemon battles): 组队战斗
- AI 对手 (AI opponents): 智能对战策略
- 经验值和等级系统 (Experience and leveling)
- 物品系统 (Item system)
- UI 集成 (UI integration): 图形界面

## License

MIT License