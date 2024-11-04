#ifndef SAGE_PHYSICS_SYSTEM_HPP
#define SAGE_PHYSICS_SYSTEM_HPP
#include "Matrix4x4.h"
#include "System.hpp"
class GameObject;
class RigidBody;
class SagePhysicsSystem : public System
{
	void Apply_Gravity(RigidBody* _component);

public:

	SagePhysicsSystem();	
	void Init() override;
	void Init_Entity(GameObject* _entity) override;
	void Update() override;
	void Update_Entity(GameObject* _entity) override;
	void Exit() override;
	SystemType GetInstance() override;
	~SagePhysicsSystem() override;

	void Add_Force_Entity(RigidBody* _entity, const ToastBox::Vec2& force, int force_mode);
	
};


#endif