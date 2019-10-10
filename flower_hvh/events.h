#pragma once
typedef void( *function )( game_event* event );
std::vector<game_event_listener2*> listeners = {};

class game_event_listener : public game_event_listener2
{
private:
    std::string eventName;
    function call;
    bool server;
public:
    game_event_listener() : eventName( "" ) , call( nullptr ) , server( false )
    {
    }

    game_event_listener( const std::string& event_name , const function Func , bool server )
        : eventName( event_name ) , call( Func ) , server( server )
    {
        this->register_listener();
    }

    virtual void fire_game_event( game_event* event )
    {
        this->call( event );
    }

    virtual int is_being_handled( void )
    {
        return 0x2A;
    }

    void register_listener( void )
    {
        static bool first = true;
        if ( !first )
            return;
        if ( flower_sdk::p_game_event->AddListener( this , this->eventName.c_str() , server ) )
            listeners.push_back( this );
    }
};

void draw_beam( vector start , vector end , int segment , float amplitude,
                unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a )
{
    beam_info create_beam;
    create_beam.type = TE_BEAMTESLA;
    create_beam.model_name = "sprites/purplelaser1.vmt";
    create_beam.model_index = -1;
    create_beam.halo_scale = 0.0f;
    create_beam.life = 1.5f;
    create_beam.w = 2.0f;
    create_beam.end_w = 2.0f;
    create_beam.fade_lenght = 0.0f;
    create_beam.amplitude = amplitude;
    create_beam.a = a;
    create_beam.propagation_speed = 0.2f;
    create_beam.start_frame = 0;
    create_beam.frame_rate = 0.f;
    create_beam.r = r;
    create_beam.g = g;
    create_beam.b = b;
    create_beam.segment = segment;
    create_beam.renderable = true;
    create_beam.start = start;
    create_beam.end = end;

    beam_t* myBeam = flower_sdk::p_beams->create_beam_points( create_beam );
    if ( myBeam )
        flower_sdk::p_beams->draw_beam( myBeam );
}

namespace events
{
#define register_event(pointer_to_event, function, event_name, extra) pointer_to_event = new game_event_listener(event_name, function, extra)

    game_event_listener * player_hurt;
    game_event_listener * bullet_impacts;

    static float	hurt_time;
    static int		health;
    static 	int		player_id;

    void listen_hitmarkers( game_event* event )
    {       
        auto setup_hitmarker = [ ]( float hurt_time_ , int health_ , int player_id_ )
        {      
            hurt_time = hurt_time_;
            health = health_;
            player_id = player_id_;
        };

        int attacker = flower_sdk::p_engine->get_player_id( event->get_int( "attacker" ) );
        static int player_id = flower_sdk::p_engine->get_player_id( event->get_int( "userid" ) );

        if ( attacker == flower_sdk::p_engine->get_local_player() && player_id != flower_sdk::p_engine->get_local_player() )
        {
            setup_hitmarker( flower_sdk::p_globals_var_base->curtime , event->get_int( "dmg_health" ) , player_id );

            flower_sdk::p_surface->play_sound( "buttons\\arena_switch_press_02.wav" );
        }
    }

    void listen_bullet_tracers( game_event* event )
    {
        csplayer * local = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_local_player() );

        if ( !local )
            return;

        auto* index = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_player_id( event->get_int( "userid" ) ) );

        vector position( event->get_float( "x" ) , event->get_float( "y" ) , event->get_float( "z" ) );

        if ( index )
            tracer_logs.push_back( beam_infos( index->get_eye_pos() , position , flower_sdk::p_globals_var_base->curtime , event->get_int( "userid" ) ) );          
    }
}
