#include"Matrix.hpp"
#include<iostream>
Matrix::Matrix()
{
	Cols = 0;			  //задаем дефолтные значения
	Rows = 0;
	matrix = nullptr;
}
Matrix::Matrix(size_t cols)	   
{
	Rows = 1;					//матрица - столбец
	Cols = cols;
	matrix = new double[Cols*Rows];

}
Matrix::Matrix(size_t rows, size_t cols)
{
	Cols = cols;					  //задаем требуемые параметры матрицы
	Rows = rows;
	matrix = new double[Cols*Rows];
}
Matrix::~Matrix() {
	delete[] matrix;   //удаляем массив с данными
}
bool  Matrix::isValid() const {
	return!(Cols == 0 || Rows == 0);	//проверяем на валидность
}

Matrix::Matrix(const Matrix& mat)// копируем матрицу
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
	Matrix composition(Rows, mat.Cols);	 //результатом умножения будет новая матрица, нового размера
	size_t i = 0;
	for (size_t rowId = 0; rowId < Rows; rowId++) {
		for (size_t colId = 0; colId < mat.Cols; colId++) {		   
			composition.matrix[i] = 0;				
			for (size_t j = 0; j < Cols; j++)			//цикл по строчкам и столбцам
			{
				composition.matrix[i] += matrix[rowId*Cols + j] * mat.matrix[colId + j * mat.Cols];	//собственно умножаем строчку на столбец, по правилу умножений матриц
			}
			i++;
		}
	}
	return composition;	   //возвращаем новую матрицу
}
Matrix Matrix::operator-(const Matrix& mat)const
{
	if (Cols != mat.Cols || Rows != mat.Rows || !mat.isValid() || !isValid())	//проверка на то, что мы можем вычитать
		return Matrix();
	Matrix difference(Rows, Cols);		 //новая матрица
	for (size_t i = 0; i < Rows*Cols; i++) {
		difference.matrix[i] = matrix[i] - mat.matrix[i];	 //поэлементно вычитаем
	}
	return difference;
}
Matrix Matrix::operator+(const Matrix& mat) const
{
	if (Cols != mat.Cols || Rows != mat.Rows || !mat.isValid() || !isValid())	   //проверка на то, что можем складывать
		return Matrix();
	Matrix sum(Rows, Cols);								 //новая матрица
	for (size_t i = 0; i < Rows*Cols; i++) {
		sum.matrix[i] = matrix[i] + mat.matrix[i];	  //поэлементно складываем
	}
	return sum;
}
Matrix Matrix::operator*(double value) const 
{
	if (isnan(value) || !isValid())			 //проверяем , что можем умножить, если не можем, вовращаем дефолтную пустую матрицу
		return Matrix();
	Matrix composition(*this);			   //новая домноженная матрица
	for (size_t i = 0; i < Rows*Cols; i++) {
		composition.matrix[i] *= value;		   //поэлементно умножаем на константу
	}
	return composition;
}
Matrix Matrix::operator/(double value) const   //деление 
{
	if (double_compare(value, 0) || isnan(value) || !isValid())	  //снова проверка
		return Matrix();
	Matrix division(*this);			  //новая матрица
	for (size_t i = 0; i < Rows*Cols; i++) {
		division.matrix[i] /= value;				 //поэлементно делим на константу
	}
	return division;
}
Matrix& Matrix:: operator=(const Matrix& mat) {
	if (!mat.isValid()) {					//если хотим приравнять к невалидной, делаем невалидной текущую и возвращаем её
		delete[] matrix;
		Cols = Rows = 0;
		matrix = nullptr;
		return *this;
	}
	if (matrix == mat.data()) return *this;			//если данные в матрицах равны, то приравнивать уже не надо, просто возвращаем текущую
	if ((Cols != mat.Cols) || (Rows != mat.Rows))
		resize(mat.Rows, mat.Cols);					   //если разные размеры, приводим нашу к размерам той, к которой хотим приравнять
	memcpy(matrix, mat.matrix, size() * sizeof(double));			 //копируем данные
	return *this;
}
Matrix& Matrix::operator *=(const Matrix& mat)
{
	if (Cols != mat.Rows || !mat.isValid() || !isValid()) {	//проверка на валидноость

		delete[] matrix;
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	*this = *this * mat; //приравниваем текущую к новой, которая результат умножения текущей на mat
	return *this;
}
Matrix& Matrix::operator -=(const Matrix& mat)
{																	 
	if (Cols != mat.Cols || Rows != mat.Rows || !mat.isValid() || !isValid())
	{
		delete[] matrix;											 //проверка на валидность
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	*this = *this - mat;			//приравниваем нашу матрицу к новой, которая результат вычитания текущий с mat
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
	*this = *this + mat;			   //аналогично -=, см.выше
	return *this;
}
Matrix& Matrix::operator *=(double value)
{
	if (!isValid() || isnan(value)) {	 //проверка что дали норм число и матрица валидно
		delete[] matrix;
		Rows = Cols = 0;
		matrix = nullptr;
		return *this;
	}
	*this = *this * value;	   //приравниваем к домноженной на константу
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
	*this = *this / value;			   //аналогично приравниванию с домножением 
	return *this;
}
size_t Matrix::rows() const {
	return Rows;
}
size_t Matrix::cols() const {
	return Cols;
}
void Matrix::resize(size_t rows, size_t cols) {	   
	delete[]matrix;								  //удаляем данные
	if ((rows == 0) || (cols == 0)) {
		Cols = Rows = 0;			//если новые размеры нулевые, то и матрица невалидная
		matrix = nullptr;
	}
	else {
		Cols = cols;			   //задаем новые размеры
		Rows = rows;
		matrix = new double[Rows* Cols];
		for (size_t i = 0; i < Cols*Rows; i++)
			matrix[i] = 0;						 //заполняем нулями
	}
}
const double& Matrix::coeffRef(size_t rowIdx, size_t colIdx) const {
	if ((rowIdx >= Rows) || (colIdx >= Cols))						 //если дали некорректные индексы, кидаем исключение
		throw std::out_of_range("Error!No such element!");
	return(matrix[rowIdx*Cols + colIdx]);		//возвращаем элемент					 
}
double& Matrix::coeffRef(size_t rowIdx, size_t colIdx) {
	if ((rowIdx >= Rows) || (colIdx >= Cols))					//аналогично тому, что выше
		throw std::out_of_range("Error!No such element!");
	return(matrix[rowIdx*Cols + colIdx]);
}
const double* Matrix::data() const {
	if ((Cols == 0) || (Rows == 0))	   //возвращаем массив с данными
		return nullptr;
	return(matrix);
}
double* Matrix::data() {
	if ((Cols == 0) || (Rows == 0))		//возвращаем массив с данными
		return nullptr;
	return(matrix);
}
Matrix& Matrix::setIdentity() //делаем матрицу единичной
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
Matrix& Matrix::setZero() { //заполняем нулями
	if (!isValid()) {
		delete[] matrix;
		Cols = Rows = 0;
		matrix = nullptr;
		return *this;
	}
	memset(matrix, 0, size() * sizeof(double));
	return *this;
}
Matrix& Matrix::setConstants(double value) {//заполняем каким-то значением 
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
Matrix& Matrix::setIdentity(size_t rows, size_t cols)// меняем размеры и делаем единичной
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
Matrix& Matrix::setZero(size_t rows, size_t cols)// меняем размеры и заполняем нулями
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

Matrix& Matrix::setConstants(size_t rows, size_t cols, double value) // меняем размеры и заполняем каким-то числом
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
	Matrix identity(rows, cols);				   //создаем новую матрицу заданного размера
	memset(identity.matrix, 0, identity.size() * sizeof(double));		   //заполняем нулями
	for (size_t i = 0; i < identity.size(); i = i + cols + 1) {
		identity.matrix[i] = 1.0;					   //на диагонали ставим единички
	}
	return identity;
}
Matrix Matrix::zeros(size_t rows, size_t cols) {
	if ((rows == 0) || (cols == 0)) {
		return Matrix();
	}
	Matrix zero(rows, cols);					 //создаем новую с заданными параметрами
	memset(zero.matrix, 0, zero.size() * sizeof(double));	//заполняем нулями
	return zero;
}
Matrix Matrix::constants(size_t rows, size_t cols, double value) {
	if ((rows == 0) || (cols == 0) || (isnan(value) == true)) {
		return Matrix();
	}
	Matrix constant(rows, cols);				//создаем новую
	for (size_t i = 0; i < constant.size(); i++)
		constant.matrix[i] = value;		   //поэлементно приравниваем к константе
	return constant;
}
Matrix operator*(double value, const Matrix& mat)
{
	if (isnan(value) || !mat.isValid()) {
		return Matrix();
	}
	Matrix composition(mat.Rows, mat.Cols);			   //создаем новую матрицу
	for (size_t i = 0; i < mat.Cols*mat.Rows; i++) {
		composition.matrix[i] = value * mat.matrix[i];	//поэлементно умножаем на константу
	}
	return composition;
}
Matrix Matrix::transpose() const
{
	if (!isValid())
		return Matrix();
	Matrix transpose(Cols, Rows);	   //создаем новую перевернутую
	size_t i = 0;
	for (size_t ind_cols = 0; ind_cols < Cols; ind_cols++)
		for (size_t ind_rows = 0; ind_rows < Rows*Cols; ind_rows = ind_rows + Cols) {
			transpose.matrix[i] = matrix[ind_cols + ind_rows];		//у новой матрицы индексы значений меняются местами
			i++;
		}

	return transpose;
}
bool Matrix::swap_rows(size_t index)
{
	size_t p = 1, num_rows = index / Cols;//вычисляем номер строки и задаем переменную, которая будет проверять не вышли  ли за пределы массива
	double *temp = new double[Cols];
	while (!compare_with_zero(matrix[index]) && (p*Cols < (size() - num_rows * Cols)))// меняем строки местами
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
bool Matrix::double_compare(double value_1, double value_2) const//сравниваем между собой два числа типа double 
{
	const double e = 1e-10;
	return (value_1 - value_2 < e);
}
bool Matrix::compare_with_zero(double value) const {//сравниваем числа типа double с 0
	return value != 0;
}
Matrix Matrix::diag() const						//создаем верхнетреугольную матрицу(то есть нет элементов ниже главной диагонали)
{
	if (!isValid()) {
		return Matrix();
	}
	if (check_diag()) {
		return *this;
	}
	size_t index = 0;
	Matrix diag(*this), copy(*this); //создаем две копии матрицы, чтобы не потерять элементы при диагонализации 
	for (size_t elInd = 0; elInd < size() - Cols; elInd = elInd + Cols + 1) {// elind нужный нам элемент. стоящий на главной диагонали 
		if (!compare_with_zero(copy.matrix[elInd])) {		//проверяем ноль на нужной позиции(т.к в нашей матрице элементы только выше верхней диагонали и на ней, то первый элемент в строке-
			index = elInd;									//это элемент главной диагонали, значит, если на этой позиции ноль , значит надо поменять с другой строкой, где не ноль , чтоб удобнее
			if (!copy.swap_rows(index) ) break;				// было работать дальше)
			diag = copy;
		}
		for (size_t rowsInd = (elInd / Cols + 1) * Cols + elInd % Cols; rowsInd < size(); rowsInd = rowsInd + Cols) {	// теперь надо занулить все элементы нашего столбца ниже, чтобы матрица приняла диагональный вид
			if (!compare_with_zero(copy.matrix[rowsInd]))																//если на нужной нам позиции ноль, то нам не надо ничего менять , идем к следующей строке
				continue;
			double coef = -copy.matrix[rowsInd] / copy.matrix[elInd];								//считаем коэффицент, на который будет домножать, чтобы занулить нужный нам в строке
			for (size_t colInd = 0; colInd < Cols - elInd % Cols; ++colInd) {
				diag.matrix[rowsInd + colInd] = copy.matrix[rowsInd + colInd] + (coef * copy.matrix[elInd + colInd]); // меняем коэффициенты
			}

		}
		copy = diag;		//копируем, чтоб было удобнее работать и не запутаться 
	}
	return diag;
}
bool  Matrix::check_diag() const {			//проверяем диагонализирована ли матрица, чтоб не делать это снова
	for (size_t elInd = 0, number_rows = 1; elInd < size(); elInd = elInd + Cols, ++number_rows) {
		for (size_t i = 0; i < number_rows; ++i)
			if (!matrix[elInd + i])
				return false;

	}
	return true;
}
double Matrix::det() const // считаем определитель матрицы
{
	if (Cols != Rows || !isValid()) {
		return NAN;
	}
	if (Rows == 1) {
		return matrix[0];
	}
	double det = 1;
	Matrix copy(*this); // копируем, чтоб диагонализировать, т.к знаем, что определитель матрицы диагональной-это произведение элементов главной диагонали 
	if (!copy.check_diag()) {
		copy = copy.diag();
	}
	for (size_t i = 0; i < size(); i = i + Cols + 1) {// считаем произведение
		det = det * copy.matrix[i];
	}
	return det;
}



