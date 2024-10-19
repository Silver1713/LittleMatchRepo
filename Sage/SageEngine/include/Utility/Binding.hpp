#ifndef BINDING_HPP
#define BINDING_HPP
#include <mono/metadata/object.h>

class GameObject;

class Binding
{
public:
	virtual void Bind() = 0;
	virtual void Bind(GameObject* object);
	virtual void Unbind() = 0;
	virtual ~Binding() = default;
};



class GameObjectBinding : public Binding
{
public:
	void Bind() override;
	void Bind( GameObject* object) override;
	void Unbind() override;

	MonoString* getName(MonoObject* obj);
	MonoBoolean getActive(MonoObject* obj);

	void Add_Component(MonoObject* obj, MonoObject* component);
	MonoObject* Get_Component(MonoObject* obj, MonoReflectionType* component_name);

	~GameObjectBinding() override = default;
};

class TransformBinding : public Binding
{
public:
	void Bind() override;
	void Bind(GameObject* object) override;
	void Unbind() override;

	MonoObject* getPosition(MonoObject* obj);
	MonoObject* getRotation(MonoObject* obj);
	MonoObject* getScale(MonoObject* obj);

	void setPosition(MonoObject* obj, MonoObject* position);
	void setRotation(MonoObject* obj, MonoObject* rotation);
	void setScale(MonoObject* obj, MonoObject* scale);

	~TransformBinding() override = default;
};


#endif