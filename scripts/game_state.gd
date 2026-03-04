extends Node

# Player stats
var player_hp: int = 100
var player_max_hp: int = 100
var player_mp: int = 50
var player_max_mp: int = 50

# Inventory
var items: Array[String] = []
var notes: Array[String] = []

# Shadow progress
var shadow_attempted: bool = false
var shadow_healed: bool = false
var note_revealed_in_battle: bool = false
var item_revealed_in_battle: bool = false

func has_item(item_name: String) -> bool:
	return items.has(item_name)

func has_note(note_name: String) -> bool:
	return notes.has(note_name)

func add_item(item_name: String) -> void:
	if not items.has(item_name):
		items.append(item_name)

func add_note(note_name: String) -> void:
	if not notes.has(note_name):
		notes.append(note_name)

func can_challenge_shadow() -> bool:
	return items.size() > 0 and notes.size() > 0

func start_battle() -> void:
	note_revealed_in_battle = false
	item_revealed_in_battle = false
	player_hp = player_max_hp
	player_mp = player_max_mp
	SceneManager.change_scene("res://scenes/battle.tscn")

func end_battle_victory() -> void:
	shadow_healed = true
	SceneManager.change_scene("res://scenes/exploration.tscn")

func end_battle_defeat() -> void:
	player_hp = player_max_hp
	player_mp = player_max_mp
	SceneManager.change_scene("res://scenes/exploration.tscn")
