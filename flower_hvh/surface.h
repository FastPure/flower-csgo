#pragma once
class surface
{
public:
    enum draw_type
    {
        def = 0 ,
    };

    enum font_flags
    {
        none ,
        italic = 0x001 ,
        underline = 0x002 ,
        strike_out = 0x004 ,
        idk_symbol = 0x008 ,
        idk_alias = 0x010 ,
        blur = 0x020 ,
        useless_one = 0x040 ,
        drop_shadow = 0x080 ,
        useless_two = 0x100 ,
        outline = 0x200 ,
        custom = 0x400 ,
        bitmap = 0x800 ,
    };

    auto draw_color( unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a )
    {
        using original = void( __thiscall* )( void* , unsigned __int8 , unsigned __int8 , unsigned __int8 , unsigned __int8 );
        return globals::tools::get_virtualfn<15 , original>( this )( this , r , g , b , a );
    }

    auto draw_filled_rect( uint32_t x , uint32_t y , uint32_t w , uint32_t h )
    {
        using original = void( __thiscall* )( void* , uint32_t , uint32_t , uint32_t , uint32_t );
        return  globals::tools::get_virtualfn<16 , original>( this )( this , x , y , w , h );
    }

    auto draw_outline_rect( uint32_t x , uint32_t y , uint32_t w , uint32_t h )
    {
        using original = void( __thiscall* )( void* , uint32_t , uint32_t , uint32_t , uint32_t );
        return  globals::tools::get_virtualfn<18 , original>( this )( this , x , y , w , h );
    }

    auto draw_line( uint32_t x , uint32_t y , uint32_t x2 , uint32_t y2 )
    {
        using original = void( __thiscall* )( void* , uint32_t , uint32_t , uint32_t , uint32_t );
        return  globals::tools::get_virtualfn<19 , original>( this )( this , x , y , x2 , y2 );
    }

    auto draw_font( unsigned long index )
    {
        using original = void( __thiscall* )( void* , unsigned long );
        return  globals::tools::get_virtualfn<23 , original>( this )( this , index );
    }

    auto set_text_color( unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a )
    {
        using original = void( __thiscall* )( void* , unsigned __int8 , unsigned __int8 , unsigned __int8 , unsigned __int8 );
        return  globals::tools::get_virtualfn<25 , original>( this )( this , r , g , b , a );
    }

    auto set_text_pos( uint32_t x , uint32_t y )
    {
        using original = void( __thiscall* )( void* , uint32_t , uint32_t );
        return  globals::tools::get_virtualfn<26 , original>( this )( this , x , y );
    }

    auto print_text( wchar_t* text , uint32_t length , draw_type drawtype = draw_type::def )
    {
        using original = void( __thiscall* )( void* , wchar_t* , int , draw_type );
        return  globals::tools::get_virtualfn<28 , original>( this )( this , text , length , drawtype );
    }

    auto unlock_cursor()
    {
        using original = void( __thiscall* )( void* );
        return  globals::tools::get_virtualfn<66 , original>( this )( this );
    }

    auto create_font()
    {
        using original = unsigned long( __thiscall* )( void* );
        return  globals::tools::get_virtualfn<71 , original>( this )( this );
    }

    auto set_font_style( unsigned long font , const char* fontName , uint32_t tall , uint32_t weight , uint32_t blur , uint32_t scanlines , uint32_t flags , uint32_t rangeMin = 0 , uint32_t rangeMax = 0 )
    {
        using original = bool( __thiscall* )( void* , unsigned long , const char* , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t );
        return  globals::tools::get_virtualfn<72 , original>( this )( this , font , fontName , tall , weight , blur , scanlines , flags , rangeMin , rangeMax );
    }

    auto get_text_size( unsigned long font , const wchar_t* text , uint32_t& wide , uint32_t& tall )
    {
        using original = void( __thiscall* )( void* , unsigned long , const wchar_t* , uint32_t& , uint32_t& );
        return  globals::tools::get_virtualfn<79 , original>( this )( this , font , text , wide , tall );
    }  

    auto play_sound( const char * patch )
    {
        using original = void( __thiscall* )( void* , const char *);
        return  globals::tools::get_virtualfn<82 , original>( this )( this , patch );
    }
};

