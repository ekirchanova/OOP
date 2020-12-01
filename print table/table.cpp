#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector> 
#include <algorithm>
#include <fstream>
#include "extended_iomanip.h"
#include"table.h"
using namespace std;
const char separator{ '|' };
const char  corner_separator  { '+' };
const char horizontal_separator{ '-' };
static Formatting formater(char symbol) 
{
	switch (symbol) {
	case'<':
		return Formatting::LEFT;
	case '>':
		return Formatting::RIGHT;
	case '=':
		return Formatting::CENTER;
	default:
		return Formatting::CENTER;
	}
}
void table:: read(istream& input, vector<Formatting> &columns, std::vector<std::vector<std::string> > &table) {
	string format;
	if (!input)
		throw bad_stream();
	getline(input, format);
	transform(format.begin(), format.end(),back_inserter(columns),formater );
	string str;
	while (getline(input, str)) {
		vector<string>temp;
		istringstream ist(str);
		copy( istream_iterator<string>(ist), {}, back_inserter(temp));
		table.push_back(temp);
		str.clear();
	}
}
static void print_separator(ostream &os,size_t size,vector<size_t> max_length) 
{
	for (size_t indCols = 0; indCols < size; indCols++) {
		os << corner_separator;
		size_t count = (max_length[indCols] % 2 == 0) ? max_length[indCols]+1 : max_length[indCols] + 2;
		for (size_t i = 0; i <count ; i++) {
			os << horizontal_separator;
		}
	}
	os << corner_separator << endl;
}
static void max__length(const vector<Formatting> &columns, const std::vector<std::vector<std::string> > &table,vector <size_t> &max_length) {
	size_t  max__length = 0;
	for (size_t i = 0; i < columns.size(); i++) {
		for (size_t j = 0; j < table.size(); j++)
		{
			if (i >= table[j].size())continue;
			if (table[j].at(i).size() > max__length)
				max__length = table[j].at(i).size();
		}
		max_length.push_back(max__length);
		max__length = 0;
	}
}
void table:: print_table(ostream &os, const vector<Formatting> &columns, const std::vector<std::vector<std::string> > &table) {
	if (!os)
		throw bad_stream();
	vector <size_t> max_length;
	max__length(columns, table, max_length);
	for (size_t indRows= 0; indRows < table.size(); indRows++) 
	{
		print_separator(os, columns.size(), max_length);
		for (size_t indCols = 0; indCols < columns.size(); indCols++)
		{
			size_t count = (max_length[indCols] % 2 == 0) ? max_length[indCols] + 1 : max_length[indCols] + 2;
			if (indCols >= table[indRows].size()) {
					os << separator << setw(count) << center(" ");
				continue;
			}
			switch (columns[indCols]) {
			case Formatting::LEFT: {
				os << separator << setw(count) << left(table[indRows][indCols]);
				continue;
			}
			case Formatting::RIGHT: {
				os << separator << setw(count) << right(table[indRows][indCols]);
				continue;
			}
			case Formatting::CENTER: {
				os << separator << setw(count) << center(table[indRows][indCols]);
				continue;
			}
			}
		}
		os << separator <<endl;
	}
	print_separator(os, columns.size(), max_length);
}