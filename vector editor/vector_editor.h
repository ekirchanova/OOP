#pragma once
#include"editor.h"
#include"build_shape.h"
#include <memory>

namespace vector_editor {
	std::vector<std::shared_ptr<Shape>> change_shape(const std::vector<std::shared_ptr<Shape>>& shapes, const  std::vector < std::pair<command, std::shared_ptr<Command>>>& commands);
}