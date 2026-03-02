extends Interactable

@export var dialogue_box_path: NodePath

var dialogue_box: CanvasLayer

func _ready():
	super._ready()
	dialogue_box = get_node(dialogue_box_path)

func interact() -> void:
	if GameState.shadow_healed:
		dialogue_box.show_text("The shadow stands peacefully. Its corruption is gone. You sense gratitude in its stillness.")
		return

	GameState.shadow_attempted = true
	dialogue_box.show_text("The shadow's corruption swirls before you. You steel yourself and step forward...")
	await dialogue_box.dismissed
	GameState.start_battle()
