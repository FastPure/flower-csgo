namespace glow_sytles
{
    uint32_t regular = 0 , hot = 1 , outline = 2;

    namespace sizes
    {
        float pixel = 0.45 , fit = 0.65 , medium = 0.8 , fat = 1;
    }
}

class glow_manager
{
public:

    class glow_definition
    {
    public:

        class csplayer * entity;
        union
        {
            vector colors;         
            struct
            {
                float   r;           
                float   g;         
                float   b;          
            };
        };

        float a;
        uint8_t pad_1[ 4 ];
        float unk_1;
        uint8_t pad_2[ 4 ];
        float unk_2;
        bool occluded;
        bool unoccluded;
        bool full_bloom;
        uint8_t pad_3[ 5 ];
        int32_t style;
        int32_t slipt;
        int32_t free;

        bool unused() const
        {
            return free != glow_definition::in_use;
        }

        static const int end_free = -1;
        static const int in_use = -2;
    };

    glow_definition *glow_def_;
    int max_size;
    int pad;
    int size;
    glow_definition *unk_4;
    int	current_objects;
};
