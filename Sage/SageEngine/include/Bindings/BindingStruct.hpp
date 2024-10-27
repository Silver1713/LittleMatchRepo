#ifndef BINDING_STRUCT_HPP
#define BINDING_STRUCT_HPP

namespace BindingStruct
{
#pragma pack(push, 1)
	struct alignas(4) CSVector2D
	{
		float x;
		float y;
	};
#pragma  pack(pop)

	enum class CSForceMode
	{
		Force,
		Impulse,
		VelocityChange,
		Acceleration
	};

}

#endif