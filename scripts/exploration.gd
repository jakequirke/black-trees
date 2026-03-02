extends Node2D

@onready var shadow: Area2D = $Shadow
@onready var item: Area2D = $Item
@onready var note: Area2D = $Note
@onready var shadow_sprite: Sprite2D = $Shadow/Sprite2D

func _ready():
	if GameState.shadow_healed:
		shadow_sprite.modulate = Color(0.5, 0.9, 0.5)
	if GameState.has_item("Worn Locket") and item:
		item.queue_free()
	if GameState.has_note("Torn Page") and note:
		note.queue_free()
