#include "Components/ScriptableBehaviour.hpp"
#include "BehaviourComponent/Player.hpp"
#include <iostream>




void Player::Init(GameObject* _parent)
{
	ScriptableBehaviour::Init();

}


void Player::Update()
{
	std::cout << "Player Update" << std::endl;
}

void Player::Exit()
{
	
}


