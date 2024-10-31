//#ifndef TEXT_HPP
//#define TEXT_HPP
//#include "SageFont.hpp"
//#include "Component.hpp"
//
//class Text : public Component // Require a Transform component
//{
//	using iterator = std::string::iterator;
//	using const_iterator = std::string::const_iterator;
//
//
//	size_t id;
//	
//	unsigned ssbo_character;
//	TextRenderer::SageFont* font_model;
//
//	std::string text;
//	int font_size;
//	unsigned capacity;
//	unsigned size;
//
//	static size_t id_counter;
//public:
//	Text();
//	Text(const char* text, TextRenderer::SageFont* font = nullptr);
//
//	operator std::string() const;
//
//
//	iterator begin();
//	iterator end();
//
//	const_iterator begin() const;
//	const_iterator end() const;
//
//	void push_back(const char& c);
//	void pop_back();
//
//	void resize();
//	void clear();
//
//	void unload();
//
//	Text& operator=(const std::string& str);
//
//	void set_font(TextRenderer::SageFont* font);
//	void set_text(const char* text);
//
//	void allocate_ssbo(); // Allocate a buffer for the text
//
//	void realloc_ssbo(size_t size); // Reallocate the buffer for the text
//
//
//	const char * c_str();
//
//
//	iterator front;
//	iterator back;
//
//
//
//
//
//};
//#endif