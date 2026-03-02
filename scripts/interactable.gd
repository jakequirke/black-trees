extends Area2D
class_name Interactable

@export var prompt_text: String = "[E] Interact"

@onready var prompt_label: Label = $PromptLabel

var player_in_range: bool = false

func _ready():
	body_entered.connect(_on_body_entered)
	body_exited.connect(_on_body_exited)
	if prompt_label:
		prompt_label.visible = false

func _on_body_entered(body: Node2D) -> void:
	if body.is_in_group("player"):
		player_in_range = true
		if prompt_label:
			prompt_label.visible = true

func _on_body_exited(body: Node2D) -> void:
	if body.is_in_group("player"):
		player_in_range = false
		if prompt_label:
			prompt_label.visible = false

func _unhandled_input(event: InputEvent) -> void:
	if player_in_range and event.is_action_pressed("interact"):
		get_viewport().set_input_as_handled()
		interact()

func interact() -> void:
	pass
