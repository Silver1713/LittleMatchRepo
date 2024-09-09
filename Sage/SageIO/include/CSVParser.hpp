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