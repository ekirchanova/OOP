#pragma once
#include"shape.h"
#include "create_command.h"

class Scale final :public Command {
	double sx, sy;
	std::pair<std::string, std::string> type_name;
public:
	Scale(const std::pair<std::string, std::string>& _type_name, double _sx, double _sy);
	void redo(std::shared_ptr<Shape> shape)override;
	void undo(std::shared_ptr<Shape> shape)override;
	void do_(std::shared_ptr<Shape> shape) override;
	std::pair<std::string, std::string> get_type_name_shape()override;
};
