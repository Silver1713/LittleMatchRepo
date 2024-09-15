#include <dinput.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

class PNG_Container
{
	// File stream
	std::ifstream image_file;

	// PNG File Operations
	using byte = unsigned char;
	using byte_4 = std::uint32_t;
	using byte_8 = std::uint64_t;
	byte PNG_Signature[8]{ 0x89,0x50,0x4E, 0x47,0xD,0xA,0x1A,0xA };

	// FILE DATA
	std::string file_name;
	size_t file_size;
	size_t image_width, image_height;
	size_t bit_depth,
		color_type,
		compression_method,
		filter_method,
		interlace_method,
		CRC;
	std::vector<byte> image_data;
	size_t signature_byte{ 8 };

public:
	

	byte_8 pack8ByteLE(unsigned char data[]);
	byte_4 pack4ByteLE(unsigned char data[]);

	byte_8 read8ByteLE(std::ifstream& file);
	byte_4 read4ByteLE(std::ifstream& file);

	bool isPNG(std::ifstream& file);

	std::streampos get_image_file_size();

	
	byte_4 getIDHRLen();


	PNG_Container(const char* file_name);

	// Move Constructor
	PNG_Container(PNG_Container&& other) noexcept;

	// Copy Constructor
	PNG_Container(const PNG_Container& other);

	// Move Assignment Operator
	PNG_Container& operator=(PNG_Container&& other) noexcept;

	// Copy Assignment Operator
	PNG_Container& operator=(const PNG_Container& other);


	// Function to load metadata (width, height, etc)
	void load_data();

	


	template<typename T>
	T& swap_endianess(T& val) {
		static_assert(std::is_integral<T>::value, "swap_endianness requires an integral type.");
		size_t obj_size = sizeof(T);
		T result = 0;

		for (size_t i = 0; i < obj_size; ++i) {
			result <<= 8;
			result |= (val & 0xFF);
			val >>= 8;
		}

		val = result;
		return val;
	}

};