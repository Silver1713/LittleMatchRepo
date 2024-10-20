#include "Bindings/Binding.hpp"

class TransformBinding : public Binding
{
public:
	struct CSVector2D
	{
		float x;
		float y;
	};

	void Bind() override;
	void Bind(GameObject* object) override;
	void Unbind() override;

	MonoObject* getPosition(MonoObject* obj);
	MonoObject* getRotation(MonoObject* obj);
	MonoObject* getScale(MonoObject* obj);

	void setPosition(MonoObject* obj, MonoObject* position);
	void setRotation(MonoObject* obj, MonoObject* rotation);
	void setScale(MonoObject* obj, MonoObject* scale);

	~TransformBinding() override = default;
};