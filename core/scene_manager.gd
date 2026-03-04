extends Node

signal scene_changing
signal scene_changed

var is_transitioning: bool = false
var spawn_position: Vector2 = Vector2.INF
var _overlay: ColorRect

func _ready() -> void:
	var canvas_layer = CanvasLayer.new()
	canvas_layer.layer = 100
	add_child(canvas_layer)

	_overlay = ColorRect.new()
	_overlay.color = Color(0, 0, 0, 0)
	_overlay.mouse_filter = Control.MOUSE_FILTER_IGNORE
	_overlay.set_anchors_preset(Control.PRESET_FULL_RECT)
	canvas_layer.add_child(_overlay)

func change_scene(path: String, target_spawn: Vector2 = Vector2.INF) -> void:
	spawn_position = target_spawn
	if is_transitioning:
		return
	is_transitioning = true
	scene_changing.emit()

	var tween = create_tween()
	tween.tween_property(_overlay, "color:a", 1.0, 0.4)
	await tween.finished

	get_tree().change_scene_to_file(path)
	await get_tree().process_frame

	var fade_in = create_tween()
	fade_in.tween_property(_overlay, "color:a", 0.0, 0.4)
	await fade_in.finished

	is_transitioning = false
	scene_changed.emit()
