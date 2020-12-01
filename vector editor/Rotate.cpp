#pragma once
#include "Rotate.h"
void Rotate::undo(std::shared_ptr<Shape> shape) {
	shape->rotate(-angle);
}
std::pair<std::string, std::string> Rotate::get_type_name_shape()
{
	return type_name;
}

void Rotate::redo(std::shared_ptr<Shape> shape) {
	shape->rotate(angle);
}
void Rotate::do_(std::shared_ptr<Shape> shape) {
	shape->rotate(angle);
}


Rotate::Rotate(const std::pair<std::string, std::string>& _type_name, double _angle) :type_name(_type_name), angle(_angle)
{
}