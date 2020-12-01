#pragma once
#include"Command.h"
#include <vector>
#include<memory>
class Editor {
	std::vector<std::shared_ptr<Command>>commands;
	std::vector<std::shared_ptr<Shape>> shapes;
	std::vector<std::shared_ptr<Command>> cancelled_commands;
	std::vector<std::shared_ptr<Shape>> cancelled_shapes;
public:
	void AddExecutrCommand(std::shared_ptr<Command>cmd, std::shared_ptr<Shape> shape);
	void undo();
	void redo();
};
