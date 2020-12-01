#pragma once
#include <memory>
class DataBase;
class Player;
class Match;
class Team;

using id = size_t;
class Product {
protected:
	static std::shared_ptr<DataBase> DB;
public:
	Product()=default;
	virtual ~Product()=default;
	virtual id get_id() const = 0;
};






