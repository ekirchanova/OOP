#include"Factory.h"
#include "processing_functions_of_string.h"
#include"PlayerCreator.h"
#include"TeamCreator.h"
#include"MatchCreator.h"
#include<stdexcept>
std::map<std::string, std::unique_ptr<Creator>> Factory::create_builder_creators()
{
	std::map<std::string, std::unique_ptr<Creator>> builder_creators;
	builder_creators.insert(std::make_pair("player", std::make_unique<PlayerCreator>()));
	builder_creators.insert(std::make_pair("team", std::make_unique<TeamCreator>()));
	builder_creators.insert(std::make_pair("match", std::make_unique<MatchCreator>()));
	return builder_creators;
}
std::map<std::string, std::unique_ptr<Creator> > Factory::builder_creators = Factory::create_builder_creators();
std::shared_ptr <Product> Factory::create_Factory(const std::string& cur_str) {
	std::vector<std::string> cur_data = processing_functions_of_string::parse_string(cur_str);
	try
	{
		Creator* cur_creator= builder_creators.at(cur_data[size_t(struct_string_info::type)]).get();
		return cur_creator->create_product(cur_data);
	}catch (const std::out_of_range)
	{
		return nullptr;
	}
}
