extends Node2D

@onready var shadow: Area2D = $Shadow
@onready var item: Area2D = $Item
@onready var note: Area2D = $Note
@onready var shadow_sprite: Sprite2D = $Shadow/Sprite2D
@onready var dialogue_box: CanvasLayer = $DialogueBox
@onready var bottom_trigger: Area2D = $BottomTrigger

var bottom_message_shown: bool = false

func _ready():
	if GameState.shadow_healed:
		shadow_sprite.modulate = Color(0.5, 0.9, 0.5)
	if GameState.has_item("Worn Locket") and item:
		item.queue_free()
	if GameState.has_note("Torn Page") and note:
		note.queue_free()
	bottom_trigger.body_entered.connect(_on_bottom_trigger_entered)

func _on_bottom_trigger_entered(body: Node2D) -> void:
	if body.is_in_group("player") and not bottom_message_shown:
		bottom_message_shown = true
		dialogue_box.show_text("The path continues south... but it is not yet safe to travel there.")
		await dialogue_box.dismissed
		bottom_message_shown = false
