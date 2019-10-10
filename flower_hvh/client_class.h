#pragma once
class client_mode
{
public:

};

struct recv_table
{
};

class client_class
{
public:
    void*			create_fn;
    void*			create_event;
    char			*network_name;
    recv_table		*recv_table;
    client_class	*next;
    int				class_id;
};
