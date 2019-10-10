#pragma once
#include "configs.h"
#include "definitions.h"

#include "global_var.h"

#include "panel.h"
#include "surface.h"

#include "engine.h"
#include "debug_overlay.h"
#include "convar.h"
#include "model.h"

#include "client_class.h"
#include "glow_manager.h"

#include "weapon_base.h"
#include "netchannel.h"
#include "user_cmd.h"
#include "view_setup.h"
#include "movement.h"
#include "game_event.h"
#include "trace.h"
#include "bullet_beam.h"
#include "entity_list.h"
#include "base_client.h"


namespace flower_sdk
{
    panel_id * p_panel = nullptr;
    surface * p_surface = nullptr;

    engine * p_engine = nullptr;
    trace * p_trace = nullptr;
    model * p_model = nullptr;
    material * p_material = nullptr;
    model_render * p_model_render = nullptr;
    material_system * p_material_system = nullptr;
    cvar * p_cvar = nullptr;
    render_view * p_render_view = nullptr;
    wep_system * p_wep_system = nullptr;

    move_helper * p_move_helper = nullptr;
    prediction * p_prediction = nullptr;
    render_beams * p_beams = nullptr;
    game_movement * p_game_movement = nullptr;
    game_event_mgr * p_game_event = nullptr;
    global_var_base * p_globals_var_base = nullptr;
    debug_overlay * p_debug_overlay = nullptr;
    client_state * p_client_state = nullptr;

    input * p_input = nullptr;
    base_client * p_base_client = nullptr;
    entity_list * p_entity_list = nullptr;

    glow_manager * p_glow = nullptr;
    client_mode * p_client_mode = nullptr;
}

#include "csplayer.h"
