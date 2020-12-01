#pragma once
#include <vector>

class Numbers final
 {
     std::vector<int> right_numbers;
     std::vector<int> left_numbers;
public:
    Numbers() = delete;
    Numbers(int range);
    size_t empty() const;
    int get_random_left();
    int get_random_right();
    void add_left(int left);
    void add_right(int right);
 };
