#include "PNG_Container.hpp"

#include <GLFW/glfw3.h>

PNG_Container::PNG_Container(PNG_Container&& other) noexcept
{
	
	image_file = std::move(other.image_file);
	file_size = other.file_size;
	image_width = other.image_width;
	image_height = other.image_height;
	image_data = std::move(other.image_data);
}


PNG_Container::PNG_Container(const char* file_name)
{
	image_file = std::ifstream(file_name, std::ios::binary);
	if (!image_file.is_open())
	{
		throw std::runtime_error("Could not open file");
	}
	this->file_name = file_name;
	if (!isPNG(image_file))
	{
		throw std::runtime_error("File is not a PNG");
	}
}

PNG_Container& PNG_Container::operator=(PNG_Container&& other) noexcept
{
	if (this != &other)
	{
		image_file = std::move(other.image_file);
		file_size = other.file_size;
		image_width = other.image_width;
		image_height = other.image_height;
		image_data = std::move(other.image_data);
	}
	return *this;
}


PNG_Container::PNG_Container(const PNG_Container& other)
{
	image_file = std::ifstream(other.file_name);
	file_size = other.file_size;
	image_width = other.image_width;
	image_height = other.image_height;
	image_data = std::move(other.image_data);
	//::copy(other.image_data.get(), other.image_data.get() + file_size, image_data.get());
}


PNG_Container::byte_4 PNG_Container::pack4ByteLE(unsigned char data[])
{
	
	byte_4 container{};
	for (int i = 3; i >= 0; i--) {
		container |= (static_cast<byte_4>((data[3 - i])) << 8 * (3 - i));
	}
	return container;
}

PNG_Container::byte_8 PNG_Container::pack8ByteLE(unsigned char data[])
{
	byte_8 container{};
	for (int i = 0; i < 8; i++) {
		container |= (static_cast<byte_8>((data[i])) << 8 * (7 - i));
	}

	return container;
}

PNG_Container::byte_4 PNG_Container::read4ByteLE(std::ifstream& file)
{
	byte_4 value{};
	image_file.read(reinterpret_cast<char*>(&value), 4);
	swap_endianess(value);
	return value;
}

PNG_Container::byte_8 PNG_Container::read8ByteLE(std::ifstream& file)
{
	byte_8 value{};
	image_file.read(reinterpret_cast<char*>(&value), 8);
	swap_endianess(value);
	return value;
}


std::streampos PNG_Container::get_image_file_size()
{
	std::streampos image_in_byte{};
	image_file.seekg(0, std::ios::end);

	image_in_byte = image_file.tellg();

	image_file.seekg(0, std::ios::beg);


	return image_in_byte;
}

PNG_Container::byte_4 PNG_Container::getIDHRLen()
{
	byte_4 idhrlen{};
	image_file.seekg(signature_byte, std::ios::beg);

	idhrlen = read4ByteLE(image_file);

	image_file.seekg(0, std::ios::beg);

	return idhrlen;
}


bool PNG_Container::isPNG(std::ifstream& file)
{
	byte_8 singature{ pack8ByteLE(PNG_Signature) };

	byte_8 content = { read8ByteLE(file) };

	if (content == singature) {
		file.seekg(0, file.beg);
		return true;
	}


	return false;
}


void PNG_Container::load_data()
{
	byte_4 idhrlen = getIDHRLen();
	image_file.seekg(idhrlen+3, std::ios::beg);

	byte_4 width = read4ByteLE(image_file);
	byte_4 height = read4ByteLE(image_file);
	bit_depth = image_file.get();
	color_type = image_file.get();
	compression_method = image_file.get();
	filter_method = image_file.get();
	interlace_method = image_file.get();
	CRC = read4ByteLE(image_file);

	// Next 4 byte will be the height
	image_width = static_cast<size_t>(width);
	image_height = static_cast<size_t>(height);

	image_file.seekg(0, std::ios::beg);

	char reader{};
	bool isInIDAT{ false }, isInIEND{ false },isInHeader{false};
	image_data.reserve(height * width);
	while (image_file)
	{
		reader = static_cast<char>(image_file.peek());
		
		if (reader == 'I')
		{
			std::string chunk_header{};
			chunk_header.resize(4);
			
			image_file.read(chunk_header.data(), 4);

			if (chunk_header == "IDAT")
			{
				std::cout << "Entered IDAT" << '\n';
				isInIDAT = true;
				isInIEND = false;
				continue;
			}
			else if (chunk_header == "IEND")
			{
				std::cout << "Entered IEND" << '\n';
				isInIEND = true;
				isInIDAT = false;
				break;
			}

			if (isInIDAT)
			{
				//push chunk header back to the stream

				image_file.seekg(-4, std::ios::cur);

				for (int i = 0; i < 4; i++)
				{
					char data = static_cast<char>(image_file.get());
					image_data.push_back(static_cast<byte>(data));

				}
				continue;
			}
		}

		if (isInIDAT)
		{
			byte data = static_cast<byte>(image_file.get());
			image_data.push_back(data);
			std::cout << "Collected Data :" << (char)data  << std::endl;
		} else
		{
			image_file.get();
		}


		
		
	}

}



void DEFLATE()
{
	//Deflating :((	

	
}










