#include"vector_editor.h"
#include"build_command.h"
#include <vector>

namespace {
	std::shared_ptr<Shape> find_shape(const std::pair<std::string,std::string>& type_name, const std::vector<std::shared_ptr<Shape>>& shapes) {
		auto& [type, name] = type_name;
		for (auto sh_cur_shape : shapes) {
			if (sh_cur_shape->check_match_shape(type, name))
				return sh_cur_shape;
		}
		return nullptr;
	}
}
std::vector<std::shared_ptr<Shape>> vector_editor::change_shape(const std::vector<std::shared_ptr<Shape>>& shapes, const  std::vector < std::pair<command, std::shared_ptr<Command>>>& commands) {
	if (shapes.empty() || commands.empty()) return std::vector<std::shared_ptr<Shape>>();
	Editor Commands;
	for (auto&[type_cmnd,cmnd] : commands) {
		if (type_cmnd == command::other_cmnd) continue;
		if (type_cmnd == command::undo) {
			Commands.undo();
			continue;
		}else if(type_cmnd==command::redo)
		{
			Commands.redo();
			continue;
		}
		std::shared_ptr<Shape> cur_shape = find_shape(cmnd->get_type_name_shape(), shapes);
		if (cur_shape) {
			Commands.AddExecutrCommand(cmnd, cur_shape);
		}
	}
	return shapes;
}