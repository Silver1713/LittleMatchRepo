//#include "Components/Text.hpp"
//#include <functional>
//
//#include "SageSystemManager.hpp"
//#include "Systems/SageGraphicsSystem.hpp"
//
//size_t Text::id_counter = 0;
//Text::Text()
//{
//	id = std::hash<size_t>{}(text.size() + id_counter++);
//	allocate_ssbo();
//	// Generate a unique id for the text
//
//}
//
//Text::iterator Text::begin()
//{
//	return front;
//}
//
//Text::iterator Text::end()
//{
//	return front + size;
//}
//
//Text::const_iterator Text::begin() const
//{
//	return front;
//}
//
//Text::const_iterator Text::end() const
//{
//	return (front+ size);
//}
//
//void Text::push_back(const char& c)
//{
//	text.push_back(c);
//	size++;
//	
//	if (size >= capacity)
//	{
//		realloc_ssbo(static_cast<size_t>(size * 2));
//		capacity *= 2;
//	}
//}
//
//void Text::allocate_ssbo()
//{
//	size = 0;
//	capacity = 60;
//
//	SageGraphicsSystem* graphics_system = SageSystemManager::Get_System<SageGraphicsSystem>();
//	graphics_system->Allocate_SSBO(id, capacity, ssbo_character);
//
//	
//
//}
//
//Text& Text::operator=(const std::string& str)
//{
//	SageGraphicsSystem* graphics_system = SageSystemManager::Get_System<SageGraphicsSystem>();
//	std::string str_cpy{ str };
//	
//	if (str.size() > capacity)
//	{
//		realloc_ssbo(static_cast<size_t>(capacity * 2));
//		capacity *= 2;
//
//		
//
//
//	}
//
//	return *this;
//}
//
//void Text::set_font(TextRenderer::SageFont* font)
//{
//	font_model = font;
//}
//
//void Text::set_text(const char* text)
//{
//	SageGraphicsSystem* graphics_system = SageSystemManager::Get_System<SageGraphicsSystem>();
//	this->text = text;
//	if (this->text.size() > capacity)
//	{
//		realloc_ssbo(capacity* 2);
//		capacity *= 2;
//		
//	}
//	graphics_system->SSBO_SubData(id, 0, this->text.size(), this->text.data());
//}
//
//
//void Text::realloc_ssbo(size_t size)
//{
//	SageGraphicsSystem* graphics_system = SageSystemManager::Get_System<SageGraphicsSystem>();
//	graphics_system->Reallocate_SSBO(id, size);
//}
//
//void Text::unload()
//{
//	SageGraphicsSystem* graphics_system = SageSystemManager::Get_System<SageGraphicsSystem>();
//	graphics_system->SSBO_Delete(ssbo_character);
//	ssbo_character = 0;
//}
