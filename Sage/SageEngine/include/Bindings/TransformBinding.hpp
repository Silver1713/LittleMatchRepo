#include "Bindings/Binding.hpp"

class TransformBinding
{
public:
#pragma pack(push, 1) 
	struct alignas(4) CSVector2D
	{
		float x;
		float y;
	};
#pragma pack(pop)

	static void Bind();
	void Bind(GameObject* object);
	static void Unbind();

	static void getPosition(MonoObject* obj, CSVector2D* out_obj=nullptr);
	static float getRotation(MonoObject* obj);
	static MonoObject* getScale(MonoObject* obj);

	static void setPosition(MonoObject* obj, CSVector2D* in_obj);
	static void setRotation(MonoObject* obj, MonoObject* rotation);
	static void setScale(MonoObject* obj, MonoObject* scale);

};