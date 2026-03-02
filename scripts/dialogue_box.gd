extends CanvasLayer

signal dismissed

@onready var panel: PanelContainer = $PanelContainer
@onready var label: Label = $PanelContainer/MarginContainer/Label

var is_showing: bool = false

func _ready():
	panel.visible = false
	set_process_input(false)

func show_text(text: String) -> void:
	label.text = text
	panel.visible = true
	is_showing = true
	get_tree().paused = true
	set_process_input(true)

func _input(event: InputEvent) -> void:
	if not is_showing:
		return
	if event.is_action_pressed("interact"):
		get_viewport().set_input_as_handled()
		hide_text()

func hide_text() -> void:
	panel.visible = false
	is_showing = false
	set_process_input(false)
	get_tree().paused = false
	dismissed.emit()
