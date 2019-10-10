template <class T>
static T GetFunction( void* instance , int index )
{
    const auto vtable = *static_cast< void*** >( instance );
    return reinterpret_cast< T >( vtable[ index ] );
}

class convar
{
public:
    char pad_0x0000[ 0x4 ];
    convar * pNext;
    int32_t bRegistered;
    char* pszName;
    char* pszHelpString;
    int32_t flags;
    char pad_0x0018[ 0x4 ];
    convar* pParent;
    char* pszDefaultValue;
    char* strString;
    int32_t StringLength;
    float fValue;
    int32_t nValue;
    int32_t bHasMin;
    float fMinVal;
    int32_t bHasMax;
    float fMaxVal;
    void *fnChangeCallback;
    float get_float( void ) const
    {
        auto temp = *( int* ) ( &fValue );
        auto temp_result = ( int ) ( temp ^ ( DWORD ) this );

        return *( float* ) ( &temp_result );
    }
    int get_int()
    {
        auto temp = *( int* ) ( &nValue );
        auto temp_result = ( int ) ( temp ^ ( uintptr_t ) this );

        return *( int* ) ( &temp_result );
    }
    bool GetBool()
    {
        return !!get_int();
    }
    void set_value( const char* value )
    {
        typedef void( __thiscall* OriginalFn )( void* , const char * );
        return GetFunction<OriginalFn>( this , 14 )( this , value );
    }
    void SetValueStr( const char* str )
    {
        typedef void( __thiscall* SetStringFn )( void* , const char* );
        return GetFunction<SetStringFn>( this , 13 )( this , str );
    }
    void set_value( int value )
    {
        typedef void( __thiscall* OriginalFn )( void* , int );
        return GetFunction<OriginalFn>( this , 16 )( this , value );
    }
    void SetValueChar( const char* name )
    {
        typedef void( __thiscall* SetNameFN )( void* , const char* );
        return GetFunction<SetNameFN>( this , 14 )( this , name );
    }
    void InternalSetString( const char* str )
    {
        typedef void( __thiscall* SetStringFn )( void* , const char* );
        return GetFunction<SetStringFn>( this , 17 )( this , str );
    }
    char* GetBaseName()
    {
        typedef char*( __thiscall* SetStringFn )( void* );
        return GetFunction<SetStringFn>( this , 6 )( this );
    }
    float get_float()
    {
        typedef float( __thiscall* SetValueFn )( void* );
        return GetFunction< SetValueFn >( this , 12 )( this );
    }
    int get_int( void ) const
    {
        return pParent->nValue;
    }
    const char* GetString( void ) const
    {
        return pParent->pszDefaultValue;
    }

};//Size=0x0048


class IAppSystem2
{
public:
    virtual void func0() = 0;
    virtual void func1() = 0;
    virtual void func2() = 0;
    virtual void func3() = 0;
    virtual void func4() = 0;
    virtual void func5() = 0;
    virtual void func6() = 0;
    virtual void func7() = 0;
    virtual void func8() = 0;
    virtual void func9() = 0;
};

struct CVarDLLIdentifier_t;

class cvar : public IAppSystem2
{
public:
    virtual void			func10() = 0;
    virtual void			RegisterConCommand( convar *pCommandBase ) = 0;
    virtual void			UnregisterConCommand( convar *pCommandBase ) = 0;
    virtual void			func13() = 0;
    virtual convar			*find_var( const char *var_name ) = 0;
    virtual void			func15() = 0;
    virtual void			func16() = 0;
    virtual void			func17() = 0;
    virtual void			func18() = 0;
    virtual void			func19() = 0;
    virtual void			func20() = 0;
};