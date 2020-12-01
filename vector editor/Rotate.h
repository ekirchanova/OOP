#pragma once
#include"shape.h"
#include "create_command.h"

class Rotate final :public Command {
	std::pair<std::string, std::string> type_name;
	double angle;
public:
	Rotate(const std::pair<std::string, std::string>& _type_name, double _angle);
	void redo(std::shared_ptr<Shape> shape)override;
	void undo(std::shared_ptr<Shape> shape)override;
	void do_(std::shared_ptr<Shape> shape) override;
	std::pair<std::string, std::string> get_type_name_shape()override;
};
