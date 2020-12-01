#include "factory_command.h"
#include "processing_functions_of_string.h"
#include"ScaleBuilder.h"
#include "RotateBuilder.h"
#include"TranslateBuilder.h"
#include <stdexcept>

namespace 
{
	static enum class struct_string_info
	{
		type_cmnd = 0
	};
	std::map<std::string, command> create_type_commands_map()
	{
		std::map<std::string, command>type_commands_map;
		type_commands_map.insert(std::make_pair("translate", command::translate));
		type_commands_map.insert(std::make_pair("scale", command::scale));
		type_commands_map.insert(std::make_pair("rotate", command::rotate));
		type_commands_map.insert(std::make_pair("undo", command::undo));
		type_commands_map.insert(std::make_pair("redo", command::redo));
		return type_commands_map;
	}
}
std::map<std::string, command> FactoryCommand::type_commands_map=create_type_commands_map();

std::map<command, std::unique_ptr<BuilderCommand> > FactoryCommand::create_builder_creators()
{
	std::map<command, std::unique_ptr<BuilderCommand>> builder_creators;
	builder_creators.insert(std::make_pair(command::scale, std::make_unique<ScaleBuilder>()));
	builder_creators.insert(std::make_pair(command::translate, std::make_unique<TranslateBuilder>()));
	builder_creators.insert(std::make_pair(command::rotate, std::make_unique<RotateBuilder>()));
	return builder_creators;
}
std::map<command, std::unique_ptr<BuilderCommand>> FactoryCommand::builder_creators = FactoryCommand::create_builder_creators();
command FactoryCommand::create_type_command(const std::string& data)
{
	try {
		return type_commands_map.at(data);
	}
	catch (const std::out_of_range) {
		return command::other_cmnd;
	}
}
std::vector<std::pair<command, std::shared_ptr<Command>>> FactoryCommand::create_commands(const std::vector<std::string>& data)
{
	if (data.empty()) return std::vector<std::pair<command, std::shared_ptr<Command>>>();
	std::vector<std::pair<command, std::shared_ptr<Command>>> commands;
	for (auto& cmnd : data) {

		std::vector<std::string> cur_data = processing_functions_of_string::parse_string((cmnd));
		command cur_type_cmnd = create_type_command(cur_data[size_t(struct_string_info::type_cmnd)]);
		if (cur_type_cmnd == command::other_cmnd) continue;
		if (cur_type_cmnd== command::undo||cur_type_cmnd==command::redo){
			commands.emplace_back(std::make_pair(cur_type_cmnd, nullptr));
			continue;
		}
		try
		{
			BuilderCommand* cur_creator = builder_creators.at(cur_type_cmnd).get();
			std::shared_ptr<Command> new_command=cur_creator->creator_command(cur_data);
			if (new_command)
				commands.emplace_back(std::make_pair(cur_type_cmnd, new_command));
		}
		catch (const std::out_of_range)
		{
			continue;;
		}
	}
	return commands;
}
