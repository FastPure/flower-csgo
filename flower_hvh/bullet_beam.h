#pragma once
class beam;
class beam_t;

enum
{
    TE_BEAMPOINTS = 0x00 ,		
    TE_SPRITE = 0x01 ,	
    TE_BEAMCYLINDER = 0x03 ,		
    TE_BEAMFOLLOW = 0x04 ,		
    TE_BEAMRING = 0x05 ,		
    TE_BEAMSPLINE = 0x06 ,
    TE_BEAMRINGPOINT = 0x07 ,
    TE_BEAMLASER = 0x08 ,		
    TE_BEAMTESLA = 0x09 ,
};


struct beam_info
{
    int			type;

    csplayer * m_pStartEnt;
    int			m_nStartAttachment;
    csplayer* m_pEndEnt;
    int			m_nEndAttachment;

    vector		start;
    vector		end;

    int			model_index;
    const char	*model_name;

    int			halo_index;
    const char	*halo_name;
    float		halo_scale;

    float		life;
    float		w;
    float		end_w;
    float		fade_lenght;
    float		amplitude;

    float		a;
    float		propagation_speed;

    int			start_frame;
    float		frame_rate;

    float		r;
    float		g;
    float		b;

    bool		renderable;

    int			segment;

    int			flags;

    vector		m_vecCenter;
    float		m_flStartRadius;
    float		m_flEndRadius;

    beam_info()
    {
        type = TE_BEAMPOINTS;
        segment = -1;
        model_name = NULL;
        halo_name = NULL;
        model_index = -1;
        halo_index = -1;
        renderable = true;
        flags = 0;
    }
};

class render_beams
{
public:
    render_beams( void );
    virtual				~render_beams( void );
public:
    virtual	void		InitBeams( void );
    virtual	void		ShutdownBeams( void );
    virtual	void		ClearBeams( void );

    virtual void		UpdateTempEntBeams();

    virtual void		draw_beam( beam_t *pbeam ); 
    virtual void		draw_beam( beam* pbeam , trace_filter *pEntityBeamTraceFilter = NULL );

    virtual	void		KillDeadBeams( csplayer *pDeadEntity );

    virtual	void		CreateBeamEnts( int startEnt , int endEnt , int modelIndex , int haloIndex , float haloScale ,
                                        float life , float width , float endWidth , float fadeLength , float amplitude ,
                                        float brightness , float speed , int startFrame ,
                                        float framerate , float r , float g , float b , int type = -1 );
    virtual beam_t		*CreateBeamEnts( beam_info &beamInfo );

    virtual	void		CreateBeamEntPoint( int	nStartEntity , const vector *pStart , int nEndEntity , const vector* pEnd ,
                                            int modelIndex , int haloIndex , float haloScale ,
                                            float life , float width , float endWidth , float fadeLength , float amplitude ,
                                            float brightness , float speed , int startFrame ,
                                            float framerate , float r , float g , float b );
    virtual beam_t		*CreateBeamEntPoint( beam_info &beamInfo );

    virtual	void		create_beam_points( vector& start , vector& end , int modelIndex , int haloIndex , float haloScale ,
                                          float life , float width , float endWidth , float fadeLength , float amplitude ,
                                          float brightness , float speed , int startFrame ,
                                          float framerate , float r , float g , float b );
    virtual	beam_t		*create_beam_points( beam_info &beamInfo );
};


class beam_infos
{
public:
    beam_infos( vector starts , vector positions , float times , int userids )
    {
        this->start = starts;
        this->position = positions;
        this->time = times;
        this->user_id = userids;
    }

    vector position;
    vector start;
    float time;
    int user_id;
};
std::vector<beam_infos> tracer_logs;




