#ifndef BINDING_HPP
#define BINDING_HPP
#include <mono/metadata/object.h>

class GameObject;

class Binding
{
public: 
	enum class BindingType
	{
		BINDINGS_BASE,
		BINDINGS_GAMEOBJECT,
		BINDINGS_TRANSFORM,
		BINDINGS_TOTAL
	};
	virtual void Bind() = 0;
	virtual void Bind(GameObject* object) = 0;
	virtual void Unbind() = 0;
	virtual ~Binding() = default;


	virtual BindingType GetType();


};






#endif