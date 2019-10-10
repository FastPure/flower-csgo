#pragma once

class vmt_hook
{
public:
    vmt_hook( void*** class_ );
    ~vmt_hook();

    template <typename T>
    T hook( size_t index , void* new_ );

private:
    size_t get_func_number() const;
    void dispose() const;

    void*** m_class;
    void** m_originalTable;
    void** m_replaceTable;
    size_t m_functionNumber;
};

template <typename T>
T vmt_hook::hook( size_t index , void* new_ )
{
    m_replaceTable[ index ] = new_;
    return ( T ) m_originalTable[ index ];
}

vmt_hook::vmt_hook( void*** class_ )
{
    if ( !class_ )
        dispose();

    m_class = class_;

    if ( !*m_class )
        dispose();

    m_originalTable = *m_class;
    m_functionNumber = get_func_number();

    if ( m_functionNumber <= 0 )
        dispose();

    m_replaceTable = new void*[ m_functionNumber ];

    if ( !m_replaceTable )
        dispose();

    memcpy_s( m_replaceTable , sizeof( void* ) * m_functionNumber , m_originalTable , sizeof( void* ) * m_functionNumber );

    *m_class = m_replaceTable;
}

vmt_hook::~vmt_hook()
{
    if ( *m_class == m_replaceTable )
        *m_class = m_originalTable;

    if ( m_replaceTable )
    {
        delete m_replaceTable;
        m_replaceTable = nullptr;
    }
}

size_t vmt_hook::get_func_number() const
{
    size_t counter = 0;
    while ( m_originalTable[ counter ] )
        counter++;

    return counter;
}

void vmt_hook::dispose() const
{
    if ( *m_class == m_replaceTable )
        *m_class = m_originalTable;

    if ( m_replaceTable )
    {
        delete m_replaceTable;
        m_replaceTable;
    }

    delete this;
}