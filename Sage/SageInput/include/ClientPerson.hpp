#ifndef Client_Person_HPP
#define Client_Person_HPP
#include <memory>
// This is the 2nd layer of abstraction

enum struct INPUT_KEYS
{
	KEY_0 = 48
};
class ClientPerson
{
private:
	class PIML_Person;
	static std::unique_ptr<PIML_Person> piml_person;

public:
	static void greet();
	static void greet(const char* name);
	static void say(const char* message);
	// EXAMPLE
	static bool getKeyPress(int key);
	static bool getKey(int key);
	
};

#endif