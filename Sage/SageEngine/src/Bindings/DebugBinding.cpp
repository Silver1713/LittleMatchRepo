#include "Bindings/DebugBinding.hpp"

#include <iostream>


void DebugBinding::Bind()
{
	mono_add_internal_call("SageEngine.Debug.SageDebug::PrintInternal", reinterpret_cast<const void*>(PrintLine));
	mono_add_internal_call("SageEngine.Debug.SageDebug::WarnInternal", reinterpret_cast<const void*>(WarnLine));
	mono_add_internal_call("SageEngine.Debug.SageDebug::ErrorInternal", reinterpret_cast<const void*>(ErrorLine));
}


void DebugBinding::PrintLine(MonoString* value)
{
	SageMonoManager::STDOUTCS& output_stream = Get_Output_Stream_CS();

	const char* str = mono_string_to_utf8(value);
	std::string full = "[INFO] " + std::string(str);

	output_stream.Add(full.c_str());
	std::cout << full << '\n';
}

void DebugBinding::WarnLine( MonoString* value)
{
	SageMonoManager::STDOUTCS& output_stream = Get_Output_Stream_CS();

	const char* str = mono_string_to_utf8(value);
	std::string full = "[WARN] " + std::string(str);
	output_stream.Add(full.c_str());
	std::cout << full << '\n';
}


void DebugBinding::ErrorLine( MonoString* value)
{
	SageMonoManager::STDERRCS& error_stream = Get_Error_Stream_CS();

	const char* str = mono_string_to_utf8(value);
	std::string full = "[ERROR] " + std::string(str);
	error_stream.Add(full.c_str());
	std::cerr << full << '\n';
}


SageMonoManager::STDERRCS& DebugBinding::Get_Error_Stream_CS()
{
	return SageMonoManager::error_stream;
}


SageMonoManager::STDOUTCS& DebugBinding::Get_Output_Stream_CS()
{
	return SageMonoManager::output_stream;
}
