#pragma once

class move_helper
{
private:
    virtual void unk() = 0;
public:
    virtual void set_host( csplayer * host ) = 0;
};


class game_movement
{
public:
    virtual			~game_movement( void )
    {
    }

    virtual void	ProcessMovement( csplayer *player , void *pMove ) = 0;
    virtual void	Reset( void ) = 0;
    virtual void	StartTrackPredictionErrors( csplayer *player ) = 0;
    virtual void	FinishTrackPredictionErrors( csplayer *player ) = 0;
    virtual void	DiffPrint( char const *fmt , ... ) = 0;

    virtual vector const&	GetPlayerMins( bool ducked ) const = 0;
    virtual vector const&	GetPlayerMaxs( bool ducked ) const = 0;
    virtual vector const&   GetPlayerViewOffset( bool ducked ) const = 0;

    virtual bool			IsMovingPlayerStuck( void ) const = 0;
    virtual csplayer*	GetMovingPlayer( void ) const = 0;
    virtual void			UnblockPusher( csplayer* player , csplayer * pusher ) = 0;

    virtual void SetupMovementBounds( void * move ) = 0;
};

class prediction
{
public:

    virtual ~prediction( void ) = 0;//

    virtual void Init( void ) = 0;//
    virtual void Shutdown( void ) = 0;//

                                    // Implement IPrediction
public:

    virtual void Update
    (
        int startframe , // World update ( un-modded ) most recently received
        bool validframe , // Is frame data valid
        int incoming_acknowledged , // Last command acknowledged to have been run by server (un-modded)
        int outgoing_command // Last command (most recent) sent to server (un-modded)
    );//

    virtual void PreEntityPacketReceived( int commands_acknowledged , int current_world_update_packet );//
    virtual void PostEntityPacketReceived( void );//5
    virtual void PostNetworkDataReceived( int commands_acknowledged );//

    virtual void OnReceivedUncompressedPacket( void );//

                                                    // The engine needs to be able to access a few predicted values
    virtual void GetViewOrigin( vector& org );//
    virtual void SetViewOrigin( vector& org );//
    virtual void GetViewAngles( vector& ang );//10
    virtual void SetViewAngles( vector& ang );//

    virtual void GetLocalViewAngles( vector& ang );//
    virtual void set_local_angles( vector& ang );//

    virtual bool InPrediction( void ) const;//14
    virtual bool IsFirstTimePredicted( void ) const;//

    virtual int GetLastAcknowledgedCommandNumber( void ) const;//

#if !defined( NO_ENTITY_PREDICTION )
    virtual int GetIncomingPacketNumber( void ) const;//
#endif

    virtual void CheckMovingGround( csplayer* player , double frametime );//
    virtual void RunCommand( csplayer* player , user_cmd* cmd , move_helper* moveHelper );//

    virtual void setup_move( csplayer* player , user_cmd* cmd , void* pHelper , void* move );//20
    virtual void finish_move( csplayer* player , user_cmd* cmd , void* move );//
    virtual void SetIdealPitch( int nSlot , csplayer* player , const vector& origin , const vector& angles , const vector& viewheight );//

    virtual void CheckError( int nSlot , csplayer* player , int commands_acknowledged );//

public:
    virtual void _Update
    (
        int nSlot ,
        bool received_new_world_update ,
        bool validframe ,            // Is frame data valid
        int incoming_acknowledged ,  // Last command acknowledged to have been run by server (un-modded)
        int outgoing_command        // Last command (most recent) sent to server (un-modded)
    );

    // Actually does the prediction work, returns false if an error occurred
    bool PerformPrediction( int nSlot , csplayer* localPlayer , bool received_new_world_update , int incoming_acknowledged , int outgoing_command );

    void ShiftIntermediateDataForward( int nSlot , int slots_to_remove , int previous_last_slot );

    void RestoreEntityToPredictedFrame( int nSlot , int predicted_frame );

    int ComputeFirstCommandToExecute( int nSlot , bool received_new_world_update , int incoming_acknowledged , int outgoing_command );

    void DumpEntity( csplayer* ent , int commands_acknowledged );

    void ShutdownPredictables( void );

    void ReinitPredictables( void );

    void RemoveStalePredictedEntities( int nSlot , int last_command_packet );

    void RestoreOriginalEntityState( int nSlot );

    void RunSimulation( int current_command , float curtime , user_cmd * cmd , csplayer* localPlayer );

    void Untouch( int nSlot );

    void StorePredictionResults( int nSlot , int predicted_frame );

    bool ShouldDumpEntity( csplayer * ent );

    void SmoothViewOnMovingPlatform( csplayer* pPlayer , vector& offset );

    void ResetSimulationTick();

    void ShowPredictionListEntry( int listRow , int showlist , csplayer* ent , int& totalsize , int& totalsize_intermediate );

    void FinishPredictionList( int listRow , int showlist , int totalsize , int totalsize_intermediate );

    void CheckPredictConvar();

};
BYTE bMoveData[ 200 ];