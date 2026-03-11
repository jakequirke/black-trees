extends CharacterBody2D

@export var speed = 400

var sprite: Sprite2D
var anim_timer: float = 0.0
var anim_frame: int = 0
var last_direction: String = "down"

# Walk frames: direction -> array of textures
var walk_frames: Dictionary = {}
# Idle frames: direction -> array of textures
var idle_frames: Dictionary = {}

func _ready():
	add_to_group("player")
	sprite = $Sprite2D
	if SceneManager.spawn_position != Vector2.INF:
		global_position = SceneManager.spawn_position
		SceneManager.spawn_position = Vector2.INF
	_load_textures()
	sprite.texture = idle_frames["down"][0]

func _load_textures():
	idle_frames["down"] = [
		load("res://assets/idle_down_1.png"),
		load("res://assets/idle_down_2.png"),
	]
	walk_frames["down"] = [
		load("res://assets/walk_down_1.png"),
	]
	walk_frames["up"] = [
		load("res://assets/walk_up_1.png"),
		load("res://assets/walk_up_2.png"),
		load("res://assets/walk_up_3.png"),
	]
	walk_frames["left"] = [
		load("res://assets/walk_right_1.png"),
		load("res://assets/walk_right_2.png"),
	]
	walk_frames["right"] = [
		load("res://assets/walk_left_1.png"),
		load("res://assets/walk_left_2.png"),
		load("res://assets/walk_left_3.png"),
	]
	# For directions without dedicated idle sprites, use the first walk frame
	idle_frames["up"] = [walk_frames["up"][0]]
	idle_frames["left"] = [walk_frames["left"][0]]
	idle_frames["right"] = [walk_frames["right"][0]]

func movement():
	var input_direction = Input.get_vector("left", "right", "up", "down")
	velocity = input_direction * speed

func _get_facing_direction(input: Vector2) -> String:
	if abs(input.x) > abs(input.y):
		return "right" if input.x > 0 else "left"
	else:
		return "down" if input.y > 0 else "up"

func _physics_process(delta):
	movement()
	move_and_slide()

	var input_direction = Input.get_vector("left", "right", "up", "down")
	if input_direction != Vector2.ZERO:
		last_direction = _get_facing_direction(input_direction)
		var frames = walk_frames[last_direction]
		anim_timer += delta
		if anim_timer >= 0.15:
			anim_timer = 0.0
			anim_frame = (anim_frame + 1) % frames.size()
		if anim_frame >= frames.size():
			anim_frame = 0
		sprite.texture = frames[anim_frame]
	else:
		var frames = idle_frames[last_direction]
		anim_timer += delta
		if anim_timer >= 0.4:
			anim_timer = 0.0
			anim_frame = (anim_frame + 1) % frames.size()
		if anim_frame >= frames.size():
			anim_frame = 0
		sprite.texture = frames[anim_frame]
