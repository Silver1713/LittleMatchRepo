/* Start Header ************************************************************************/
/*!
\file		CSVParser.cpp
\title		Memory's Flame
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		08 September 2024
\brief		A generic parser to read and organise data from a CSV to Parsed_CSV struct
			that can be read by the AssetLoader.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "CSVParser.hpp"

/*!*****************************************************************************
  \brief
	Gets the map of prefabs

  \param _search_string
	the string to look for

  \param _col
	column to search for

  \return
	Pointer to the row's data
*******************************************************************************/
Parsed_CSV_Row_Data* Parsed_CSV::Find_Row_With_ID(std::string const& search_string, unsigned int col)
{
	for (Parsed_CSV_Row_Data m_pd : comma_seperated_data)
	{
		if (std::strcmp(m_pd.associated_data[col].c_str(), search_string.c_str()) == 0)
		{
			return &(comma_seperated_data[m_pd.row]);
		}
	}
	return nullptr;
}

/*!*****************************************************************************
  \brief
	Parses the csv in the path

  \param _path
	the path to parse

  \return
	The parsed csv
*******************************************************************************/
Parsed_CSV Parse_CSV(std::string const& path)
{

	std::ifstream ifs(path);

	Parsed_CSV p;
	Parsed_CSV_Row_Data pd;

	if (ifs.is_open())
	{
		std::cerr << "CSV File in " << path << " opened and read successfully." << std::endl;

		std::string cur_line;
		std::string word;
		std::istringstream iss{};
		int cur_row{};

		std::getline(ifs, cur_line);
		p.num_rows++;
		p.num_cols = (int)(std::count(cur_line.begin(), cur_line.end(), ',')) + 1;
		iss = std::istringstream(cur_line);
		while (std::getline(iss, word, ','))
		{
			pd.row = cur_row;
			pd.associated_data.push_back(word);
		}

		p.comma_seperated_data.push_back(pd);
		pd.associated_data.clear();

		while (std::getline(ifs, cur_line))
		{
			cur_row++;
			iss = std::istringstream(cur_line);

			while (std::getline(iss, word, ','))
			{
				pd.row = cur_row;
				pd.associated_data.push_back(word);
			}

			p.comma_seperated_data.push_back(pd);
			pd.associated_data.clear();
			
			p.num_rows++;
		}
		ifs.close();
	}
	else 
	{
		std::cerr << "CSV File in " << path << " cannot be opened." << std::endl;
		return p;
	}
	
	return p;
}