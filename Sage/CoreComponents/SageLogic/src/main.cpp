#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <iostream>
#include <chrono>
#include "SageScriptCompiler.hpp"
#include "SageScriptLoader.hpp"
SageLoader loader{};
int main(){
	// Get Start time
	auto start = std::chrono::high_resolution_clock::now();
	
	SageAssembler assembler{};
	assembler.Init("..\\MONO\\bin\\", "..\\CoreComponents\\SageLogic\\programs");

	assembler.Set_Command("mcs");
	assembler.Set_Compile_Flags("/target:library");

	assembler.Add_Script(SageAssembler::FILE_MODE, "../CoreComponents/SageLogic/scripts/abc.cs");
	/*assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/hello.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/abc1.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/hello1.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/abc2.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/hello2.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/abc3.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/hello3.cs");*/
	assembler.Add_Script(SageAssembler::FILE_MODE, "../CoreComponents/SageLogic/scripts/SageBehaviour.cs");
	assembler.StartCompilation(true);
	std::cout << "Compiling C# Code...\n";
	assembler.Wait_For_Compile();
	std::cout << "C# code compiled successfully\n";
	loader.Init("../MONO/lib", "../MONO/etc");

	loader.Load_Assembly("abc", "../CoreComponents/SageLogic/programs/SageLibrary.dll");
	

	std::cout << "Running Main @ abc.cs ...\n";
	std::cout << "---------------------\n";
	loader.Run_Main("abc");
	std::cout << "---------FIN----------\n";
	std::cout << "Running Main @ hello.cs ...\n";
	std::cout << "---------------------\n";
	loader.Run_Main("hello");
	std::cout << "---------FIN----------\n";

	loader.Exit();
	return 0;

	
}