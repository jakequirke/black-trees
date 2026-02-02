# GAME DESIGN DOCUMENT (SIMPLE MASTER VERSION)

## 1. HIGH-LEVEL OVERVIEW
Title: black trees
Author / Date: Jacob Quirke / 29/1/26

Elevator Pitch:
A boy wakes in a dark forest and finds his village empty—only black shadows remain. Using a mysterious healing power, he must confront shadow beasts and uncover the truth behind the village’s disappearance and the world’s decay.

Genre / Perspective / Art Style:
- Genre: RPG
- Perspective: Top-down
- Art Style: Pixel art similar to Chrono Trigger

Target Platforms:
PC / Mac (distributed via Steam)

Target Audience:
Fans of 90s JRPGs who are looking to return to the old style with a new twist.

Core Gameplay Loop:
1. Explore region
2. Discover puzzle and/or shadows
3. Heal shadow in battle / Solve puzzle
4. Recover memory
5. Unlock world progress

Unique Selling Point (USP):
The player does not attack - their power is to heal shadows rather than defeat them to unlock memories of how the world became what it is.

Must-Have Features:
1. Engaging healing/combat system that develops as you play to be constantly interesting throughout a playthrough.
2. A constant feeling of 'this is entertaining', 'I am engrossed'.
3. Tight story where every action moves the player forward.
4. Side quests always allow you to learn more about the story / world / player / characters. They are never fetch quests of padding to increase play time.
5. 

Estimated Scope:
- Vertical slice length:
- Full game length:
- Number of regions:
- Number of memories:


## 2. VERTICAL SLICE DEFINITION
Goal:
(Build the smallest complete experience proving the concept)

Vertical Slice Includes:
- One explorable region
- One place screen with a puzzle
- One shadow encounter
- One healing battle
- One memory reveal
- Save/load functionality

Success Criteria:
(Player can travel → explore → heal → unlock memory → save progress)

Files / Scenes Needed:
- Main scene:
- Region scene:
- Place scene:
- Battle UI scene:
- Dialogue / memory UI scene


## 3. COMBAT DESIGN (HEALING BATTLES)
Design Intent:
Battles are not to add time to gameplay. Every battle matters where in the middle and at the end something new is learned about the shadow who is turned back to normal or about the player character. It should be engaging and offer an alternative to typical battle systems. The player must manage healing the shadow, defending themselves and ensuring with a shadow's action they do not become completely corrupted.

Battle Type:
- Turn-based
- Party size: 1
- Enemy type: Shadow

Core Stats:
- Player MP:
- Shadow Corruption (0 = healed)
- Optional additional stats:

Healing Actions:
| ID | Name | MP Cost | Heal Amount | Notes |
|----|------|---------|-------------|-------|
|    |      |         |             |       |

Turn Flow:
Start → Player Turn → Choose Heal → Apply Heal → Resolve → Check Healed → End or Repeat

Win Condition:
(Shadow fully healed)

Loss / Failure Condition:
(If applicable)
1. Player becomes corrupted and turns to shadow.
2. If above occurs, player will be saved by their protector who guides them from the start. 

Battle UI Elements:
- Action list
- MP display
- Corruption bar
- Feedback text
- Memory reveal window

Progression Notes:
(How healing actions improve or expand over time)
- Start with single ability to heal
- Parry attacks and...
- Timed attacks - if perfect increase healing.
- Heal self of corruption from enemy
- Enemy never 'attacks' but corrupts the PC.
- Heal all enemies
- 


## 4. WORLD & REGION DESIGN
World Concept:
Twelve floating shards in an void space traversed through a white orb of light that initially helps the PC when they wake up. It grows from the PC's staff and consumes them to move to another shard.

World Map Structure:
- Regions count: 12 shards
- Travel method: Orb between shards. Walk across regions on each shard. Walk in each individual place.
- Locked / unlocked areas: Each shard follows a metroidvania concept wherein not all areas are available on first visit to a shard. After unlocking new abilities the player can return to defeat more challening bosses or pass through increasingly difficult puzzles.

Region Template:
- Region ID:
- Region Name:
- Biome:
- Key Landmarks:
  1.
  2.
  3.
- Shadows present:
- Place screens:
- Visual / mood notes:


## 5. PLACE SCREENS & PUZZLES
Place ID / Scene Name:

Purpose:
(Puzzle, lore, shadow encounter, etc.)

Puzzle Type:
(e.g. switches, memory clues, dialogue)

Key Objects:
- Object ID:
- Object ID:

Puzzle Solution Steps:
1.
2.
3.

Failure / Reset Rules:
(What happens if player leaves or fails)

Rewards:
- Memory ID:
- Other rewards:


## 6. MEMORY SYSTEM
Memory Purpose:
(Why memories matter narratively and mechanically)

Memory Types:
- Lore
- Character backstory
- World history
- Gameplay unlocks

Memory Data Fields:
- ID
- Title
- Text
- Region
- Shadow Source

Memory Presentation:
(Dialogue box, illustrated panel, audio, etc.)

Player Access:
(Where memories are stored and reviewed)


## 7. UI / UX & CONTROLS
Input Methods:
- Keyboard
- Gamepad
- Mouse (optional)

Core Controls:
- Move:
- Interact:
- Menu:
- Confirm / Cancel:

Battle UI Layout:
(Describe or sketch textually)

Dialogue / Memory UI:
(Text box placement, style, pacing)

Accessibility Considerations:
- Text size
- Color contrast
- Dialogue speed


## 8. TECHNICAL DESIGN
Engine:
Godot (version)

Language:
GDScript

Project Folder Structure:
/scenes
/scripts
/core
/entities
/ui
/assets
/data