#pragma once

#include <cstdint>

#define NET_FRAMES_BACKUP	64		// must be power of 2
#define NET_FRAMES_MASK		(NET_FRAMES_BACKUP-1)

typedef enum
{
    NA_NULL = 0 ,
    NA_LOOPBACK ,
    NA_BROADCAST ,
    NA_IP ,
} netadrtype_t;

typedef struct netadr_s
{
public:
    netadrtype_t	type;
    unsigned char	ip[ 4 ];
    unsigned short	port;
} netadr_t;

class INetMessageBinder;
class IDemoRecorder;
class INetMessage;
class INetChannelHandler;
class bf_write;


class INetChannelInfo
{
public:

    enum
    {
        GENERIC = 0 ,	// must be first and is default group
        LOCALPLAYER ,	// bytes for local player entity update
        OTHERPLAYERS ,	// bytes for other players update
        ENTITIES ,		// all other entity bytes
        SOUNDS ,			// game sounds
        EVENTS ,			// event messages
        TEMPENTS ,		// temp entities
        USERMESSAGES ,	// user messages
        ENTMESSAGES ,	// entity messages
        VOICE ,			// voice data
        STRINGTABLE ,	// a stringtable update
        MOVE ,			// client move cmds
        STRINGCMD ,		// string command
        SIGNON ,			// various signondata
        TOTAL ,			// must be last and is not a real group
    };

    virtual const char  *GetName( void ) const = 0;	// get channel name
    virtual const char  *GetAddress( void ) const = 0; // get channel IP address as string
    virtual float		GetTime( void ) const = 0;	// current net time
    virtual float		GetTimeConnected( void ) const = 0;	// get connection time in seconds
    virtual int			GetBufferSize( void ) const = 0;	// netchannel packet history size
    virtual int			GetDataRate( void ) const = 0; // send data rate in byte/sec

    virtual bool		IsLoopback( void ) const = 0;	// true if loopback channel
    virtual bool		IsTimingOut( void ) const = 0;	// true if timing out
    virtual bool		IsPlayback( void ) const = 0;	// true if demo playback

    virtual float		GetLatency( int flow ) const = 0;	 // current latency (RTT), more accurate but jittering
    virtual float		GetAvgLatency( int flow ) const = 0; // average packet latency in seconds
    virtual float		GetAvgLoss( int flow ) const = 0;	 // avg packet loss[0..1]
    virtual float		GetAvgChoke( int flow ) const = 0;	 // avg packet choke[0..1]
    virtual float		GetAvgData( int flow ) const = 0;	 // data flow in bytes/sec
    virtual float		GetAvgPackets( int flow ) const = 0; // avg packets/sec
    virtual int			GetTotalData( int flow ) const = 0;	 // total flow in/out in bytes
    virtual int			GetTotalPackets( int flow ) const = 0;
    virtual int			GetSequenceNr( int flow ) const = 0;	// last send seq number
    virtual bool		IsValidPacket( int flow , int frame_number ) const = 0; // true if packet was not lost/dropped/chocked/flushed
    virtual float		GetPacketTime( int flow , int frame_number ) const = 0; // time when packet was send
    virtual int			GetPacketBytes( int flow , int frame_number , int group ) const = 0; // group size of this packet
    virtual bool		GetStreamProgress( int flow , int *received , int *total ) const = 0;  // TCP progress if transmitting
    virtual float		GetTimeSinceLastReceived( void ) const = 0;	// get time since last recieved packet in seconds
    virtual	float		GetCommandInterpolationAmount( int flow , int frame_number ) const = 0;
    virtual void		GetPacketResponseLatency( int flow , int frame_number , int *pnLatencyMsecs , int *pnChoke ) const = 0;
    virtual void		GetRemoteFramerate( float *pflFrameTime , float *pflFrameTimeStdDeviation ) const = 0;

    virtual float		GetTimeoutSeconds() const = 0;
};

class net_channel
{
public:
    __int32 vtable; //0x0000 
    INetMessageBinder* msgbinder1; //0x0004 
    INetMessageBinder* msgbinder2; //0x0008 
    INetMessageBinder* msgbinder3; //0x000C 
    INetMessageBinder* msgbinder4; //0x0010 
    unsigned char m_bProcessingMessages; //0x0014 
    unsigned char m_bShouldDelete; //0x0015 
    char pad_0x0016[ 0x2 ]; //0x0016
    __int32 m_nOutSequenceNr; //0x0018 
    __int32 sequence_number; //0x001C 
    __int32 m_nOutSequenceNrAck; //0x0020 
    __int32 m_nOutReliableState; //0x0024 
    __int32 state; //0x0028 
    __int32 m_nChokedPackets; //0x002C 

