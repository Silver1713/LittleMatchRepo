#include "PNG_Container.hpp"
#include "SageJSON.hpp"
#include <crtdbg.h>
#include <chrono>
#define _CRTDBG_MAP_ALLOC
//#define STB_IMAGE_IMPLEMENTATION
const char* image = "../SageIO/image/image_asset.png";
const char* data = "../SageIO/data/test_data.json";
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
int main()
{
	//Execution time
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SageJSON::SageJSON json{ data };

	auto v = json["bio"];

	std::cout << v.as<std::string>() << std::endl;
	json.close();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::cout << "Execution time: " << elapsed_time << " ms" << std::endl;
	
    return 0;
}