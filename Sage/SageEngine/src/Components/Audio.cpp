#include "Components/Audio.hpp"

void Audio::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void Audio::Update()
{

}
void Audio::Exit()
{

}
ComponentType Audio::Get_Component_Type() { return AUDIO; }