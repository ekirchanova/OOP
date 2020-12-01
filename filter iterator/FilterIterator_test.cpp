#include "pch.h"
#include"FilterIterator.h"
#include "gtest-memleak.h"
#include <vector>
#include<unordered_map>
#include<list>
#include<deque>
const size_t count_el = 5;
using namespace std;
struct is_negative_number {
	bool operator()(const int x) { return x<0; }
	bool operator()(const int x) const { return x<0; }
};
struct is_positive_pair {
	bool operator()(const std::pair<int, int> x) { return x.first > 0; }
	bool operator()(const std::pair<int, int> x) const{ return x.first > 0; }
};
TEST(Test_vector_without_pred, int) {
	vector<int> test{ 5,-9,-8,6,-2 }, result{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter=0;
	for (auto i : filter_a) {
		if(i==result[counter])
		++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_vector_without_pred, double) {
	vector<double> test = { -0.1,0.5,-8.3,3.6,-7.2 }, result{ -0.1,0.5,-8.3,3.6,-7.2 };
	auto filter_a = make_filter_class( test.begin(), test.end());
	size_t counter=0;
	for (auto i : filter_a) {
		if (i == result[counter])
		++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_vector_with_pred, int) {
	vector<int> test{ 5,-9,-8,6,-2 }, result{ - 9,-8,-2};
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter=0;
	for (auto i : filter_a) {
		if (i == result[counter])
		++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_vector_with_pred, double) {
	std::vector<double> test = { 0,-1.1,0.5,3.6,-8.3,0.6,0.4,-85.3,12.36,-7.2 }, result{-1.1,-8.3,-85.3,-7.2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter=0;
	for (auto i : filter_a) {
		if (i -result[counter]< 1e-10)
		++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(test_invalid_without_pred, begin) {
	vector<int> test{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.begin(), test.begin());
	size_t counter = 0;
	for (auto i : filter_a) {
			++counter;
	}
	EXPECT_EQ(counter, 0);
}
TEST(test_invalid_without_pred, end) {
	vector<int> test{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.end(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
		++counter;
	}
	EXPECT_EQ(counter, 0);
}
TEST(test_unord_map_with_pred,int) {
	std::unordered_map<int, int > test = {
		{ 0, 0 }, { 4, 0 }, { -5, 0 }, { 2, 0 }, { 8, 0 }, { -1, 0 },{9,62},{-95,4} };
	std::vector<int> result{ 8,4,2,9 };
	auto filter_b = make_filter_class(is_positive_pair(),test.begin(), test.end());
	size_t counter = 0;
	for (auto [a,b]: filter_b) {
		if (a== result[counter])
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(test_unord_map_without_pred, int) {
	std::unordered_map<int, int > test = {
		{ 0, 0 }, { 4, 0 }, { -5, 0 }, { 2, 0 }, { 8, 0 }, { -1, 0 },{9,62},{-95,4} };
	auto filter_b = make_filter_class( test.begin(), test.end());
	size_t counter = 0;
	for (auto [a, b] : filter_b) {
			++counter;
	}
	EXPECT_EQ(counter, test.size());
}
TEST(test_unord_map_with_pred, double) {
	std::unordered_map<double,double > test = {
		{ 2.3, 0 }, { 4.6, 0 }, { -5.9, 0 }, { 2.4, 0 }, { 8.6, 0 }, { -1.345, 0 },{9.3214,62},{-95.3,4} };
	std::vector<double> result{ 4.6,2.3,2.4,9.3214,8.6};
	auto filter_b = make_filter_class(is_positive_pair(), test.begin(), test.end());
	size_t counter = 0;
	for (auto [a, b] : filter_b) {
		if (a == result[counter])
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(test_unord_map_without_pred, double) {
	std::unordered_map<double, double > test = {
		{ 2.3, 0 }, { 4.6, 0 }, { -5.9, 0 }, { 2.4, 0 }, { 8.6, 0 }, { -1.345, 0 },{9.3214,62},{-95.3,4} };
	auto filter_b = make_filter_class( test.begin(), test.end());
	size_t counter = 0;
	for (auto [a, b] : filter_b) {
			++counter;
	}
	EXPECT_EQ(counter, test.size());
}
TEST(test_mas_without_pred, int) {
	int mas[count_el] = { 10,20,36,58,95 };
	int test1[count_el]= { 10,20,36,58,95 };
	auto filter_b = make_filter_class( begin(mas), end(mas));
	int counter = 0;
	for (auto i:filter_b) {
		if (i == test1[counter]) {
			++counter;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_mas_without_pred, double) {
	double mas[count_el] = { 10.8,20.5,36.9,58.74,95.03 };
	double test1[count_el] = { 10.8,20.5,36.9,58.74,95.03 };
	auto filter_b = make_filter_class(begin(mas), end(mas));
	int counter = 0;
	for (auto i : filter_b) {
		if (i == test1[counter]) {
			++counter;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_mas_with_pred, int) {
	int mas[count_el] = { 10,-20,-36,-58,95 };
	int test1[count_el] = { -20,-36,-58 };
	auto filter_b = make_filter_class(is_negative_number(),begin(mas), end(mas));
	int counter = 0;
	for (auto i : filter_b) {
		if (i == test1[counter]) {
			++counter;
		}
	}
	EXPECT_EQ(counter, count_el-2);
}
TEST(test_mas_with_pred, double) {
	double mas[count_el] = { 10.8,-20.5,36.9,-58.74,-95.03 };
	double test1[count_el] = { -20.5,-58.74,-95.03 };
	auto filter_b = make_filter_class(begin(mas), end(mas));
	int counter = 0;
	for (auto i : filter_b) {
		if (i == test1[counter]) {
			++counter;
		}
	}
	EXPECT_EQ(counter, count_el-2);
}
TEST(test_list_without_pred, int) {
	list<int> test{ 5,-9,-8,6,-2 }, result{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_list_with_pred, int) {
	list<int> test{ 5,-9,-8,6,-2 }, result{ -9,-8,-2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(test_deque_without_pred, int) {
	deque<int> test{ 5,-9,-8,6,-2 }, result{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
		if (i == result[counter]) {
			++counter;
		}
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_deque_with_pred, int) {
	deque<int> test{ 5,-9,-8,6,-2 }, result{ -9,-8,-2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
		if (i == result[counter]) {
			++counter;
		}
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_deque_without_pred, double) {
	deque<double> test = { -0.1,0.5,-8.3,3.6,-7.2 }, result{ -0.1,0.5,-8.3,3.6,-7.2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
		if (i == result[counter])
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_deque_with_pred, double) {
	std::deque<double> test = { 0,-1.1,0.5,3.6,-8.3,0.6,0.4,-85.3,12.36,-7.2 }, result{ -1.1,-8.3,-85.3,-7.2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
		
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_list_without_pred, double) {
	list<double> test = { -0.1,0.5,-8.3,3.6,-7.2 }, result{ -0.1,0.5,-8.3,3.6,-7.2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_list_with_pred, double) {
	std::list<double> test = { 0,-1.1,0.5,3.6,-8.3,0.6,0.4,-85.3,12.36,-7.2 }, result{ -1.1,-8.3,-85.3,-7.2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter = 0;
	for (auto i : filter_a) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}


TEST(vec, empty) {
	std::vector<int> vec = {};
	auto sh = make_filter_class(vec.begin(), vec.end());

	int amount = 0;
	for (auto i : sh) {
		amount++;
	}
	std::cout << std::endl;
	EXPECT_EQ(amount, vec.size());
}

TEST(containers, amount_check) {
	std::vector<int> vec = { 1,2,3,11,5,0 };
	int ar[] = { 1,2,3,11,5,0 };
	std::vector<char> v1 = { 'a','b','c','d' };
	std::unordered_map< int, int > c = {
	{ 0, 0 }, { 4, 0 }, { 5, 0 }, { 2, 0 }, { 8, 0 }, { 1, 0 }
	};
	auto sh = make_filter_class(vec.begin(), vec.end());
	auto sh1 = make_filter_class(v1.begin(), v1.end());
	auto sh2 = make_filter_class(c.begin(), c.end());
	auto sh3 = make_filter_class(ar, ar + 6);
	int amount = 0;
	for (auto i : sh3) {
		amount++;
	}
	EXPECT_EQ(amount, 6);
	amount = 0;
	for (auto i : sh) {
		amount++;
	}
	EXPECT_EQ(amount, vec.size());
	amount = 0;
	for (auto i : sh1)
		amount++;
	EXPECT_EQ(amount, v1.size());
	amount = 0;
	for (auto i : sh2)
		amount++;
	EXPECT_EQ(amount, c.size());

}






TEST(vec_vec, algs)
{
	std::vector<std::vector<int>> vec = { { 1, 2, 3, 11, 5, 0 },{ 1,2,3,11,5,0 },{ 1,2,3,11,5,0 } };
	auto sh = make_filter_class(vec.begin(), vec.end());
	int amount = 0;
	for (auto i : sh)
		amount++;
	EXPECT_EQ(amount, vec.size());
}
TEST(vec, value)
{
	std::vector<int> vec = { 1,2,3,11,5,0 };
	auto sh = make_filter_class(vec.begin(), vec.end());
	std::set<int> s;
	for (auto i : sh)
	{
		s.insert(i);
	}
	EXPECT_EQ(s.size(), vec.size());
	for (auto i : vec)
	{
		s.insert(i);
	}
	EXPECT_EQ(s.size(), vec.size());
}

TEST(eq_operator, dflt)
{
	std::vector<int> v{ 1 };
	auto sh = make_filter_class(v.begin(), v.end());
	auto sh1 = make_filter_class(v.begin(), v.end());
	EXPECT_FALSE(sh.begin() == sh1.begin());
}

TEST(eq_operator, cnst)
{
	std::vector<int> v{ 1 };
	const auto sh = make_filter_class(v.begin(), v.end());
	const auto sh1 = make_filter_class(v.begin(), v.end());
	EXPECT_FALSE(sh.begin() == sh1.begin());
}
TEST(eq_operator, cnst1)
{
	std::vector<int> v{ 1 };
	const auto sh = make_filter_class(v.cbegin(), v.cend());
	const auto sh1 = make_filter_class(v.cbegin(), v.cend());
	EXPECT_FALSE(sh.begin() == sh1.begin());
}
TEST(cnst_cbegin, operator_star)
{
	std::vector<int> v{ 1 };
	const auto sh = make_filter_class(v.begin(), v.end());
	EXPECT_TRUE((*sh.begin()) == 1);
}
TEST(begin, oper_star)
{
	std::vector<int> v{ 1 };
	auto sh = make_filter_class(v.begin(), v.end());
	*(sh.begin()) = 6;
	EXPECT_TRUE(*sh.begin() == 6);
}

TEST(Test_const_iter_vector_without_pred_, int) {
	vector<int> test{ 5,-9,-8,6,-2 }, result{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i= filter_a.cbegin();i!=filter_a.cend();++i)
		++counter;
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_vector_without_pred, double) {
	vector<double> test = { -0.1,0.5,-8.3,3.6,-7.2 }, result{ -0.1,0.5,-8.3,3.6,-7.2 };
	auto filter_a = make_filter_class(test.cbegin(), test.cend());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_vector_with_pred, int) {
	vector<int> test{ 5,-9,-8,6,-2 }, result{ -9,-8,-2 };
	auto filter_a = make_filter_class(is_negative_number(), test.cbegin(), test.cend());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_vector_with_pred, double) {
	std::vector<double> test = { 0,-1.1,0.5,3.6,-8.3,0.6,0.4,-85.3,12.36,-7.2 }, result{ -1.1,-8.3,-85.3,-7.2 };
	auto filter_a = make_filter_class(is_negative_number(), test.cbegin(), test.cend());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(test_const_invalid_without_pred, begin) {
	vector<int> test{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.cbegin(), test.cbegin());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
		++counter;
	}
	EXPECT_EQ(counter, 0);
}
TEST(test_const_invalid_without_pred, end) {
	vector<int> test{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.cend(), test.cend());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
		++counter;
	}
	EXPECT_EQ(counter, 0);
}
TEST(test_const_unord_map_with_pred, int) {
	std::unordered_map<int, int > test = {
		{ 0, 0 }, { 4, 0 }, { -5, 0 }, { 2, 0 }, { 8, 0 }, { -1, 0 },{9,62},{-95,4} };
	std::vector<int> result{ 8,4,2,9 };
	auto filter_b = make_filter_class(is_positive_pair(), test.cbegin(), test.cend());
	size_t counter = 0;
	for (auto i = filter_b.cbegin(); i!=filter_b.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(test_const_unord_map_without_pred, int) {
	std::unordered_map<int, int > test = {
		{ 0, 0 }, { 4, 0 }, { -5, 0 }, { 2, 0 }, { 8, 0 }, { -1, 0 },{9,62},{-95,4} };
	auto filter_b = make_filter_class(test.cbegin(), test.cend());
	size_t counter = 0;
	for (auto i = filter_b.cbegin(); i!=filter_b.cend(); ++i) {
		++counter;
	}
	EXPECT_EQ(counter, test.size());
}
TEST(test_const_unord_map_with_pred, double) {
	std::unordered_map<double, double > test = {
		{ 2.3, 0 }, { 4.6, 0 }, { -5.9, 0 }, { 2.4, 0 }, { 8.6, 0 }, { -1.345, 0 },{9.3214,62},{-95.3,4} };
	std::vector<double> result{ 4.6,2.3,2.4,9.3214,8.6 };
	auto filter_a = make_filter_class(is_positive_pair(), test.cbegin(), test.cend());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(test_const_unord_map_without_pred, double) {
	std::unordered_map<double, double > test = {
		{ 2.3, 0 }, { 4.6, 0 }, { -5.9, 0 }, { 2.4, 0 }, { 8.6, 0 }, { -1.345, 0 },{9.3214,62},{-95.3,4} };
	auto filter_a = make_filter_class(test.cbegin(), test.cend());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
		++counter;
	}
	EXPECT_EQ(counter, test.size());
}
TEST(test_const_mas_without_pred, int) {
	int mas[count_el] = { 10,20,36,58,95 };
	int test1[count_el] = { 10,20,36,58,95 };
	auto filter_a = make_filter_class(begin(mas), end(mas));
	int counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_const_mas_without_pred, double) {
	double mas[count_el] = { 10.8,20.5,36.9,58.74,95.03 };
	double test1[count_el] = { 10.8,20.5,36.9,58.74,95.03 };
	auto filter_a = make_filter_class(begin(mas), end(mas));
	int counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_const_mas_with_pred, int) {
	int mas[count_el] = { 10,-20,-36,-58,95 };
	int test1[count_el] = { -20,-36,-58 };
	auto filter_a = make_filter_class(is_negative_number(), begin(mas), end(mas));
	int counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, count_el - 2);
}
TEST(test_const_mas_with_pred, double) {
	double mas[count_el] = { 10.8,-20.5,36.9,-58.74,-95.03 };
	double test1[count_el] = { -20.5,-58.74,-95.03 };
	auto filter_a = make_filter_class(is_negative_number(),begin(mas), end(mas));
	int counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, count_el - 2);
}
TEST(test_const_list_without_pred, int) {
	list<int> test{ 5,-9,-8,6,-2 }, result{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
		++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_list_with_pred, int) {
	list<int> test{ 5,-9,-8,6,-2 }, result{ -9,-8,-2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
		++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(test_const_deque_without_pred, int) {
	deque<int> test{ 5,-9,-8,6,-2 }, result{ 5,-9,-8,6,-2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_deque_with_pred, int) {
	deque<int> test{ 5,-9,-8,6,-2 }, result{ -9,-8,-2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_deque_without_pred, double) {
	deque<double> test = { -0.1,0.5,-8.3,3.6,-7.2 }, result{ -0.1,0.5,-8.3,3.6,-7.2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_deque_with_pred, double) {
	std::deque<double> test = { 0,-1.1,0.5,3.6,-8.3,0.6,0.4,-85.3,12.36,-7.2 }, result{ -1.1,-8.3,-85.3,-7.2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
			++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_list_without_pred, double) {
	list<double> test = { -0.1,0.5,-8.3,3.6,-7.2 }, result{ -0.1,0.5,-8.3,3.6,-7.2 };
	auto filter_a = make_filter_class(test.begin(), test.end());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
		++counter;
	}
	EXPECT_EQ(counter, result.size());
}
TEST(Test_const_list_with_pred, double) {
	std::list<double> test = { 0,-1.1,0.5,3.6,-8.3,0.6,0.4,-85.3,12.36,-7.2 }, result{ -1.1,-8.3,-85.3,-7.2 };
	auto filter_a = make_filter_class(is_negative_number(), test.begin(), test.end());
	size_t counter = 0;
	for (auto i = filter_a.cbegin(); i!=filter_a.cend(); ++i) {
		++counter;
	}
	EXPECT_EQ(counter, result.size());
}
GTEST_API_ int main(int argc, char* argv[])
{
	if (argc > 0)
	{
		testing::internal::FilePath arg(argv[0]);
		const auto name = arg.RemoveDirectoryName().RemoveExtension("exe").string();
		testing::GTEST_FLAG(output) = std::string("xml:") + name + ".xml";
	}
	testing::InitGoogleTest(&argc, argv);
#if defined(_MSC_VER)
	testing::UnitTest::GetInstance()->listeners().Append(new testing::MSVCMemoryLeakListener());
#endif // defined(_MSC_VER)
	return RUN_ALL_TESTS();
}