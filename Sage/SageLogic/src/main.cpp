#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <iostream>
#include <chrono>
#include "SageScriptCompiler.hpp"
MonoDomain* domain;
char const* domain_name = "Environment.exe";
int main(){
	// Get Start time
	auto start = std::chrono::high_resolution_clock::now();
	
	SageAssembler assembler{};
	assembler.Init("..\\MONO\\bin\\", "..\\SageLogic\\programs");

	assembler.Set_Command("mcs");
	assembler.Set_Compile_Flags("/target:exe");

	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/abc.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/hello.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/abc1.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/hello1.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/abc2.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/hello2.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/abc3.cs");
	assembler.Add_Script(SageAssembler::FILE_MODE, "../SageLogic/scripts/hello3.cs");
	assembler.StartCompilation();
	std::cout << "Compiling C# Code...\n";
	assembler.Wait_For_Compile();
	std::cout << "C# code compiled successfully\n";
	mono_set_dirs("../MONO/lib", "../MONO/etc");
	domain = mono_jit_init(domain_name);
	//load assembly
	MonoAssembly* assembly = mono_domain_assembly_open(domain, assembler.Get_Assembly("abc").path_to_assembly.c_str());
	if (!assembly) {
		printf("Failed to open assembly\n");
		return 1;
	}
	MonoImage* image = mono_assembly_get_image(assembly);
	MonoMethodDesc* desc = mono_method_desc_new("Program:Main(string[])", 0);
	MonoMethod* method = mono_method_desc_search_in_image(desc, image);
	
	if (!method) {
		printf("Failed to find method\n");
		return 1;
	}

	MonoClass* string_class = mono_get_string_class();
	MonoArray* args_array = mono_array_new(domain, string_class, 0);

	
	char* argv[1] = { new char[] {"Hello"}};

	mono_runtime_invoke(method, nullptr, (void**) args_array, nullptr);

	mono_method_desc_free(desc);

	std::cout << "C# code executed successfully\n";
	mono_jit_cleanup(domain);
	delete[] argv[0];

	// get elapsed time
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << "s\n";
	return 0;

	
}