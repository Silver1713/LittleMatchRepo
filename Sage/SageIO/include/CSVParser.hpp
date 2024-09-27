/* Start Header ************************************************************************/
/*!
\file		CSVParser.hpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		A generic parser to read and organise data from a CSV to Parsed_CSV struct.
			Also contains the structs that define the read data in a way that can be read by
			the AssetLoader.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Parsed_CSV_Row_Data
{
	int row{};
	std::vector<std::string> associated_data{};	
};

struct Parsed_CSV
{
	int num_rows{};
	int num_cols{};
	std::vector<Parsed_CSV_Row_Data> comma_seperated_data{};

	Parsed_CSV_Row_Data* Find_Row_With_ID(std::string const& search_string, unsigned int const col = 0);
};

Parsed_CSV Parse_CSV(std::string const& path);