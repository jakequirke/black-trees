extends Control

@onready var start_button: Button = $VBoxContainer/StartButton
@onready var options_button: Button = $VBoxContainer/OptionsButton

func _ready() -> void:
	start_button.pressed.connect(_on_start_pressed)
	options_button.pressed.connect(_on_options_pressed)

func _on_start_pressed() -> void:
	SceneManager.change_scene("res://scenes/forest.tscn", Vector2(600, 400))

func _on_options_pressed() -> void:
	pass
