#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <iostream>
MonoDomain* domain;
char const* code = R"(
	using System;

class Program
{
    static void Main(string[] args)
    {
        string delimitedString = "H,e,l,l,o";
        char delimiter = ',';

        // Split the string by the delimiter
        string[] splitString = delimitedString.Split(delimiter);

        // Join the characters back into a single string without the delimiter
        string result = string.Join("", splitString);

        // Output the result
        Console.WriteLine(result); // Output: Hello
    }
}
)";
char const* domain_name = "HelloWorld.exe";
int main(){
	mono_set_dirs("../MONO/lib", "../MONO/etc");
	// RUn a mono HelloWorld.exe
	domain = mono_jit_init(domain_name);
	//load assembly
	MonoAssembly* assembly = mono_domain_assembly_open(domain, "../SageLogic/programs/hello.exe");
	
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
	// Create an empty string[] array to pass as arguments
	MonoClass* string_class = mono_get_string_class();
	MonoArray* args_array = mono_array_new(domain, string_class, 0);  // Empty string[]

	// Prepare arguments (args_array is passed as the arguments)
	
	
	// empty string array
	// C++
	char* argv[1] = { new char[] {"Hello"}};

	mono_runtime_invoke(method, nullptr, reinterpret_cast<void**>(argv), nullptr);

	mono_method_desc_free(desc);

	std::cout << "C# code executed successfully\n";
	mono_jit_cleanup(domain);
	//delete[] argv;
	return 0;

	
}