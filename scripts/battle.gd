extends Control

enum State { PLAYER_TURN, SHADOW_TURN, BATTLE_OVER }

# Battle stats
var shadow_corruption: int = 80
var shadow_max_corruption: int = 80
var shadow_damage: int = 8

var current_state: State = State.PLAYER_TURN

# UI references
@onready var corruption_bar: ProgressBar = $VBoxContainer/CorruptionSection/CorruptionBar
@onready var corruption_label: Label = $VBoxContainer/CorruptionSection/CorruptionLabel
@onready var feedback_label: Label = $VBoxContainer/FeedbackLabel
@onready var hp_label: Label = $VBoxContainer/StatsSection/HPLabel
@onready var mp_label: Label = $VBoxContainer/StatsSection/MPLabel
@onready var heal_button: Button = $VBoxContainer/ButtonSection/HealButton
@onready var reveal_note_button: Button = $VBoxContainer/ButtonSection/RevealNoteButton
@onready var reveal_item_button: Button = $VBoxContainer/ButtonSection/RevealItemButton
@onready var talk_button: Button = $VBoxContainer/ButtonSection/TalkButton
@onready var flee_button: Button = $VBoxContainer/ButtonSection/FleeButton

func _ready():
	heal_button.pressed.connect(_on_heal)
	reveal_note_button.pressed.connect(_on_reveal_note)
	reveal_item_button.pressed.connect(_on_reveal_item)
	talk_button.pressed.connect(_on_talk)
	flee_button.pressed.connect(_on_flee)

	reveal_note_button.visible = GameState.has_note("Torn Page") and not GameState.note_revealed_in_battle
	reveal_item_button.visible = GameState.has_item("Worn Locket") and not GameState.item_revealed_in_battle

	update_ui()
	feedback_label.text = "A corrupted shadow stands before you. Help it remember..."

func update_ui() -> void:
	corruption_bar.max_value = shadow_max_corruption
	corruption_bar.value = shadow_corruption
	corruption_label.text = "Corruption: %d / %d" % [shadow_corruption, shadow_max_corruption]
	hp_label.text = "HP: %d / %d" % [GameState.player_hp, GameState.player_max_hp]
	mp_label.text = "MP: %d / %d" % [GameState.player_mp, GameState.player_max_mp]

	var can_act = current_state == State.PLAYER_TURN
	heal_button.disabled = not can_act or GameState.player_mp < 10
	talk_button.disabled = not can_act
	flee_button.disabled = not can_act

	if reveal_note_button.visible:
		reveal_note_button.disabled = not can_act or GameState.note_revealed_in_battle or GameState.player_mp < 15
	if reveal_item_button.visible:
		reveal_item_button.disabled = not can_act or GameState.item_revealed_in_battle or GameState.player_mp < 15

func _on_heal() -> void:
	if current_state != State.PLAYER_TURN:
		return
	GameState.player_mp -= 10
	shadow_corruption = max(0, shadow_corruption - 15)
	feedback_label.text = "You channel healing light... The shadow's corruption fades slightly. (-15 corruption, -10 MP)"
	end_player_turn()

func _on_reveal_note() -> void:
	if current_state != State.PLAYER_TURN:
		return
	GameState.player_mp -= 15
	shadow_corruption = max(0, shadow_corruption - 25)
	GameState.note_revealed_in_battle = true
	feedback_label.text = "You hold up the torn page. The shadow trembles as a memory resurfaces... (-25 corruption, -15 MP)"
	reveal_note_button.visible = false
	update_ui()
	await get_tree().create_timer(2.0).timeout
	end_player_turn()

func _on_reveal_item() -> void:
	if current_state != State.PLAYER_TURN:
		return
	GameState.player_mp -= 15
	shadow_corruption = max(0, shadow_corruption - 25)
	GameState.item_revealed_in_battle = true
	feedback_label.text = "You show the worn locket. The shadow reaches out, recognition flickering... (-25 corruption, -15 MP)"
	reveal_item_button.visible = false
	update_ui()
	await get_tree().create_timer(2.0).timeout
	end_player_turn()

func _on_talk() -> void:
	if current_state != State.PLAYER_TURN:
		return
	shadow_corruption = max(0, shadow_corruption - 3)
	feedback_label.text = "You speak softly to the shadow. It listens... barely. (-3 corruption)"
	end_player_turn()

func _on_flee() -> void:
	if current_state != State.PLAYER_TURN:
		return
	current_state = State.BATTLE_OVER
	update_ui()
	feedback_label.text = "You step back from the shadow. It watches you leave, still lost in its corruption..."
	await get_tree().create_timer(1.5).timeout
	GameState.end_battle_defeat()

func end_player_turn() -> void:
	update_ui()
	if shadow_corruption <= 0:
		if GameState.note_revealed_in_battle and GameState.item_revealed_in_battle:
			victory()
		else:
			await corruption_restores()
		return
	current_state = State.SHADOW_TURN
	update_ui()
	await get_tree().create_timer(1.0).timeout
	shadow_turn()

func corruption_restores() -> void:
	current_state = State.BATTLE_OVER
	update_ui()
	feedback_label.text = "The corruption fades... but without its lost memories, darkness floods back. You need something more to truly reach it."
	await get_tree().create_timer(3.0).timeout
	shadow_corruption = shadow_max_corruption
	update_ui()
	await get_tree().create_timer(1.0).timeout
	current_state = State.SHADOW_TURN
	update_ui()
	await get_tree().create_timer(1.0).timeout
	shadow_turn()

func shadow_turn() -> void:
	var damage = shadow_damage
	if GameState.note_revealed_in_battle and GameState.item_revealed_in_battle:
		damage = shadow_damage / 2
	GameState.player_hp -= damage
	feedback_label.text = "The shadow lashes out in confusion! You take %d damage." % damage
	if GameState.player_hp <= 0:
		GameState.player_hp = 0
		update_ui()
		defeat()
		return
	current_state = State.PLAYER_TURN
	update_ui()

func victory() -> void:
	current_state = State.BATTLE_OVER
	update_ui()
	feedback_label.text = "The shadow's corruption fades completely. It remembers who it was... You saved it."
	await get_tree().create_timer(2.5).timeout
	GameState.end_battle_victory()

func defeat() -> void:
	current_state = State.BATTLE_OVER
	update_ui()
	feedback_label.text = "The corruption overwhelms you... You collapse, but the shadow spares you. You awaken back in the field."
	await get_tree().create_timer(2.5).timeout
	GameState.end_battle_defeat()
