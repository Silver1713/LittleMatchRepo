
#include "SageJSON.hpp"
#include <fstream>
#include <crtdbg.h>
#include <chrono>

#define _CRTDBG_MAP_ALLOC
//#define STB_IMAGE_IMPLEMENTATION
const char* image = "../SageIO/image/image_asset.png";
const char* data = "../SageIO/data/test_data.json";
const char* output = "../SageIO/data/output.json";
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
using JSON = SageJSON::SageJSON;
int main()
{
	//Execution time
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SageJSON::SageJSON json{};

	std::ifstream file(data);

	if (!file)
		return 1;

	while (!file.eof())
	{
		file >> json;
		
		/*std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		
		double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

		std::cout << "Execution time: " << elapsed_time << " ms" << std::endl;*/
	}


	
	
		std::cout << json["Nested"]["BoolArray"][2].as<JSON::NumberValue>() << std::endl;
	

	


	
	json.close();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::cout << "Execution time: " << elapsed_time << " ms" << std::endl;
	
    return 0;
}