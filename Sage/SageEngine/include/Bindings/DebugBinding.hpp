#ifndef DEBUG_BINDING_HPP
#define DEBUG_BINDING_HPP
#include "GameObjectBinding.hpp"
#include "SageMonoManager.hpp"

struct DebugBinding
{

	static void PrintLine(MonoString* value);
	static void WarnLine(MonoString* value);
	static void ErrorLine(MonoString* value);

	static SageMonoManager::STDOUTCS& Get_Output_Stream_CS();
	static SageMonoManager::STDERRCS& Get_Error_Stream_CS();
public:
	static void Bind();


};


#endif