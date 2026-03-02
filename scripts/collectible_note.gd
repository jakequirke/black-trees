extends Interactable

@export var note_name: String = "Torn Page"
@export var note_text: String = "A torn page reads: '...I remember the garden, the light through the leaves... before the darkness came and took everything...'"
@export var dialogue_box_path: NodePath

var dialogue_box: CanvasLayer

func _ready():
	super._ready()
	dialogue_box = get_node(dialogue_box_path)

func interact() -> void:
	GameState.add_note(note_name)
	dialogue_box.show_text(note_text)
	await dialogue_box.dismissed
	queue_free()
