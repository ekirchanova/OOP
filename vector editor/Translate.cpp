#include"Translate.h"
Translate::Translate(const std::pair<std::string, std::string>& _type_name, double _dx, double _dy) : type_name(_type_name), dx(_dx), dy(_dy)
{
}
void Translate::undo(std::shared_ptr<Shape> shape) {
	shape->translate(-dx, -dy);
}
std::pair<std::string, std::string> Translate::get_type_name_shape()
{
	return type_name;
}
void Translate::redo(std::shared_ptr<Shape> shape) {
	shape->translate(dx, dy);
}
void Translate::do_(std::shared_ptr<Shape> shape) {
	shape->translate(dx, dy);
}