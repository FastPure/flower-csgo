#pragma once

class bf_write;
class bf_read;

class game_event
{
public:
    virtual ~game_event() = 0;
    virtual const char *GetName() const = 0;

    virtual bool  IsReliable() const = 0;
    virtual bool  IsLocal() const = 0;
    virtual bool  IsEmpty( const char *keyName = NULL ) = 0;

    virtual bool  GetBool( const char *keyName = NULL , bool defaultValue = false ) = 0;
    virtual int   get_int( const char *keyName = NULL , int defaultValue = 0 ) = 0;
    virtual unsigned long GetUint64( const char *keyName = NULL , unsigned long defaultValue = 0 ) = 0;
    virtual float get_float( const char *keyName = NULL , float defaultValue = 0.0f ) = 0;
    virtual const char *GetString( const char *keyName = NULL , const char *defaultValue = "" ) = 0;
    virtual const wchar_t *GetWString( const char *keyName , const wchar_t *defaultValue = L"" ) = 0;

    virtual void SetBool( const char *keyName , bool value ) = 0;
    virtual void SetInt( const char *keyName , int value ) = 0;
    virtual void SetUint64( const char *keyName , unsigned long value ) = 0;
    virtual void SetFloat( const char *keyName , float value ) = 0;
    virtual void SetString( const char *keyName , const char *value ) = 0;
    virtual void SetWString( const char *keyName , const wchar_t *value ) = 0;
};

class game_event_listener2
{
public:
    virtual ~game_event_listener2( void )
    {
    };
    virtual void fire_game_event( game_event* pEvent ) = 0;
};

class game_event_mgr
{
public:
    virtual ~game_event_mgr( void )
    {
    };
    virtual int LoadEventsFromFile( const char* filename ) = 0;
    virtual void Reset() = 0;
    virtual bool AddListener( game_event_listener2* listener , const char* name , bool server_side ) = 0;
    virtual bool FindListener( game_event_listener2* listener , const char* name ) = 0;
    virtual void RemoveListener( game_event_listener2* listener ) = 0;
    virtual void AddListenerGlobal( game_event_listener2* listener , bool server_side ) = 0;
    virtual game_event* unk( const char* pad , bool unk = false , int* trash = nullptr ) = 0;
    virtual bool fire_event( game_event* pEvent , bool bDontBroadcast = false ) = 0;
    virtual bool FireEventClientSide( game_event* pEvent ) = 0;
    virtual game_event* duplicate_event( game_event* pEvent ) = 0;
    virtual void FreeEvent( game_event* pEvent ) = 0;
    virtual bool SerializeEvent( game_event* pEvent , bf_write* buf ) = 0;
    virtual game_event* UnserializeEvent( bf_read* buf ) = 0;
};

