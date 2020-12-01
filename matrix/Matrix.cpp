#include"Matrix.hpp"
#include<iostream>
Matrix::Matrix()
{
	Cols = 0;			  //������ ��������� ��������
	Rows = 0;
	matrix = nullptr;
}
Matrix::Matrix(size_t cols)	   
{
	Rows = 1;					//������� - �������
	Cols = cols;
	matrix = new double[Cols*Rows];

}
Matrix::Matrix(size_t rows, size_t cols)
{
	Cols = cols;					  //������ ��������� ��������� �������
	Rows = rows;
	matrix = new double[Cols*Rows];
}
Matrix::~Matrix() {
	delete[] matrix;   //������� ������ � �������
}
bool  Matrix::isValid() const {
	return!(Cols == 0 || Rows == 0);	//��������� �� ����������
}

Matrix::Matrix(const Matrix& mat)// �������� �������
{
	if (!mat.isValid()) {
		Cols = Rows = 0;
		matrix = nullptr;
		return;
	}
	Cols = mat.Cols;
	Rows = mat.Rows;
	matrix = new double[Cols*Rows];
	memcpy(matrix, mat.matrix, size() * sizeof(double));
}
size_t Matrix::size()const {
	return Cols * Rows;
}
Matrix Matrix::operator*(const Matrix& mat)const
{
	if (Cols != mat.Rows || !mat.isValid() || !isValid()) {
		return Matrix();
	}
	Matrix composition(Rows, mat.Cols);	 //����������� ��������� ����� ����� �������, ������ �������
	size_t i = 0;
	for (size_t rowId = 0; rowId < Rows; rowId++) {
		for (size_t colId = 0; colId < mat.Cols; colId++) {		   
			composition.matrix[i] = 0;				
			for (size_t j = 0; j < Cols; j++)			//���� �� �������� � ��������
			{
				composition.matrix[i] += matrix[rowId*Cols + j] * mat.matrix[colId + j * mat.Cols];	//���������� �������� ������� �� �������, �� ������� ��������� ������
			}
			i++;
		}
	}
	return composition;	   //���������� ����� �������
}
Matrix Matrix::operator-(const Matrix& mat)const
{
	if (Cols != mat.Cols || Rows != mat.Rows || !mat.isValid() || !isValid())	//�������� �� ��, ��� �� ����� ��������
		return Matrix();
	Matrix difference(Rows, Cols);		 //����� �������
	for (size_t i = 0; i < Rows*Cols; i++) {
		difference.matrix[i] = matrix[i] - mat.matrix[i];	 //����������� ��������
	}
	return difference;
}
Matrix Matrix::operator+(const Matrix& mat) const
{
	if (Cols != mat.Cols || Rows != mat.Rows || !mat.isValid() || !isValid())	   //�������� �� ��, ��� ����� ����������
		return Matrix();
	Matrix sum(Rows, Cols);								 //����� �������
	for (size_t i = 0; i < Rows*Cols; i++) {
		sum.matrix[i] = matrix[i] + mat.matrix[i];	  //����������� ����������
	}
	return sum;
}
Matrix Matrix::operator*(double value) const 
{
	if (isnan(value) || !isValid())			 //��������� , ��� ����� ��������, ���� �� �����, ��������� ��������� ������ �������
		return Matrix();
	Matrix composition(*this);			   //����� ����������� �������
	for (size_t i = 0; i < Rows*Cols; i++) {
		composition.matrix[i] *= value;		   //����������� �������� �� ���������
	}
	return composition;
}
Matrix Matrix::operator/(double value) const   //������� 
{
	if (double_compare(value, 0) || isnan(value) || !isValid())	  //����� ��������
		return Matrix();
	Matrix division(*this);			  //����� �������
	for (size_t i = 0; i < Rows*Cols; i++) {
		division.matrix[i] /= value;				 //����������� ����� �� ���������
	}
	return division;
}
Matrix& Matrix:: operator=(const Matrix& mat) {
	if (!mat.isValid()) {					//���� ����� ���������� � ����������, ������ ���������� ������� � ���������� �
		delete[] matrix;
		Cols = Rows = 0;
		matrix = nullptr;
		return *this;
	}
	if (matrix == mat.data()) return *this;			//���� ������ � �������� �����, �� ������������ ��� �� ����, ������ ���������� �������
	if ((Cols != mat.Cols) || (Rows != mat.Rows))
		resize(mat.Rows, mat.Cols);					   //���� ������ �������, �������� ���� � �������� ���, � ������� ����� ����������
	memcpy(matrix, mat.matrix, size() * sizeof(double));			 //�������� ������
	return *this;
}
Matrix& Matrix::operator *=(const Matrix& mat)
{
	if (Cols != mat.Rows || !mat.isValid() || !isValid()) {	//�������� �� �����������

		delete[] matrix;
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	*this = *this * mat; //������������ ������� � �����, ������� ��������� ��������� ������� �� mat
	return *this;
}
Matrix& Matrix::operator -=(const Matrix& mat)
{																	 
	if (Cols != mat.Cols || Rows != mat.Rows || !mat.isValid() || !isValid())
	{
		delete[] matrix;											 //�������� �� ����������
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	*this = *this - mat;			//������������ ���� ������� � �����, ������� ��������� ��������� ������� � mat
	return *this;
}
Matrix& Matrix::operator +=(const Matrix& mat)
{
	if (Cols != mat.Cols || Rows != mat.Rows || !mat.isValid() || !isValid())
	{
		delete[] matrix;
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	*this = *this + mat;			   //���������� -=, ��.����
	return *this;
}
Matrix& Matrix::operator *=(double value)
{
	if (!isValid() || isnan(value)) {	 //�������� ��� ���� ���� ����� � ������� �������
		delete[] matrix;
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	*this = *this * value;	   //������������ � ����������� �� ���������
	return *this;
}
Matrix& Matrix::operator /=(double value)
{
	if (double_compare(value, 0) || isnan(value) || !isValid()) {
		delete[] matrix;
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	*this = *this / value;			   //���������� ������������� � ����������� 
	return *this;
}
size_t Matrix::rows() const {
	return Rows;
}
size_t Matrix::cols() const {
	return Cols;
}
void Matrix::resize(size_t rows, size_t cols) {	   
	delete[]matrix;								  //������� ������
	if ((rows == 0) || (cols == 0)) {
		Cols = Rows = 0;			//���� ����� ������� �������, �� � ������� ����������
		matrix = nullptr;
	}
	else {
		Cols = cols;			   //������ ����� �������
		Rows = rows;
		matrix = new double[Rows* Cols];
		for (size_t i = 0; i < Cols*Rows; i++)
			matrix[i] = 0;						 //��������� ������
	}
}
const double& Matrix::coeffRef(size_t rowIdx, size_t colIdx) const {
	if ((rowIdx >= Rows) || (colIdx >= Cols))						 //���� ���� ������������ �������, ������ ����������
		throw std::out_of_range("Error!No such element!");
	return(matrix[rowIdx*Cols + colIdx]);		//���������� �������					 
}
double& Matrix::coeffRef(size_t rowIdx, size_t colIdx) {
	if ((rowIdx >= Rows) || (colIdx >= Cols))					//���������� ����, ��� ����
		throw std::out_of_range("Error!No such element!");
	return(matrix[rowIdx*Cols + colIdx]);
}
const double* Matrix::data() const {
	if ((Cols == 0) || (Rows == 0))	   //���������� ������ � �������
		return nullptr;
	return(matrix);
}
double* Matrix::data() {
	if ((Cols == 0) || (Rows == 0))		//���������� ������ � �������
		return nullptr;
	return(matrix);
}
Matrix& Matrix::setIdentity() //������ ������� ���������
{
	if (!isValid()) {
		delete[] matrix;
		Cols = Rows = 0;
		matrix = nullptr;
		return *this;
	}
	memset(matrix, 0, size() * sizeof(double));
	for (size_t i = 0; i < size(); i = i + Cols + 1) {
		matrix[i] = 1.0;
	}
	return *this;
}
Matrix& Matrix::setZero() { //��������� ������
	if (!isValid()) {
		delete[] matrix;
		Cols = Rows = 0;
		matrix = nullptr;
		return *this;
	}
	memset(matrix, 0, size() * sizeof(double));
	return *this;
}
Matrix& Matrix::setConstants(double value) {//��������� �����-�� ��������� 
	if (isnan(value) || !isValid()) {
		delete[] matrix;
		Cols = Rows = 0;
		matrix = nullptr;
		return *this;
	}
	for (size_t i = 0; i < size(); i++)
		matrix[i] = value;
	return *this;
}
Matrix& Matrix::setIdentity(size_t rows, size_t cols)// ������ ������� � ������ ���������
{
	if (!isValid()) {
		delete[] matrix;
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	if (Rows != rows || Cols != cols)
		resize(rows, cols);
	else
		memset(matrix, 0, size() * sizeof(double));
	for (size_t i = 0; i < size(); i = i + Cols + 1) {
		matrix[i] = 1.0;
	}
	return *this;
}
Matrix& Matrix::setZero(size_t rows, size_t cols)// ������ ������� � ��������� ������
{
	if (!isValid()) {
		delete[] matrix;
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	if ((Rows != rows) && (Cols != cols))
		resize(rows, cols);
	else
		memset(matrix, 0, size() * sizeof(double));

	return *this;
}

Matrix& Matrix::setConstants(size_t rows, size_t cols, double value) // ������ ������� � ��������� �����-�� ������
{
	if (isnan(value) || !isValid()) {
		delete[] matrix;
		Cols = Rows = 0;
		matrix = nullptr;
		return *this;
	}
	if ((Rows != rows) && (Cols != cols))
		resize(rows, cols);
	for (size_t i = 0; i < size(); i++)
		matrix[i] = value;
	return *this;
}
Matrix  Matrix::identity(size_t rows, size_t cols)
{
	if (rows == 0 || cols == 0) {
		return Matrix();
	}
	Matrix identity(rows, cols);				   //������� ����� ������� ��������� �������
	memset(identity.matrix, 0, identity.size() * sizeof(double));		   //��������� ������
	for (size_t i = 0; i < identity.size(); i = i + cols + 1) {
		identity.matrix[i] = 1.0;					   //�� ��������� ������ ��������
	}
	return identity;
}
Matrix Matrix::zeros(size_t rows, size_t cols) {
	if ((rows == 0) || (cols == 0)) {
		return Matrix();
	}
	Matrix zero(rows, cols);					 //������� ����� � ��������� �����������
	memset(zero.matrix, 0, zero.size() * sizeof(double));	//��������� ������
	return zero;
}
Matrix Matrix::constants(size_t rows, size_t cols, double value) {
	if ((rows == 0) || (cols == 0) || (isnan(value) == true)) {
		return Matrix();
	}
	Matrix constant(rows, cols);				//������� �����
	for (size_t i = 0; i < constant.size(); i++)
		constant.matrix[i] = value;		   //����������� ������������ � ���������
	return constant;
}
Matrix operator*(double value, const Matrix& mat)
{
	if (isnan(value) || !mat.isValid()) {
		return Matrix();
	}
	Matrix composition(mat.Rows, mat.Cols);			   //������� ����� �������
	for (size_t i = 0; i < mat.Cols*mat.Rows; i++) {
		composition.matrix[i] = value * mat.matrix[i];	//����������� �������� �� ���������
	}
	return composition;
}
Matrix Matrix::transpose() const
{
	if (!isValid())
		return Matrix();
	Matrix transpose(Cols, Rows);	   //������� ����� ������������
	size_t i = 0;
	for (size_t ind_cols = 0; ind_cols < Cols; ind_cols++)
		for (size_t ind_rows = 0; ind_rows < Rows*Cols; ind_rows = ind_rows + Cols) {
			transpose.matrix[i] = matrix[ind_cols + ind_rows];		//� ����� ������� ������� �������� �������� �������
			i++;
		}

	return transpose;
}
bool Matrix::swap_rows(size_t index)
{
	size_t p = 1, num_rows = index / Cols;//��������� ����� ������ � ������ ����������, ������� ����� ��������� �� �����  �� �� ������� �������
	double *temp = new double[Cols];
	while (!compare_with_zero(matrix[index]) && (p*Cols < (size() - num_rows * Cols)))// ������ ������ �������
	{
		for (size_t j = 0; j < Cols; j++)
			temp[j] = matrix[num_rows *Cols + j];
		for (size_t i = 0; i < Cols; i++)
			matrix[num_rows *Cols + i] = matrix[num_rows *Cols + i + p * Cols];
		for (size_t i = 0; i < Cols; i++)
			matrix[num_rows *Cols + p * Cols + i] = temp[i];
		p++;
	}
	delete[]temp;
	if (!compare_with_zero(matrix[index]) || (p*Cols < (size() - num_rows * Cols))) {
		return true;
	}
	return false;


}
bool Matrix::double_compare(double value_1, double value_2) const//���������� ����� ����� ��� ����� ���� double 
{
	const double e = 1e-10;
	return (value_1 - value_2 < e);
}
bool Matrix::compare_with_zero(double value) const {//���������� ����� ���� double � 0
	return value != 0;
}
Matrix Matrix::diag() const						//������� ����������������� �������(�� ���� ��� ��������� ���� ������� ���������)
{
	if (!isValid()) {
		return Matrix();
	}
	if (check_diag()) {
		return *this;
	}
	size_t index = 0;
	Matrix diag(*this), copy(*this); //������� ��� ����� �������, ����� �� �������� �������� ��� �������������� 
	for (size_t elInd = 0; elInd < size() - Cols; elInd = elInd + Cols + 1) {// elind ������ ��� �������. ������� �� ������� ��������� 
		if (!compare_with_zero(copy.matrix[elInd])) {		//��������� ���� �� ������ �������(�.� � ����� ������� �������� ������ ���� ������� ��������� � �� ���, �� ������ ������� � ������-
			index = elInd;									//��� ������� ������� ���������, ������, ���� �� ���� ������� ���� , ������ ���� �������� � ������ �������, ��� �� ���� , ���� �������
			if (!copy.swap_rows(index) ) break;				// ���� �������� ������)
			diag = copy;
		}
		for (size_t rowsInd = (elInd / Cols + 1) * Cols + elInd % Cols; rowsInd < size(); rowsInd = rowsInd + Cols) {	// ������ ���� �������� ��� �������� ������ ������� ����, ����� ������� ������� ������������ ���
			if (!compare_with_zero(copy.matrix[rowsInd]))																//���� �� ������ ��� ������� ����, �� ��� �� ���� ������ ������ , ���� � ��������� ������
				continue;
			double coef = -copy.matrix[rowsInd] / copy.matrix[elInd];								//������� ����������, �� ������� ����� ���������, ����� �������� ������ ��� � ������
			for (size_t colInd = 0; colInd < Cols - elInd % Cols; ++colInd) {
				diag.matrix[rowsInd + colInd] = copy.matrix[rowsInd + colInd] + (coef * copy.matrix[elInd + colInd]); // ������ ������������
			}

		}
		copy = diag;		//��������, ���� ���� ������� �������� � �� ���������� 
	}
	return diag;
}
bool  Matrix::check_diag() const {			//��������� ����������������� �� �������, ���� �� ������ ��� �����
	for (size_t elInd = 0, number_rows = 1; elInd < size(); elInd = elInd + Cols, ++number_rows) {
		for (size_t i = 0; i < number_rows; ++i)
			if (!matrix[elInd + i])
				return false;

	}
	return true;
}
double Matrix::det() const // ������� ������������ �������
{
	if (Cols != Rows || !isValid()) {
		return NAN;
	}
	if (Rows == 1) {
		return matrix[0];
	}
	double det = 1;
	Matrix copy(*this); // ��������, ���� �����������������, �.� �����, ��� ������������ ������� ������������-��� ������������ ��������� ������� ��������� 
	if (!copy.check_diag()) {
		copy = copy.diag();
	}
	for (size_t i = 0; i < size(); i = i + Cols + 1) {// ������� ������������
		det = det * copy.matrix[i];
	}
	return det;
}



