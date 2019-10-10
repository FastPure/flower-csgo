#pragma once

#define pi		3.14159265358979323846f
#define deg_2_rad (x)  ((float)(x) * (float)(pi / 180.f))

typedef float matrix_divided[ 3 ][ 4 ];

typedef float vec_t;

class vector
{
public:

    float x , y , z;

    vector( float x = 0 , float y = 0 , float z = 0 )
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
     
    vector operator + ( const vector& In ) const
    {
        return vector( x + In.x , y + In.y , z + In.z );
    }

    vector operator - ( const vector& In ) const
    {
        return vector( x - In.x , y - In.y , z - In.z );
    }

    vector operator * ( const vector& In )
    {
        return vector( x * In.x , y * In.y , z * In.z );
    }

    vector operator / ( const vector& In )
    {
        return vector( x / In.x , y / In.y , z / In.z );
    }

    vector operator -= ( const vector& In )
    {
        this->x -= In.x;
        this->y -= In.y;
        this->z -= In.z;

        return *this;
    }

    vector operator += ( const vector& In )
    {
        this->x += In.x;
        this->y += In.y;
        this->z += In.z;

        return *this;
    }

    vector operator *= ( const vector& In )
    {
        this->x *= In.x;
        this->y *= In.y;
        this->z *= In.z;

        return *this;
    }

    vector &operator/=( const vector &v )
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    bool operator!=( const vector &src ) const
    {
        return ( src.x != x ) || ( src.y != y ) || ( src.z != z );
    }

    bool operator==( const vector &src ) const
    {
        return ( src.x == x ) && ( src.y == y ) && ( src.z == z );
    }


    inline vec_t& operator[]( int i )
    {
        return ( ( vec_t* ) this )[ i ];
    }

    inline vec_t operator[]( int i ) const
    {
        return ( ( vec_t* ) this )[ i ];
    }

    void init( float ix = 0.0f , float iy = 0.0f , float iz = 0.0f )
    {
        x = ix; y = iy; z = iz;
    }

    inline void zero()
    {
        x = y = z = 0.0f;
    }

    float dot( const vector &vOther ) const
    {
        return ( x*vOther.x + y * vOther.y + z * vOther.z );
    }

    float lenght() const
    {
        return sqrt( x*x + y * y + z * z );
    }

    float lenght_2d() const
    {
        return sqrt( x*x + y * y );
    }

    float lenght_sqr( void ) const
    {
        return ( x*x + y * y + z * z );
    }

    vec_t* base()
    {
        return ( vec_t* ) this;
    }

    vec_t const* base() const
    {
        return ( vec_t const* ) this;
    }
};

namespace vector_extras
{
    void vector_copy( const vector& src , vector& dst )
    {
        dst.x = src.x;
        dst.y = src.y;
        dst.z = src.z;
    }
}
