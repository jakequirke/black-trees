# GAME DESIGN DOCUMENT (SIMPLE MASTER VERSION)

## 1. HIGH-LEVEL OVERVIEW
Title: black trees
Author / Date: Jacob Quirke / 29/1/26

Elevator Pitch:
A boy wakes in a dark forest alongside a mysterious white orb. Returning home, he finds his village empty — only black shadows remain. Carrying the orb in his staff, he travels between shards of memory, healing shadows and uncovering the truth behind the world's decay. The player does not fight. They witness, understand, and heal.

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
2. Collect items and notes belonging to shadows
3. Match items/notes to the correct shadow
4. Heal shadow in battle using matched information
5. Recover memory / world becomes lighter
6. Unlock world progress

Unique Selling Point (USP):
The player does not attack — their power is to heal shadows rather than defeat them. Healing requires understanding: matching fragments of a person's life to their shadow before the truth of their final moments can be revealed.

Must-Have Features:
1. Engaging healing/combat system that develops as you play to be constantly interesting throughout a playthrough.
2. A constant feeling of 'this is entertaining', 'I am engrossed'.
3. Tight story where every action moves the player forward.
4. Side quests always allow you to learn more about the story / world / player / characters. They are never fetch quests or padding to increase play time.
5.

Estimated Scope:
- Vertical slice length:
- Full game length:
- Number of regions:
- Number of memories:


---

## 2. STORY & TONE

### Tone
The game is rooted in the bleakness of trauma with the persistent hope of moving beyond it. There is always darkness, but there is always light present too. The orb is the physical embodiment of this — it never goes out entirely.

The game communicates almost entirely through visuals, environment, and fragments. In the spirit of Inside and Limbo, there is no explicit exposition. Players who pay attention will understand more. Players who do not will still feel the weight of what they experience. Both are valid.

### The Opening
The orb wakes first. It becomes aware of darkness, then warmth, then the faint sense of being held. The PC is already there — already protecting it — before the player understands who either of them are. The first thing the player sees is the orb. The first thing the orb knows is that it is not alone.

Why the PC is in the forest, and why the orb is there, is never directly explained. The two simply find each other. The relationship forms from circumstance and proximity.

The PC returns home to find everyone gone — replaced by shadows. The orb did not cause this. Whether the two events are connected is left unresolved. That uncertainty is intentional.

### The Orb
The orb is not a companion in the traditional sense. It does not speak, guide, or advise. It is carried by the PC in a staff — not wielded, but protected. The dynamic is inverted from most companion designs: the PC is the protector, not the other way around.

The orb is the PC's last intact feeling — something they were still holding onto when everything broke. It predates language for them. It simply is.

**Behaviour:**
- Dims in heavier shards, brightens as trauma is resolved — a passive emotional barometer
- Vibrates when used in empty spaces, revealing shadows that were always present but unseen
- The shadow was there before it was visible — this mirrors how suppressed memory works
- Other characters may not perceive the orb the same way, or at all

The orb grows stronger and more defined over the course of the journey, reflecting the PC's own healing without a word of dialogue about it. The PC's own shadow — their own unprocessed moment — is likely the last one the orb finds.

### The Shadows
Shadows are not enemies. They are people. The PC does not hunt them — they witness them. Healing a shadow is the act of understanding them: finding the fragments of their life, matching them correctly, and refusing to let them be reduced to their worst moment.

When a shadow is healed, they do not return. They disappear. The world simply carries less of their pain. Each resolution makes the world that much lighter.

**The item/note system:**
- Each shadow has a corresponding item and note hidden in the world
- Items and notes are contextually placed — a notebook in the tavern, an axe in the executioner's yard
- It is the trauma associated with an item that connects it to the shadow, not the item itself
- In battle, the player must determine which information belongs to which shadow
- Using the wrong information damages the PC and strengthens the shadow
- Using the correct information reveals the shadow's final true memory before they are healed
- If the PC heals a shadow without the correct item, a false memory is shown — the shadow returns if the PC leaves and comes back

### The PC's Shadow
The PC's own shadow will have no external items or notes to find. Whatever is needed to heal it has been carried the whole time. That recognition is the ending.

---

## 3. VERTICAL SLICE DEFINITION
Goal:
Build the smallest complete experience proving the concept.

Vertical Slice Includes:
- One explorable region
- One place screen with a puzzle
- One shadow encounter
- One healing battle
- One memory reveal
- Save/load functionality

Success Criteria:
Player can travel → explore → collect fragments → match to shadow → heal → unlock memory → save progress

Base scenes needed:
- World map
- Region map (initial class extended to 12 regions)
- Place (numerous states navigated by PC by exiting edges of screen)
- Battle
- Memory scene (duplicated from 'Place' with a different colour palette — possibly black and white)


