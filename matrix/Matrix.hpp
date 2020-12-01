#pragma once
class Matrix final {
private:
	double* matrix;
	size_t Cols;
	size_t Rows;
	bool swap_rows(size_t index);
	bool double_compare(double value_1, double value_2) const;
	bool compare_with_zero(double value) const;
	bool check_diag() const;
	Matrix findminor(size_t colId, size_t rowId) const ;
	size_t size() const;
public:
	Matrix();
	Matrix(size_t cols);
	Matrix(size_t rows, size_t cols);
	~Matrix();

	Matrix(const Matrix& mat);
	Matrix operator*(const Matrix& mat) const;
	Matrix operator-(const Matrix& mat) const;
	Matrix operator+(const Matrix& mat) const;

	Matrix operator*(double value) const;
	Matrix operator/(double value) const;

	Matrix& operator=(const Matrix& mat);
	Matrix& operator*=(const Matrix& mat);
	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);

	Matrix& operator*=(double value);
	Matrix& operator/=(double value);
	bool isValid() const ;

	void resize(size_t rows, size_t cols);

	const double& coeffRef(size_t rowIdx, size_t colIdx) const;
	double& coeffRef(size_t rowIdx, size_t colIdx);

	const double* data() const;
	double* data();

	size_t rows() const;
	size_t cols() const;

	Matrix& setIdentity();
	Matrix& setZero();
	Matrix& setConstants(double value);

	Matrix& setIdentity(size_t rows, size_t cols);
	Matrix& setZero(size_t rows, size_t cols);
	Matrix& setConstants(size_t rows, size_t cols, double value);

	Matrix diag() const;
	Matrix transpose()const;
	Matrix inverse() const;
	double det()const;

	Matrix static identity(size_t rows, size_t cols);
	Matrix static zeros(size_t rows, size_t cols);
	Matrix static constants(size_t rows, size_t cols, double value);

	friend Matrix operator*(double value, const Matrix& mat);
};
