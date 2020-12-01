#include"editor.h"

void Editor::AddExecutrCommand(std::shared_ptr<Command>cmd,std::shared_ptr<Shape> shape)
{
	commands.push_back(cmd);
	shapes.push_back(shape);
	cmd->do_(shape);
}
void Editor::undo() {
	if (commands.empty())return;
	std::shared_ptr<Command> cmd = commands.back();
	const std::shared_ptr<Shape> shape = shapes.back();
	cmd->undo(shape);
	cancelled_commands.push_back(cmd);
	cancelled_shapes.push_back(shape);
	commands.pop_back();
	shapes.pop_back();
}

void Editor::redo()
{
	if (cancelled_commands.empty())return;
	std::shared_ptr<Command> cmd = cancelled_commands.back();
	const std::shared_ptr<Shape> shape = cancelled_shapes.back();
	cmd->redo(shape);
	commands.push_back(cmd);
	shapes.push_back(shape);
	cancelled_commands.pop_back();
	cancelled_shapes.pop_back();
}
