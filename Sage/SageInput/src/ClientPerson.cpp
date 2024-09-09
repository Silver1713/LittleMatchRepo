#include "InternalPerson.hpp"
#include "ClientPerson.hpp"

// This is the 2nd layer of abstraction - Hides implementation for the InternalPerson class
// This source file has access to both the 2nd and 3rd layer of abstraction




class ClientPerson::PIML_Person
{
public:
	static void greet()
	{
		
		InternalPerson::greet();
		
	}

	static void greet(const char* name)
	{
		InternalPerson::greet(name);
	}

	static void say(const char* message)
	{
		InternalPerson::say(message);
	}

	static bool getKeyPress(int key)
	{
		return InternalPerson::getKeyPress(key);
	}

	static bool getKey(int key)
	{
		return InternalPerson::getKey(key);
	}
};

std::unique_ptr<ClientPerson::PIML_Person> ClientPerson::piml_person{ std::make_unique<ClientPerson::PIML_Person>() };


void ClientPerson::greet()
{
	piml_person->greet();

}

void ClientPerson::greet(const char* name)
{

	piml_person->greet(name);
}

void ClientPerson::say(const char* message)
{
	piml_person->say(message);
}

bool ClientPerson::getKeyPress(int key)
{
	return	piml_person->getKeyPress(key);
}


bool ClientPerson::getKey(int key)
{
	
	return piml_person->getKey(key);
}



