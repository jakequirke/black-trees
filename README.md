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

Base scenes needed:
- World map
- Region map (initial class extended to 12 region)
- Place (numerous states navigated by PC by exiting edges of screen)
- Battle
- Memory scene (duplicated from 'Place' with a different colour pallette. Maybe black and white?)

## 3. COMBAT DESIGN (HEALING BATTLES)
Design Intent:
Battles are not to add time to gameplay. Every battle matters where in the middle and at the end something new is learned about the shadow who is turned back to normal or about the player character. It should be engaging and offer an alternative to typical battle systems. The player must manage healing the shadow, defending themselves and ensuring with a shadow's action they do not become completely corrupted.

Battle Type:
- Turn-based
- Party size: 1
- Enemy type: Shadow (of various forms)

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
(Shadow fully healed / uncorrupted)

Loss / Failure Condition:
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
- Talk - player can decide to talk on every turn to learn more about the shadow / person inside
- Parry attacks and...
- Timed attacks - if perfect increase healing.
- Corruption purge - Heal self of corruption from enemy
- Purge overflow - overpurge converts excess corruption into a shared heal pool
- Pacifying mend - can delay an enemy's turn
- Enemy never 'attacks' but corrupts the PC.
- Sacrificial mend
- Manifest memory - show a shadow a related memory to them if you discover their identiy in a prior puzzle.
- Heal all enemies
- Corrupt self - make the ultimate sacrifice and take all the corruption from an enemy and give to self.


## 4. WORLD & REGION DESIGN
World Concept:
Twelve floating shards in an void space traversed through a white orb of light that initially helps the PC when they wake up. It grows from the PC's staff and consumes them to move to another shard.

World Map Structure:
- Regions count: 12 shards
- Travel method: Orb between shards. Walk across regions on each shard. Walk in each individual place.
- Locked / unlocked areas: Each shard follows a metroidvania concept wherein not all areas are available on first visit to a shard. After unlocking new abilities the player can return to defeat more challening bosses or pass through increasingly difficult puzzles.

## 4.1 REGIONS:
The Fanged Shard (Gæt) - will be the initial prototype area to perfect before continuing to the rest of the game.
- Region ID: R01
- Biome:
- Places:
  1. Village square
    1.1. Main square
    1.2. The Crooked Ox
    1.3. Reeves' home
    1.4. Homes of several villagers
  2. PC's home
  3. Jonas' home
  4. The edge of the wilds (forest of black trees)
  5. ____'s home (woman)
- Shadows present: PC's father, Mathias, Mathias' wife, PC's best friend (Mathias' son), Orl (innkeeper), Reeves, Couple, Jonas (final boss of area), creature in the whilds (optional boss who is the PC's mother).
- Puzzles / Investigation: each shadow has a connected item which is the only way to completely remove their corruption. If not used, the shadow will reveal a false memory and will return once disappeared after PC leaves and returns to same screen. It unlocks a new memory before revealing the final, true memory when mended.
PC can also discover notes related to the shadow. In battle, the player must figure out which information matches to the shadow. If they choose the wrong information then the PC will be damaged and the shadow will become stronger. The PC will have to use contextual clues on the shadow's location to figure out which information links to shadow. E.g. notebook found in the tavern reveals Reeves was incredibly lonely in her house. A lone shadow is found in the house. Another example: Axe belonging to executioner but is actually the item associated with Mathias who is the last person to be executed with the axe. It is the trauma associated with the item that is part of the reason they are a shadow. The same with any notes that are found.
- Visual / mood notes: Death Stranding (east). Iceland in summer


## 5. PUZZLES / INVESTIGATIONS
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
- Move: WASD / Arrow keys (directions on controller)
- Interact: Enter (X / A on controller)
- Menu: M (Triangle / Y on controller)
- Confirm / Cancel: X (O / B on controller)

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