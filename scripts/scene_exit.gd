extends Area2D

@export var target_scene: String
@export var spawn_offset: Vector2 = Vector2(0, 64)

func _ready() -> void:
	body_entered.connect(_on_body_entered)

func _on_body_entered(body: Node2D) -> void:
	if body.is_in_group("player"):
		SceneManager.change_scene(target_scene, spawn_offset)
