extends Interactable

@export var item_name: String = "Worn Locket"
@export var pickup_text: String = "You found a Worn Locket. It feels warm to the touch, as if holding a fading memory..."
@export var dialogue_box_path: NodePath

var dialogue_box: CanvasLayer

func _ready():
	super._ready()
	dialogue_box = get_node(dialogue_box_path)

func interact() -> void:
	GameState.add_item(item_name)
	dialogue_box.show_text(pickup_text)
	await dialogue_box.dismissed
	queue_free()
