#ifndef SAGE_TEXT_SYSTEM_HPP
#define SAGE_TEXT_SYSTEM_HPP
#include <map>

#include "System.hpp"

class SageGraphicsSystem : public System
{
	std::map<unsigned, unsigned> ssbo_data;
public:
	void Init() override;
	void Update() override;
	void Exit() override;
	SystemType GetInstance() override;
	~SageGraphicsSystem() override;

	void Allocate_SSBO(unsigned id,unsigned size, unsigned& ssbo_handle);
	void Reallocate_SSBO(unsigned id, size_t size);
	void Append_SSBO(unsigned id, unsigned offset, unsigned data_size, void * data);
	void SSBO_SubData(unsigned id, unsigned offset, unsigned size, void* data);
	void SSBO_Delete(unsigned& id);
};


#endif // SAGE_TEXT_SYSTEM_HPP