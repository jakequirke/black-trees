# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**Black Trees** is a top-down pixel-art RPG built in **Godot 4.6** using **GDScript**. The player heals shadow creatures rather than attacking them, recovering memories to progress. The project is in early development (vertical slice phase).

## Engine & Language

- **Engine:** Godot 4.6 (Forward Plus renderer)
- **Language:** GDScript (no C#/C++ — previous C++ approach was removed)
- **Physics:** Jolt Physics (3D engine set, but game is 2D)

## Running the Project

Open `project.godot` in the Godot 4.6 editor. The main scene is `scenes/hello_world.tscn`.

Claude Code cannot run Godot directly — scene/node changes should be made by editing `.tscn` and `.gd` files.

## Project Structure

```
scenes/       # Godot scene files (.tscn)
scripts/      # GDScript files (.gd)
assets/       # Sprites, tilesets, and other art
```

Planned but not yet created directories (from design doc):
```
core/         # Core systems (save/load, game state)
entities/     # Entity scripts (shadows, NPCs)
ui/           # UI scenes and scripts
data/         # JSON content data (memories, dialogue)
```

## Architecture

- **Player** (`scripts/player.gd`): CharacterBody2D with grid-based input movement using Godot's input map. Movement uses `left`/`right`/`up`/`down` actions (WASD + Arrow keys + gamepad).
- **Main scene** (`scenes/hello_world.tscn`): Root Node2D containing the player (CharacterBody2D with Sprite2D, CollisionShape2D, Camera2D) and a TileMapLayer with 64x64 tile size.

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
