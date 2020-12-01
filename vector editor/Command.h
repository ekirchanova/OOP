#pragma once
#include"shape.h"
#include <memory>

enum class command
{
	translate, scale, rotate, undo,redo,other_cmnd
};
class Scale;
class Translate;
class Rotate;
class Command {
public:
	virtual ~Command()=default;
	virtual void redo(std::shared_ptr<Shape> shape) = 0;
	virtual void do_(std::shared_ptr<Shape> shape) = 0;
	virtual void undo(std::shared_ptr<Shape> shape) = 0;
	virtual std::pair<std::string, std::string> get_type_name_shape() = 0;
};


