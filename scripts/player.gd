extends CharacterBody2D

@export var speed = 400

func _ready():
	add_to_group("player")
	if SceneManager.spawn_position != Vector2.INF:
		global_position = SceneManager.spawn_position
		SceneManager.spawn_position = Vector2.INF

func movement():
	var input_direction = Input.get_vector("left", "right", "up", "down")
	velocity = input_direction * speed

func _physics_process(_delta):
	movement()
	move_and_slide()
