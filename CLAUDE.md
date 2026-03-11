# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**Black Trees** is a top-down pixel-art RPG built in **Godot 4.6** using **GDScript**. The player heals shadow creatures rather than attacking them, recovering memories to progress. The project is in early development (vertical slice phase).

## Engine & Language

- **Engine:** Godot 4.6 (Forward Plus renderer)
- **Language:** GDScript (no C#/C++ — previous C++ approach was removed)
- **Physics:** Jolt Physics (3D engine set, but game is 2D)

## Running the Project

Open `project.godot` in the Godot 4.6 editor. The main scene is `scenes/main_menu.tscn`.

Claude Code cannot run Godot directly — scene/node changes should be made by editing `.tscn` and `.gd` files. **Important:** Avoid overwriting `.tscn` tile_map_data or TileSet sub_resources — those are managed by Godot's editor. Only add/modify nodes and script references.

## Project Structure

```
scenes/       # Godot scene files (.tscn)
scripts/      # GDScript files (.gd)
assets/       # Sprites, tilesets, and other art
```

```
core/         # Core systems (SceneManager autoload, save/load, game state)
entities/     # Entity scripts (shadows, NPCs)
ui/           # UI scenes and scripts
data/         # JSON content data (memories, dialogue)
```

## Architecture

- **Player** (`scripts/player.gd`): CharacterBody2D with grid-based input movement using Godot's input map. Movement uses `left`/`right`/`up`/`down` actions (WASD + Arrow keys + gamepad).
- **Main menu** (`scenes/main_menu.tscn`): Start Game and Options buttons. Entry point of the game.
- **Forest scene** (`scenes/forest.tscn`): First gameplay scene. Left exit leads to village, right side has collision wall.
- **Village square** (`scenes/village-square.tscn`): Root Node2D with TileMapLayer, Player, Shadow/Item/Note interactables, DialogueBox, and ExitToHome Area2D.
- **Home scene** (`scenes/home.tscn`): PC's home with Player and ExitToVillage Area2D.
- **SceneManager** (`core/scene_manager.gd`): Autoload providing `change_scene(path, spawn_position)` with fade-to-black transitions.
- **Scene exits** (`scripts/scene_exit.gd`): Reusable Area2D trigger with `@export var target_scene` and `@export var spawn_offset`.

## Input Map

Custom input actions defined in `project.godot`: `left`, `right`, `up`, `down` (gameplay movement) alongside default `ui_left`, `ui_right`, `ui_up`, `ui_down` (menus). Use these action names when scripting input.

## Game Design Reference

`README.md` contains the full Game Design Document. Key mechanics to be aware of:
- **Healing battles** (turn-based): Player heals shadows, not attacks. Win = shadow fully healed. Loss = player becomes corrupted.
- **Memory system**: Healing shadows and solving puzzles unlock memories that drive narrative.
- **World structure**: 12 floating shards, each a region. First region is "The Fanged Shard" (R01).
- **Puzzles/Investigation**: Shadows have connected items; wrong item choices damage the player.

## Conventions

- Use tabs for indentation (GDScript standard, per `.editorconfig`)
- Use `snake_case` for variables/functions, `PascalCase` for classes/nodes (GDScript convention)
- Prefix exported variables with `@export`
- Keep scripts in `scripts/`, scenes in `scenes/`, art in `assets/`
