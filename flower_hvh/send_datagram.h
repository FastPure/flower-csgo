#pragma once
namespace send_datagram
{
    using prototype_send_datagram = int( __thiscall* )( void* , void* );
    prototype_send_datagram original_send_datagram = nullptr;

    std::unique_ptr<vmt_hook> send_datagram;

    static bool hooked = false;

    int __fastcall hook_send_datagram( net_channel * net_channel , void* , bf_write* datagram )
    {
        int instate = net_channel->state;
        int insequencenr = net_channel->sequence_number;

        if ( globals::functions::move::backtrack_types == 2 )
            net_channel->sequence_number += 2 * NET_FRAMES_MASK -
                static_cast< uint32_t >( NET_FRAMES_MASK * 0.1 );

        int ret = original_send_datagram( net_channel , datagram );

        net_channel->state = instate;
        net_channel->sequence_number = insequencenr;

        return ret;
    }
}