#ifndef SAGE_ENGINE_HPP
#define SAGE_ENGINE_HPP


struct SageEngine
{
	static void Init();
	static void Update();
	static void PhysicsUpdate();
	static void Draw(bool inEditor);
	static void Exit();
};

#endif