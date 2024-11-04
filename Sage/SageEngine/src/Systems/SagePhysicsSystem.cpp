#include "Systems/SagePhysicsSystem.hpp"
#include "Components/RigidBody.hpp"
#include "GameObjects.hpp"
#include "SageProfiler.hpp"
#include "SageTimer.hpp"


SagePhysicsSystem::SagePhysicsSystem() = default;

void SagePhysicsSystem::Init()
{
	
	auto& entities = Game_Objects::Get_Game_Objects();

	for (auto& entity : entities)
	{
		Init_Entity(entity.second.get());
	}
}

void SagePhysicsSystem::Init_Entity(GameObject* _entity)
{
	RigidBody* rigid_body = _entity->Get_Component<RigidBody>();
	Transform* transform = _entity->Get_Component<Transform>();

	if (!rigid_body || !transform)
	{
		return;
	}

	if (!rigid_body->Get_Enabled())
	{
		return;
	}

	rigid_body->Get_Current_Velocity() = rigid_body->Get_Velocity();
}


void SagePhysicsSystem::Update()
{
	auto& entities = Game_Objects::Get_Game_Objects();

	for (auto& entity : entities)
	{
		Update_Entity(entity.second.get());
	}

}

void SagePhysicsSystem::Update_Entity(GameObject* _entity)
{
	static int i = 0;
	while (i++ < 100000)
		continue;
	Profiler::SageProfiler::Mark("Physics Engine"); // Marker
	
	RigidBody* rigid_body = _entity->Get_Component<RigidBody>();
	Transform* transform = _entity->Get_Component<Transform>();

	if (!rigid_body || !transform)
	{
		//Profiler::SageProfiler::Stop_Marker("Physics Engine");
		return;
	}

	if (!rigid_body->Get_Enabled())
	{
		//Profiler::SageProfiler::Stop_Marker("Physics Engine");
		return;
	}

	float dt = static_cast<float>(SageTimer::delta_time);

	if (rigid_body->Gravity_Flag())
	{

		rigid_body->Get_Current_Velocity() += rigid_body->Get_Gravity() * dt;
	}

	transform->Translate({ rigid_body->Get_Current_Velocity().x * dt, rigid_body->Get_Current_Velocity().y * dt, 0.f });
	//Profiler::SageProfiler::Stop_Marker("Physics Engine");
}


void SagePhysicsSystem::Exit()
{

}


void SagePhysicsSystem::Add_Force_Entity(RigidBody* _entity, const ToastBox::Vec2& force, int force_mode)
{
	if (!_entity)
	{
		return;
	}
	switch (force_mode)
	{
	case static_cast<int>(RigidBody::ForceMode::Force):
		_entity->Get_Current_Velocity() += (force / _entity->Get_Mass()) * static_cast<float>(SageTimer::delta_time);
		break;
	case
		static_cast<int>(RigidBody::ForceMode::Impulse):
		_entity->Get_Current_Velocity() += force / _entity->Get_Mass();
		break;
	}

}


void SagePhysicsSystem::Apply_Gravity(RigidBody* _component)
{
	if (!_component)
	{
		return;
	}
	_component->Get_Current_Velocity() += _component->Get_Gravity() * static_cast<float>(SageTimer::delta_time);
}



System::SystemType SagePhysicsSystem::GetInstance()
{
	return System::SystemType::PHYSICS;
}


SagePhysicsSystem::~SagePhysicsSystem() = default;






