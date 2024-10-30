#include "GameObjects.hpp"
#include "Bindings/RigidBodyBinding.hpp"
#include "BindingSystem.hpp"


class RigidBody;

void RigidBodyBinding::Bind()
{
	mono_add_internal_call("SageEngine.RigidBody::Set_Velocity_Internal", reinterpret_cast<const void*>(Set_Velocity));
	mono_add_internal_call("SageEngine.RigidBody::Set_Gravity_Internal", reinterpret_cast<const void*>(Set_Gravity));

	mono_add_internal_call("SageEngine.RigidBody::Get_Velocity_Internal", reinterpret_cast<const void*>(Get_Velocity));
	mono_add_internal_call("SageEngine.RigidBody::Get_Gravity_Internal", reinterpret_cast<const void*>(Get_Gravity));

	mono_add_internal_call("SageEngine.RigidBody::Set_Mass_Internal", reinterpret_cast<const void*>(Set_Mass));
	mono_add_internal_call("SageEngine.RigidBody::Get_Mass_Internal", reinterpret_cast<const void*>(Get_Mass));

	mono_add_internal_call("SageEngine.RigidBody::Set_Enable_Gravity", reinterpret_cast<const void*>(Set_Gravity_On));

	mono_add_internal_call("SageEngine.RigidBody::Add_Force_Internal", reinterpret_cast<const void*>(Add_Force));

}



void RigidBodyBinding::Set_Velocity(MonoObject* obj, BindingStruct::CSVector2D* velocity)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	// Get Rigidbody Component
	RigidBody* rigidBody = entity->Get_Component<RigidBody>();
	if (!rigidBody) return;
	// Get the velocity
	rigidBody->Get_Current_Velocity().x = velocity->x;
	rigidBody->Get_Current_Velocity().y = velocity->y;
}

void RigidBodyBinding::Get_Velocity(MonoObject* obj, BindingStruct::CSVector2D* out_obj)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	// Get Rigidbody Component
	RigidBody* rigidBody = entity->Get_Component<RigidBody>();
	if (!rigidBody) return;
	// Get the velocity
	out_obj->x = rigidBody->Get_Current_Velocity().x;
	out_obj->y = rigidBody->Get_Current_Velocity().y;
}


void RigidBodyBinding::Set_Mass(MonoObject* obj, float mass)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	// Get Rigidbody Component
	RigidBody* rigidBody = entity->Get_Component<RigidBody>();
	if (!rigidBody) return;
	// Set the mass
	rigidBody->Set_Mass(mass);
}

float RigidBodyBinding::Get_Mass(MonoObject* obj)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return 0;
	// Get Rigidbody Component
	RigidBody* rigidBody = entity->Get_Component<RigidBody>();
	if (!rigidBody) return 0;
	// Get the mass
	return rigidBody->Get_Mass();

}

void RigidBodyBinding::Get_Gravity(MonoObject* obj, BindingStruct::CSVector2D* out_obj)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	// Get Rigidbody Component
	RigidBody* rigidBody = entity->Get_Component<RigidBody>();
	if (!rigidBody) return;
	// Get the gravity
	ToastBox::Vec2 gravity = rigidBody->Get_Gravity();
	out_obj->x = gravity.x;
	out_obj->y = gravity.y;
}

void RigidBodyBinding::Set_Gravity(MonoObject* obj, BindingStruct::CSVector2D* gravity)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	// Get Rigidbody Component
	RigidBody* rigidBody = entity->Get_Component<RigidBody>();
	if (!rigidBody) return;
	// Set the gravity
	rigidBody->Set_Gravity({ gravity->x,gravity->y });
}


void RigidBodyBinding::Set_Gravity_On(MonoObject* obj, MonoBoolean gravity_on)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	// Get Rigidbody Component
	RigidBody* rigidBody = entity->Get_Component<RigidBody>();
	if (!rigidBody) return;
	// Set the gravity
	rigidBody->Set_Gravity_Disable(!gravity_on);
}

void RigidBodyBinding::Add_Force(MonoObject* obj, BindingStruct::CSVector2D* force, MonoObject* forceModeType)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	if (!entity) return;
	int forceAsInt = *(reinterpret_cast<int*>(mono_object_unbox(forceModeType)));
	RigidBody* rigidBody = entity->Get_Component<RigidBody>();
	if (!rigidBody) return;

	rigidBody->AddForce({ force->x,force->y }, static_cast<RigidBody::ForceMode>(forceAsInt));
}








