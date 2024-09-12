#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "CSVParser.hpp"

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