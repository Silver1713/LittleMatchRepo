#ifndef GAMEOBJECTBINDING_HPP
#define GAMEOBJECTBINDING_HPP
#include "Binding.hpp"

class GameObjectBinding : public Binding
{
public:
	void Bind() override;
	void Bind(GameObject* object) override;
	void Unbind() override;

	MonoString* getName(MonoObject* obj);
	MonoBoolean getActive(MonoObject* obj);

	void Add_Component(MonoObject* obj, MonoObject* component);
	MonoObject* Get_Component(MonoObject* obj, MonoReflectionType* component_name);

	~GameObjectBinding() override = default;
};


#endif