---

## 4. COMBAT DESIGN (HEALING BATTLES)

Design Intent:
Battles are not filler. Every battle matters — in the middle and at the end, something new is learned about the shadow or the PC. The player manages healing the shadow, defending themselves, and ensuring the shadow's actions do not corrupt them entirely.

Battle Type:
- Turn-based
- Party size: 1
- Enemy type: Shadow (various forms)

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
Shadow fully healed / uncorrupted

Loss / Failure Condition:
1. Player becomes corrupted and turns to shadow.
2. If above occurs, player will be saved by the orb.

Battle UI Elements:
- Action list
- MP display
- Corruption bar
- Feedback text
- Memory reveal window

Progression Notes:
- Start with single ability to heal
- Talk — player can decide to talk on every turn to learn more about the shadow / person inside
- Parry attacks and...
- Timed attacks — if perfect, increase healing
- Corruption purge — heal self of corruption from enemy
- Purge overflow — overpurge converts excess corruption into a shared heal pool
- Pacifying mend — can delay an enemy's turn
- Enemy never 'attacks' but corrupts the PC
- Sacrificial mend
- Manifest memory — show a shadow a related memory to them if you discovered their identity in a prior puzzle
- Heal all enemies
- Corrupt self — make the ultimate sacrifice and take all the corruption from an enemy and give to self


---

## 5. WORLD & REGION DESIGN

World Concept:
Twelve floating shards in a void space. The shards are fragments of memory — the PC and those around them living through them in order to move past not only their own trauma but the trauma of those around them. The orb is the means of travel between shards: it grows from the PC's staff and consumes them to move to another shard.

World Map Structure:
- Regions count: 12 shards
- Travel method: Orb between shards. Walk across regions on each shard. Walk in each individual place.
- Locked / unlocked areas: Each shard follows a metroidvania concept — not all areas are available on first visit. After unlocking new abilities the player can return to defeat more challenging bosses or pass through increasingly difficult puzzles.

### 5.1 REGIONS

**The Fanged Shard (Gæt)** — initial prototype area
- Region ID: R01
- Biome:
- Visual / mood notes: Death Stranding (east). Iceland in summer.
- Places:
  1. Village square
     - 1.1 Main square
     - 1.2 The Crooked Ox
     - 1.3 Reeves' home
     - 1.4 Homes of several villagers
  2. PC's home
  3. Jonas' home
  4. The edge of the wilds (forest of black trees)
  5. ____'s home (woman)

- Shadows present:
  - PC's father
  - Mathias
  - Mathias' wife
  - PC's best friend (Mathias' son)
  - Orl (innkeeper)
  - Reeves
  - Couple
  - Jonas (final boss of area)
  - Creature in the wilds (optional boss — PC's mother)

- Puzzle / Investigation notes:
  Each shadow has a connected item which is the only way to completely remove their corruption. Items and notes are contextually placed — the trauma associated with the item connects it to the shadow.
  Example: A notebook found in the tavern reveals Reeves was incredibly lonely in her house. A lone shadow is found in the house.
  Example: An axe belonging to an executioner is actually associated with Mathias — the last person to be executed with it. It is the trauma of the item, not the item itself, that matters.


---

## 6. PUZZLES / INVESTIGATIONS

Place ID / Scene Name:

Purpose:
(Puzzle, lore, shadow encounter, etc.)

Puzzle Type:
(e.g. item/note matching, environmental clues, shadow context)

Key Objects:
- Object ID:
- Object ID:

Puzzle Solution Steps:
1.
2.
3.

Failure / Reset Rules:
Wrong match damages PC and strengthens shadow. Shadow returns after PC leaves if healed without correct item.

Rewards:
- Memory ID:
- Other rewards:


---

## 7. MEMORY SYSTEM

Memory Purpose:
Memories are the reward for understanding. Each healed shadow reveals their final true moment — not a victory, but a witness. The world becomes lighter each time.

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


---

## 8. DIALOGUE & WORLD BUILDING

There is no spoken dialogue. The world is communicated through:
- Environmental detail
- Items with contextual placement
- Notes and fragments found in the world
- The memory reveals unlocked by healing shadows correctly

Dialogue boxes, where used, are atmospheric and sparse. Each one earns its place. JSON structure for text boxes includes speaker (null for narration), style, and ID for tracking. See `/data/` for dialogue files.


---

## 9. UI / UX & CONTROLS

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
- Colour contrast
- Dialogue speed


---

## 10. TECHNICAL DESIGN

Engine:
Godot (version)

Language:
GDScript

Project Folder Structure:
```
/scenes
/scripts
/core
/entities
/ui
/assets
/data
  /dialogue     ← JSON text box files per scene
  /memories     ← Memory reveal data
  /items        ← Item/shadow correspondence data
```