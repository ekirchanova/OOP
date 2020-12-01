#pragma once
#include"Scale.h"

Scale::Scale(const std::pair<std::string, std::string>& _type_name, double _sx, double _sy) : type_name(_type_name), sx(_sx), sy(_sy)
{
}
void Scale::undo(std::shared_ptr<Shape> shape) {
	shape->scale(1 / sx, 1 / sy);
}
std::pair<std::string, std::string> Scale::get_type_name_shape()
{
	return type_name;
}
void Scale::redo(std::shared_ptr<Shape> shape) {
	shape->scale(sx, sy);
}
void Scale::do_(std::shared_ptr<Shape> shape) {
	shape->scale(sx, sy);
}