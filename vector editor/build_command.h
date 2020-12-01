#pragma once
#include<memory>
#include<vector>
#include<string>
#include"Command.h"
class ScaleBuilder;
class TranslateBuilder;
class RotateBuilder;
class BuilderCommand {
public:
	virtual ~BuilderCommand()=default;
	virtual std::shared_ptr<Command> creator_command(const std::vector<std::string>& cur_data)=0;
};