    void* m_StreamReliable; //0x0030 
    /*CUtlMemory*/ char m_ReliableDataBuffer[ 12 ]; //0x0048 
    void* m_StreamUnreliable; //0x0054 
    /*CUtlMemory*/ char m_UnreliableDataBuffer[ 12 ]; //0x006C 
    void* m_StreamVoice; //0x0078 
    /*CUtlMemory*/char m_VoiceDataBuffer[ 12 ]; //0x0090 
    __int32 m_Socket; //0x009C 
    __int32 m_StreamSocket; //0x00A0 
    __int32 m_MaxReliablePayloadSize; //0x00A4 
    char pad_0x00A8[ 0x4 ]; //0x00A8
    netadr_t remote_address; //0x00AC 
    char dylanpadding[ 84 ]; //padding added by dylan
    float last_received; //0x00B8  //dylan found 0x10c
                         //char pad_0x00BC[0x4]; //0x00BC
    double /*float*/ connect_time; //0x00C0 //dylan found 0x110
                                   //char pad_0x00C4[0x4]; //0x00C4
    __int32 m_Rate; //0x00C8  //dylan found 0x118
    /*float*/double m_fClearTime; //0x00CC  //dylan found 0x120
    char pad_0x00D0[ 0x8 ]; //0x00D0
    char m_WaitingList[ 48 ];
    //CUtlVector m_WaitingList[0]; //0x00D8 
    //CUtlVector m_WaitingList[1]; //0x00EC 
    //char pad_0x0100[0x4120]; //0x0100
    char pad_0x0100[ 0x40F0 ]; //dylan changed
    __int32 m_PacketDrop; //0x4220  //dylan found 0x4250
    char m_Name[ 32 ]; //0x4224 
    __int32 m_ChallengeNr; //0x4244 
    float m_Timeout; //0x4248 //dylan found 0x4278
    INetChannelHandler* m_MessageHandler; //0x424C 
    /*CUtlVector*/char m_NetMessages[ 14 ]; //0x4250 
    __int32 dylanUnknown;
    void* m_pDemoRecorder; //0x4264 
    __int32 m_nQueuedPackets; //0x4268  //dylan found 0x4298
    float m_flInterpolationAmount; //0x426C //dylan found 0x429c
    float m_flRemoteFrameTime; //0x4270 //dylan found 0x42a0
    float m_flRemoteFrameTimeStdDeviation; //0x4274  //dylan found 0x42a4
    float m_flRemoteFrameTimeUnknown; //dylan found 0x42a8
    __int32 m_nMaxRoutablePayloadSize; //0x4278  //dylan found 0x42ac
    __int32 m_nSplitPacketSequence; //0x427C  //dylan found 0x42b0
    char pad_0x4280[ 0x14 ]; //0x4280


    bool Transmit( bool a );
};//Size=0x4294

class CEventInfo
{
public:

    uint16_t classID; //0x0000 0 implies not in use
    char pad_0002[ 2 ]; //0x0002 
    float fire_delay; //0x0004 If non-zero, the delay time when the event should be fired ( fixed up on the client )
    char pad_0008[ 4 ]; //0x0008
    client_class *pClientClass; //0x000C
    void *pData; //0x0010 Raw event data
    char pad_0014[ 48 ]; //0x0014
}; //Size: 0x0044

class CClockDriftMgr
{
public:
    float m_ClockOffsets[ 16 ];   //0x0000
    uint32_t m_iCurClockOffset; //0x0044
    uint32_t m_nServerTick;     //0x0048
    uint32_t m_nClientTick;     //0x004C
}; //Size: 0x0050

class client_state
{

public:

    void ForceFullUpdate()
    {
        m_nDeltaTick = -1;
    }

    char pad_0000[ 156 ];				//0x0000
    net_channel *m_NetChannel;		//0x009C
    uint32_t m_nChallengeNr;		//0x00A0
    char pad_00A4[ 100 ];				//0x00A4
    uint32_t m_nSignonState;		//0x0108
    char pad_010C[ 8 ];				//0x010C
    float m_flNextCmdTime;			//0x0114
    uint32_t m_nServerCount;		//0x0118
    uint32_t m_nCurrentSequence;	//0x011C
    char pad_0120[ 8 ];               //0x0120
    CClockDriftMgr m_ClockDriftMgr; //0x0128
    uint32_t m_nDeltaTick;          //0x0178
    bool m_bPaused;                 //0x017C
    char pad_017D[ 3 ];               //0x017D
    uint32_t m_nViewEntity;			//0x0180
    uint32_t m_nPlayerSlot;			//0x0184
    char m_szLevelName[ 260 ];		//0x0188
    char m_szLevelNameShort[ 40 ];	//0x028C
    char m_szGroupName[ 40 ];			//0x02B4
    char pad_02DC[ 52 ];				//0x02DC
    uint32_t m_nMaxClients;			//0x0310
    char pad_0314[ 18820 ];			//0x0314
    float m_flLastServerTickTime;	//0x4C98
    bool insimulation;				//0x4C9C
    char pad_4C9D[ 3 ];				//0x4C9D
    uint32_t oldtickcount;			//0x4CA0
    float m_tickRemainder;			//0x4CA4
    float m_frameTime;				//0x4CA8
    uint32_t lastoutgoingcommand;	//0x4CAC
    uint32_t chokedcommands;		//0x4CB0
    uint32_t last_command_ack;		//0x4CB4
    uint32_t command_ack;			//0x4CB8
    uint32_t m_nSoundSequence;		//0x4CBC
    char pad_4CC0[ 80 ];				//0x4CC0
    vector viewangles;				//0x4D10
    char pad_4D1C[ 208 ];				//0x4D1C
    CEventInfo *events;				//0x4DECf
}; //Size: 0x4E1C

class INetMessage
{

public:

    virtual ~INetMessage();
};

template<typename T>
class CNetMessagePB : public INetMessage , public T
{
};

class CCLCMsg_Move
{

private:

    char __PAD0[ 0x8 ];

public:

    int numBackupCommands;
    int numNewCommands;
};

using CCLCMsg_Move_t = CNetMessagePB<CCLCMsg_Move>;