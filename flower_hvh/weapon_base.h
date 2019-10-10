#pragma once

class weapon_struct
{
public:
    char __pad0[ 0x14 ];
    int max_clip;
    char __pad1[ 0xC ];
    int max_reserved_ammo;
    char __pad2[ 0x60 ];
    char *hud_name;
    char *weapon_name;
    char __pad3[ 0x38 ];
    int type;
    char __pad4[ 0x4 ];
    int price;
    int reward;
    char __pad5[ 0x14 ];
    uint8_t full_auto;
    char __pad6[ 0x3 ];
    int damage;
    float armor_ratio;
    int bullets;
    float penetration;
    char __pad7[ 0x8 ];
    float range;
    float range_modifier;
    float throw_velocity;
    char __pad8[ 0xC ];
    uint8_t silencer;
    char __pad9[ 0xF ];
    float max_speed;
    float max_speed_alt;
    char __pad10[ 0x4C ];
    int recoil_seed;
    char __pad11[ 0x20 ];
};

class wep_system
{
    virtual void unused0() = 0;
    virtual void unused1() = 0;
public:
    virtual const weapon_struct *get_wep_data( unsigned int ItemDefinitionIndex ) = 0;
};

class weapon_base 
{
public:
    HANDLE get_handle()
    {
        return *( HANDLE* ) ( ( uintptr_t ) this + 0x14C );
    }
};
