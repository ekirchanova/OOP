#pragma once
#include"shape.h"
#include"Line.h"
#include "Rect.h"
#include"Ellipse.h"
#include<memory>
#include<stdexcept>

enum class shape {
	rect, line, ellipse
};
class ShapeCreator final{
public:
	template<typename ...Args>
	std::shared_ptr<Shape> create_shape(shape cur_shape, Args&&...args) {
		switch (cur_shape)
		{ 
			case shape::line:
				return construct<Line>(std::forward<Args>(args)...);
			case shape::rect:
				return construct<Rect>(std::forward<Args>(args)...);
			case shape::ellipse:
				return construct<Ellipse>(std::forward<Args>(args)...);

			default:
			throw std::invalid_argument("Shape is not exist");
		}
	}
private:
	template<typename Concrete,typename ...Args>
	std::enable_if_t<std::is_constructible_v<Concrete, Args...>, std::shared_ptr<Concrete>>
		construct(Args&&...args) {
		return std::make_shared<Concrete>(std::forward<Args>(args)...);
	};
	template<typename Concrete, typename ...Ts>
	static 	std::shared_ptr<Concrete > construct(...) {
		return nullptr;
	};
};