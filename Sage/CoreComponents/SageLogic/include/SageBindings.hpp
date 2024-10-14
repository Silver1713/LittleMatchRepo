#ifndef SAGE_BINDINGS_HPP
#define SAGE_BINDINGS_HPP
#include <mono/metadata/loader.h>

struct SageBindings
{
	template <typename FuncPtr>
	static void Add_Internal_Call(const char* _csname, FuncPtr _bindings_func);
	
};

template <typename FuncPtr>
void SageBindings::Add_Internal_Call(const char* _csname, FuncPtr _bindings_func)
{
	mono_add_internal_call(_csname, _bindings_func);
}


#endif