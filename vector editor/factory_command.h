#pragma once
#include "Command.h"
#include "build_command.h"
#include <memory>
#include <map>
#include <functional>

class FactoryCommand  final
 {
    static 	std::map<std::string, command>  type_commands_map;
    static std::map<command, std::unique_ptr<BuilderCommand> > create_builder_creators();
    static std::map<command, std::unique_ptr<BuilderCommand> >builder_creators;
    static command create_type_command(const std::string& data);
 public:
     static std::vector < std::pair<command, std::shared_ptr<Command>>> create_commands(const std::vector<std::string> & data);
 };
