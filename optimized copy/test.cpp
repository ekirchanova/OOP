#include "pch.h"
#include"optim_copy.h"
#include <vector>
#include<string>
#include<list>
#include<deque>
using namespace std;
const size_t count_el = 5;
TEST(Test_vector, int) {
	vector<int> test {5,9,8,6,2}, result(count_el);
	copy::copy(test.begin(), test.end(),result.begin() );
	EXPECT_EQ(test, result);
}
TEST(Test_vector, char) {
	vector<char> test = { 'f','k','j','i','l' }, result(count_el);
	copy::copy(test.begin(), test.end(), result.begin());
	EXPECT_EQ(test, result);
}
TEST(Test_vector, double) {
	vector<double> test = { 0.1,0.5,8.3,3.6,7.2 }, result(count_el);
	copy::copy(test.begin(), test.end(), result.begin());
	EXPECT_EQ(test, result);
}
TEST(test_mas, int) {
	int mas[count_el] = { 10,20,36,58,95 };
	int test1[count_el];
	copy::copy(&mas[0], &mas[count_el], &test1[0]);
	int counter = 0;
	for (size_t i = 0; i < count_el;i++) {
		if (mas[i]==test1[i]) {
			counter++; 
		}
	}
	EXPECT_EQ(counter, count_el);
}

TEST(test_mas_vector, int) {
	int mas[count_el] = { 10,20,36,58,95 };
	vector<int> test1(count_el);
	copy::copy(begin(mas), end(mas),begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas[i] == test1.at(i)) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_vector_mas, int) {
	vector<int> mas { 10,20,36,58,95 };
	int test1[count_el];
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas.at(i) == test1[i]) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_mas_vector, int_double) {
	int mas[count_el] = { 10,20,36,58,95 };
	vector<double> test1(count_el);
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas[i] == test1.at(i)) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_vector_mas, double_int) {
	vector<double> mas{ 10,20,36,58,95 };
	int test1[count_el];
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas.at(i) == test1[i]) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_mas_vector, int_unsign_int) {
	int mas[count_el] = { 10,20,36,58,95 };
	vector<unsigned int> test1(count_el);
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas[i] == test1.at(i)) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_vector_mas, unsign_int_int) {
	vector<unsigned int> mas{ 10,20,36,58,95 };
	int test1[count_el];
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas.at(i) == test1[i]) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_mas_vector, unsign_int_int) {
	unsigned int mas[count_el] = { 10,20,36,58,95 };
	vector<int> test1(count_el);
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas[i] == test1.at(i)) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_vector_mas, int_unsign_int) {
	vector<int> mas{ 10,20,36,58,95 };
	unsigned int test1[count_el];
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas.at(i) == test1[i]) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_string, str) {
	string test("abdkdidfb;bktr"),result(14,' ');
	copy::copy(test.begin(), test.end(), result.begin());
	EXPECT_EQ(test, result);
}
struct test_str {
	int number;
	string name;
};

TEST(test_mas, char) {
	char mas[count_el] = { 'f','k','j','i','l' };
	char test1[count_el];
	copy::copy(&mas[0], &mas[count_el], &test1[0]);
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas[i] == test1[i]) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_mas, double) {
	double mas[count_el] = { 0.1,0.5,8.3,3.6,7.2 };
	double test1[count_el];
	copy::copy(&mas[0], &mas[count_el], &test1[0]);
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		if (mas[i] == test1[i]) {
			counter++;
		}
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_nevalid, begin) {
	vector<int> test{ 5,9,8,6,2 }, result(1);
	copy::copy(test.begin(), test.begin(), result.begin());
	EXPECT_EQ(result.size(), 1);
}
TEST(test_nevalid, source_end) {
	vector<int> test{ 5,9,8,6,2 }, result(1);
	copy::copy(test.end(), test.end(), result.begin());
	EXPECT_EQ(result.size(), 1);
}
TEST(test_nevalid, end_end) {
	vector<int> test{ 5,9,8,6,2 }, result(1);
	copy::copy(test.end(), test.end(), result.end());
	EXPECT_EQ(result.size(), 1);
}
TEST(test_list, int) {
	list<int> test = { 20,30,65,109,54,74 },result(6);
	copy::copy(test.begin(), test.end(), result.begin());
	EXPECT_EQ(result, test);
}
TEST(test_mas_list, int) {
	int mas[count_el] = { 10,20,36,58,95 };
	list<int> test1(count_el);
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
			counter++;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_list_mas, int) {
	list<int> mas { 10,20,36,58,95 };
	int test1[count_el];
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		counter++;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_list_mas, int_double) {
	list<int> mas{ 10,20,36,58,95 };
	double test1[count_el];
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		counter++;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_vector_list, int) {
	vector<int> mas{ 10,20,36,58,95 };
	list<int> test1(count_el);
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		counter++;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_list_vector, int) {
	list<int> mas{ 10,20,36,58,95 };
	vector <int> test1(count_el);
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		counter++;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_vector_list, int_double) {
	vector<int> mas{ 10,20,36,58,95 };
	list<double> test1(count_el);
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		counter++;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_list_vector, double_int) {
	list<double> mas{ 10,20,36,58,95 };
	vector <int> test1(count_el);
	copy::copy(begin(mas), end(mas), begin(test1));
	int counter = 0;
	for (size_t i = 0; i < count_el; i++) {
		counter++;
	}
	EXPECT_EQ(counter, count_el);
}
TEST(test_deque, int) {
	deque<int> test = { 20,30,65,109,54,74 }, result(6);
	copy::copy(test.begin(), test.end(), result.begin());
	EXPECT_EQ(result, test);
}
TEST(Test_vector_dif_type, int_double) {
	vector<int> test{ 5,9,8,6,2 };
	vector<double> result(count_el);
	vector<double> test2{ 5,9,8,6,2 };
	copy::copy(test.begin(), test.end(), result.begin());
	size_t counter;
	EXPECT_EQ(result, test2);
}
TEST(Test_vector_dif_type, int_unsigned_int) {
	vector<int> test{ 5,9,8,6,2 };
	vector<unsigned int> result(count_el);
	vector<unsigned int> test2{ 5,9,8,6,2 };
	copy::copy(test.begin(), test.end(), result.begin());
	size_t counter;
	EXPECT_EQ(result, test2);
}
TEST(Test_vector_dif_type, int_long_long) {
	vector<int> test{ 5,9,8,6,2 };
	vector<long long> result(count_el);
	vector<long long> test2{ 5,9,8,6,2 };
	copy::copy(test.begin(), test.end(), result.begin());
	size_t counter;
	EXPECT_EQ(result, test2);
}
TEST(Test_vector_dif_type, int_long) {
	vector<int> test{ 5,9,8,6,2 };
	vector<long > result(count_el);
	vector<long> test2{ 5,9,8,6,2 };
	copy::copy(test.begin(), test.end(), result.begin());
	size_t counter;
	EXPECT_EQ(result, test2);
}