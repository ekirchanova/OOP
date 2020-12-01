#pragma once
#include "build_command.h"
#include "create_command.h"

class TranslateBuilder final :public BuilderCommand
{
public:
	std::shared_ptr<Command> creator_command(const std::vector<std::string>& cur_data)override;
};
