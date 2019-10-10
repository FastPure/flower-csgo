#pragma once
namespace drawing
{
    auto draw_outline_rect( uint32_t x , uint32_t y , uint32_t w , uint32_t h , unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a )
    {
        flower_sdk::p_surface->draw_color( r , g , b , a );
        flower_sdk::p_surface->draw_outline_rect( x , y , w , h );
    }

    auto draw_fill_rect( uint32_t x , uint32_t y , uint32_t w , uint32_t h , unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a )
    {
        flower_sdk::p_surface->draw_color( r , g , b , a );
        flower_sdk::p_surface->draw_filled_rect( x , y , w , h );
    }

    auto draw_line( uint32_t x , uint32_t y , uint32_t w , uint32_t h , unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a )
    {
        flower_sdk::p_surface->draw_color( r , g , b , a );
        flower_sdk::p_surface->draw_line( x , y , w , h );
    }

    auto draw_outline_box( uint32_t x , uint32_t y , uint32_t w , uint32_t h , unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a )
    {
        draw_outline_rect( x , y , w , h , r , g , b , a );
        draw_outline_rect( x + 1 , y + 1 , w - 1 , h - 1 , 0 , 0 , 0 , a );
        draw_outline_rect( x - 1 , y - 1 , w + 1 , h + 1 , 0 , 0 , 0 , a );
    }

    auto draw_inline_box( uint32_t x , uint32_t y , uint32_t w , uint32_t h , unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a )
    {
        draw_outline_rect( x , y , w , h , r , g , b , a );
        draw_outline_rect( x - 1 , y - 1 , w + 1 , h + 1 , 0 , 0 , 0 , a );
    }

    auto draw_text( uint32_t x , uint32_t y , unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a , unsigned long font , const char* text , ... )
    {
        size_t origsize = strlen( text ) + 1;
        const size_t newsize = 100;
        size_t convertedChars = 0;
        wchar_t wcstring[ newsize ];
        mbstowcs_s( &convertedChars , wcstring , origsize , text , _TRUNCATE );

        flower_sdk::p_surface->draw_font( font );
        flower_sdk::p_surface->set_text_color( r , g , b , a );
        flower_sdk::p_surface->set_text_pos( x , y );
        flower_sdk::p_surface->print_text( wcstring , wcslen( wcstring ) );
    }

    auto draw_complex_text( uint32_t x , uint32_t y , unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , unsigned __int8 a , unsigned long font , const char* text , ... )
    {
        if ( !text ) return;

        va_list va_alist;
        char logBuf[ 256 ] = { 0 };

        va_start( va_alist , text );
        _vsnprintf_s( logBuf + strlen( logBuf ) , 256 - strlen( logBuf ) , sizeof( logBuf ) - strlen( logBuf ) , text , va_alist );
        va_end( va_alist );

        draw_text( x , y , r , g , b , a , font , logBuf );
    }
}