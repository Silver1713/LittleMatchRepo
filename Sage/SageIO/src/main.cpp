#include "PNG_Container.hpp"
#include "SageJSON.hpp"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
//#define STB_IMAGE_IMPLEMENTATION
const char* image = "../SageIO/image/image_asset.png";
const char* data = "../SageIO/data/test_data.json";
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SageJSON::SageJSON json{ data };
	json.close();
	
    return 0;
}