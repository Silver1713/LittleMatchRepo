#include "Bindings/Binding.hpp"
#include "Bindings/BindingStruct.hpp"
class TransformBinding
{
public:
	static void Bind();
	void Bind(GameObject* object);
	static void Unbind();

	static void getPosition(MonoObject* obj, BindingStruct::CSVector2D* out_obj=nullptr);
	static float getRotation(MonoObject* obj);
	static MonoObject* getScale(MonoObject* obj);

	static void setPosition(MonoObject* obj, BindingStruct::CSVector2D* in_obj);
	static void setRotation(MonoObject* obj, MonoObject* rotation);
	static void setScale(MonoObject* obj, MonoObject* scale);

};