#pragma once
#include"Command.h"
#include<memory>
#include <stdexcept>
class CommandCreator final {
public:
	template<typename ...Args>
	std::shared_ptr<Command> create_command(command cur_cmnd, Args&&...args) {
		switch (cur_cmnd)
		{
		case command::scale:
			return construct<Scale>(std::forward<Args>(args)...);
		case command::translate:
			return construct<Translate>(std::forward<Args>(args)...);
		case command::rotate:
			return construct<Rotate>(std::forward<Args>(args)...);

		default:
			throw std::invalid_argument("Command is not exist");
		}
	}
private:
	template<typename Concrete, typename ...Args>
	std::enable_if_t<std::is_constructible_v<Concrete, Args...>, std::shared_ptr<Concrete>>
		construct(Args&&...args) {
		return std::make_shared<Concrete>(std::forward<Args>(args)...);
	};
	template<typename Concrete, typename ...Ts>
	std::shared_ptr<Concrete > construct(...) {
		return nullptr;
	};
};