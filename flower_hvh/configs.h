#pragma once
namespace configs
{
	//ur config here
    std::string config_patch_txt = "C:\\flower_hvh\\legit.txt";

    auto init()
    {
        if ( CreateDirectory( "C:\\flower_hvh" , NULL ) )
        {

        }
    }
}