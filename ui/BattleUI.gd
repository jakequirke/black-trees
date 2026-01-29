extends Control
# This is a skeleton example. Replace `WorldAPI` calls with your actual binding names.

var world_api = null
var current_shadow_id = ""

func _ready():
    # Example: a singleton exposed by GDNative/GDExtension
    if Engine.has_singleton("WorldAPI"):
        world_api = Engine.get_singleton("WorldAPI")
    else:
        print("WorldAPI singleton not found. Make sure GDExtension wrapper is loaded.")

func start_battle(player_id, shadow_id):
    current_shadow_id = shadow_id
    var actions = world_api.get_available_actions()
    update_action_buttons(actions)
    update_shadow_ui()

func update_action_buttons(actions):
    # Clear and create button list (pseudo)
    $ActionsVBox.clear()
    for a in actions:
        var btn = Button.new()
        btn.text = a.name
        btn.connect("pressed", Callable(self, "_on_action_pressed").bind(a.id))
        $ActionsVBox.add_child(btn)

func _on_action_pressed(action_id):
    var result = world_api.perform_action(action_id, current_shadow_id)
    $MessageLabel.text = result["message"]
    if result.has("healed") and result["healed"]:
        var mem = world_api.get_memory_for_shadow(current_shadow_id)
        get_node("/root/DialogueUI").show_memory(mem)
