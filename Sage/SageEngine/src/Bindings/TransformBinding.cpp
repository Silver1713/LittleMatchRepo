#include "Bindings/TransformBinding.hpp"

#include <mono/metadata/appdomain.h>

#include "BindingSystem.hpp"
#include "GameObjects.hpp"

void TransformBinding::Bind()
{
	mono_add_internal_call("SageEngine.Transform::getPosition", TransformBinding::getPosition);
	mono_add_internal_call("SageEngine.Transform::getRotation", TransformBinding::getRotation);
	mono_add_internal_call("SageEngine.Transform::getScale", TransformBinding::getScale);

	mono_add_internal_call("SageEngine.Transform::setPosition", TransformBinding::setPosition);
	mono_add_internal_call("SageEngine.Transform::setRotation", TransformBinding::setRotation);
	mono_add_internal_call("SageEngine.Transform::setScale", TransformBinding::setScale);

}

MonoObject* nVector2D;

void TransformBinding::Unbind()
{
	
}

void TransformBinding::getPosition(MonoObject* obj, BindingStruct::CSVector2D* out)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	//Get Vector2D class
	SageMonoManager::MonoKlassInfo* klassInfo = SageMonoManager::Get_Klass_Info("Vector2D", "SageEngine.Math");
	if (!klassInfo || !klassInfo->klass) return;
	// Create a shadow object
	BindingStruct::CSVector2D vector{};
	
	


	// Get Transform Component
	Transform* transform = entity->Get_Component<Transform>();
	if (!transform) return;

	// Get the position
	ToastBox::Vec3 position = transform->Get_Position();
	
	out->x = position.x;
	out->y = position.y;
}

float TransformBinding::getRotation(MonoObject* obj)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return 0;
	// Get Transform Component
	Transform* transform = entity->Get_Component<Transform>();
	if (!transform) return 0;
	// Get the rotation
	return transform->Get_Rotation().x;
}

MonoObject* TransformBinding::getScale(MonoObject* obj)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return nullptr;
	//Get Vector2D class
	SageMonoManager::MonoKlassInfo* klassInfo = SageMonoManager::Get_Klass_Info("Vector2D", "SageEngine.Math");
	if (!klassInfo || !klassInfo->klass) return {};
	// Create a shadow object
	BindingStruct::CSVector2D vector{};

	// Get Transform Component
	Transform* transform = entity->Get_Component<Transform>();
	if (!transform) return {};

	
	// Get the position
	ToastBox::Vec3 scale = transform->Get_Scale();
	vector.x = scale.x;
	vector.y = scale.y;

	//Box the object
	MonoObject* boxed = SageMonoManager::Box_Value(SageMonoManager::Get_Default_Domain(), klassInfo->klass, &vector);
	return boxed;
}

void TransformBinding::setPosition(MonoObject* obj, BindingStruct::CSVector2D* position)
{
	std::string name = mono_class_get_name(mono_object_get_class(obj));
	if (!position) return;
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	//Get Vector2D class
	SageMonoManager::MonoKlassInfo* klassInfo = SageMonoManager::Get_Klass_Info("Vector2D", "SageEngine.Math");
	if (!klassInfo || !klassInfo->klass) return;

	// Get Transform Component
	Transform* transform = entity->Get_Component<Transform>();
	if (!transform) return;

	// Set the position
	transform->Set_Position({ position->x,position->y, 0.0f });

	
}

void TransformBinding::setRotation(MonoObject* obj, MonoObject* rotation)
{
	return;
}

void TransformBinding::setScale(MonoObject* obj, MonoObject* scale)
{
	return;
}






