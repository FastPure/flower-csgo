#pragma once
namespace fixes
{
    inline auto distance_point_to_line( vector point , vector origin , vector direction )
    {
        auto point_direction = point - origin;

        auto temp_offset = point_direction.dot( direction ) / ( direction.x*direction.x + direction.y*direction.y + direction.z*direction.z );
        if ( temp_offset < 0.000001f )
            return FLT_MAX;

        auto perpendicular = origin + ( direction * temp_offset );

        return ( point - perpendicular ).lenght();
    }

    inline vector angle_to_vector( vector vector_ )
    {
        auto sy = sin( vector_.y / 180.f * static_cast< float >( 3.14159265358979323846f ) );
        auto cy = cos( vector_.y / 180.f * static_cast< float >( 3.14159265358979323846f ) );

        auto sp = sin( vector_.x / 180.f * static_cast< float >( 3.14159265358979323846f ) );
        auto cp = cos( vector_.x / 180.f* static_cast< float >( 3.14159265358979323846f ) );

        return vector( cp*cy , cp*sy , -sp );
    }

    auto angle_to_vector( const vector &angles , vector &forward )
    {   
        auto sin_cos=[]( float radian , float *sin , float *cos )
        {
            *sin = std::sin( radian );
            *cos = std::cos( radian );
        };

        auto deg_to_rad=[]( float val )
        {
            return val * ( 3.141592654f / 180.f );
        };

        float sp , sy , cp , cy;

        sin_cos( deg_to_rad( angles.y ) , &sy , &cy );
        sin_cos( deg_to_rad( angles.x ) , &sp , &cp );

        forward.x = cp * cy;
        forward.y = cp * sy;
        forward.z = -sp;
    }

    auto clamp = [ ] ( vector& angles )
    {
        if ( angles.x > 89.0f ) angles.x = 89.0f;
        else if ( angles.x < -89.0f ) angles.x = -89.0f;

        if ( angles.y > 180.0f ) angles.y = 180.0f;
        else if ( angles.y < -180.0f ) angles.y = -180.0f;

        angles.z = 0;
    };

    auto normalize_angles = [ ] ( vector& angles )
    {
        while ( angles.y <= -180 ) angles.y += 360;
        while ( angles.y > 180 ) angles.y -= 360;
        while ( angles.x <= -180 ) angles.x += 360;
        while ( angles.x > 180 ) angles.x -= 360;


        if ( angles.x > 89.0f )
            angles.x = 89.0f;
        else if ( angles.x < -89.0f )
            angles.x = -89.0f;

        if ( angles.y > 179.99999f )
            angles.y = 179.99999f;
        else if ( angles.y < -179.99999f )
            angles.y = -179.99999f;

        angles.z = 0;
    };

    auto clamp_and_normalize( vector& angles )
    {       
        normalize_angles( angles );
        clamp( angles );
    }

    auto vector_to_angles( const vector& forward , vector &angles )
    {
        if ( forward[ 1 ] == 0.0f && forward[ 0 ] == 0.0f )
        {
            angles[ 0 ] = ( forward[ 2 ] > 0.0f ) ? 270.0f : 90.0f;
            angles[ 1 ] = 0.0f;
        }
        else
        {
            angles[ 0 ] = atan2( -forward[ 2 ] , forward.lenght() ) * -180 / 3.14159265358979323846f;
            angles[ 1 ] = atan2( forward[ 1 ] , forward[ 0 ] ) * 180 / 3.14159265358979323846f;

            if ( angles[ 1 ] > 90 ) angles[ 1 ] -= 180;
            else if ( angles[ 1 ] < 90 ) angles[ 1 ] += 180;
            else if ( angles[ 1 ] == 90 ) angles[ 1 ] = 0;
        }

        angles[ 2 ] = 0.0f;
    }

    vector calc_angle( vector src , vector dst )
    {
        vector angles;
        vector delta = src - dst;
        vector_to_angles( delta , angles );
        normalize_angles( delta );
        return angles;
    }

    auto get_fov( const vector& view_angle , const vector& aim_angle )
    {
        vector delta = aim_angle - view_angle;
        normalize_angles( delta );
        return sqrtf( powf( delta.x , 2.0f ) + powf( delta.y , 2.0f ) );
    }

    auto init_prediction( user_cmd * cmd , csplayer * local )
    {
        *globals::functions::move::pred_random_seed = cmd->random_seed;

        globals::functions::move::pred_curtime = flower_sdk::p_globals_var_base->curtime;
        globals::functions::move::pred_frame_time = flower_sdk::p_globals_var_base->frametime;
     
        flower_sdk::p_globals_var_base->curtime = ( float ) local->get_tick_base() * flower_sdk::p_globals_var_base->interval_per_tick;
        flower_sdk::p_globals_var_base->frametime = flower_sdk::p_globals_var_base->interval_per_tick;

        flower_sdk::p_game_movement->StartTrackPredictionErrors( local );

        flower_sdk::p_move_helper->set_host( local );
        flower_sdk::p_prediction->setup_move( local , cmd , nullptr , bMoveData );
        flower_sdk::p_game_movement->ProcessMovement( local , bMoveData );
        flower_sdk::p_prediction->finish_move( local , cmd , bMoveData );
    }

    auto end_prediction( user_cmd * cmd , csplayer * local )
    {
        flower_sdk::p_game_movement->FinishTrackPredictionErrors( local );
        flower_sdk::p_move_helper->set_host( 0 );

        *globals::functions::move::pred_random_seed = -1;

        flower_sdk::p_globals_var_base->curtime = globals::functions::move::pred_curtime;
        flower_sdk::p_globals_var_base->frametime = globals::functions::move::pred_frame_time;
    }

    auto fix_move( user_cmd * cmd )
    {
#define DEG2RAD(x)  ((float)(x) * (float)(3.14159265358979323846f / 180.f))

        vector old_angles;
        flower_sdk::p_engine->get_view_angles( old_angles );

        float backup_foward = cmd->foward ,
         backup_side = cmd->side,
         delta = cmd->view_angles.y - old_angles.y,
         temp_1,
         temp_2;

        if ( old_angles.y < 0.f )
            temp_1 = 360.0f + old_angles.y;
        else
            temp_1 = old_angles.y;

        if ( cmd->view_angles.y < 0.0f )
            temp_2 = 360.0f + cmd->view_angles.y;
        else
            temp_2 = cmd->view_angles.y;

        if ( temp_2 < temp_1 )
            delta = abs( temp_2 - temp_1 );
        else
            delta = 360.0f - abs( temp_1 - temp_2 );
        delta = 360.0f - delta;

        cmd->foward = cos( DEG2RAD( delta ) ) * backup_foward + cos( DEG2RAD( delta + 90.f ) ) * backup_side;
        cmd->side = sin( DEG2RAD( delta ) ) * backup_foward + sin( DEG2RAD( delta + 90.f ) ) * backup_side;

        if ( cmd->view_angles.x >= 180 && cmd->view_angles.x <= 270 ) cmd->foward = -cmd->foward;
    }

    auto fix_slide( user_cmd * cmd )
    {
        cmd->buttons &= ~1024;
        cmd->buttons &= ~512;
        cmd->buttons &= ~8;
        cmd->buttons &= ~16;

        if ( cmd->foward > 0.f )
            cmd->buttons |= 8;
        else if ( cmd->foward < 0.f )
            cmd->buttons |= 16;
        if ( cmd->side > 0.f )
        {
            cmd->buttons |= 1024;
        }
        else if ( cmd->side < 0.f )
        {
            cmd->buttons |= 512;
        }
    }
}