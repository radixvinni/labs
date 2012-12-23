#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <emmintrin.h>
#include <time.h>

#define pi 3.14159265
#define e exp(1.0)

// матрица узлов решетки
double X[200][200];
// старые значения узлов для посчета eps
double X_old[200][200];
// граничные условия
double X0[200], Y0[200], X1[200], Y1[200];

double eps;

int n;		/* Размерность матрицы n*n*/

double x_0(int i)
{
	double h = i+1;
	h/= (n+1);
	return sin(pi * h);
}


double x_1(int i)
{
	double h = i+1;
	h /= (n+1);
	double a = pow(e, -h);
	return sin(pi * h)*a;
}

double y_0(int i)
{
	return 0;
}

double y_1(int i)
{
	return 0;
}


// Вычисление двух точек по методу Гаусса-Зейделя
// в узлах i, j и i+2, j
__m128d Gauss_Zeid(int i, int j)
{
	__m128d sum;
	if (i != 0)
		sum = _mm_setr_pd(X[i-1][j],X[i+1][j]);
	else
		sum = _mm_setr_pd(X0[j],X[i+1][j]);

	if (i+3 != n)
		sum = _mm_add_pd(sum , _mm_setr_pd(X[i+1][j],X[i+3][j]));
	else
		sum = _mm_add_pd(sum , _mm_setr_pd(X[i+1][j],X1[j]));


	if (j != 0)
		sum = _mm_add_pd(sum , _mm_setr_pd(X[i][j-1],X[i+2][j-1]));
	else
		sum = _mm_add_pd(sum , _mm_setr_pd(Y0[i],Y0[i+2]));

	if (j != n-1)
		sum = _mm_add_pd(sum , _mm_setr_pd(X[i][j+1],X[i+2][j+1]));
	else
		sum = _mm_add_pd(sum , _mm_setr_pd(Y1[i],Y1[i+2]));

	return _mm_div_pd(sum , _mm_setr_pd(4.0, 4.0));
}

// инициализации начальных значений X и Х_old
void init_x()
{
	int i = 0, j = 0;
	while(i < n)
	{
		j = 0;
		while(j < n)
		{
			X[i][j] = 0;
			X_old[i][j] = 0;
			j++;
		}
		X0[i] = x_0(i);
		X1[i] = x_1(i);
		Y0[i] = y_0(i);
		Y1[i] = y_1(i);
		i++;
	}
}

// проверка выполнения условия
// возращаемое значение - номер строки в которой все элементы удовлетворяют условию |x-x_old| <= eps
// в противном случае возвращается значение -1
bool checkEps()
{
	int i = 0, j = 0;
	while(i < n)
	{
		j = 0;
		while(j < n)
		{
			if (fabs(X[i][j] - X_old[i][j]) > eps)
				return false;
			j++;
		}
		i++;
	}
	return true;
}

// копирование X в X_old
void copy_X()
{
	int i = 0, j = 0;
	while(i < n)
	{
		j = 0;
		while(j < n)
		{
			X_old[i][j] = X[i][j];
			j++;
		}
		i++;
	}
}


// подсчет суммы
double getSum()
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			sum += X[i][j];
	}
	return sum;
}


int main(int argc, char* argv[])
{
	time_t end;
	double workTime;
	int i = 0, j = 0;
	n = 200;
	eps = 0.0005;
	
	init_x();

	double sum = 0;
	time_t start=clock();
	do{
		// скопировать X
		copy_X();
		int from=0;
		int to=n;
		// подсчет для красных точек
		// red
		for (i = from; i < to; i += 4)
			for (j = 0; j < n; j += 2)
			{	
				__m128d sum = Gauss_Zeid(i, j);
				_mm_storel_pd(&X[i][j], sum);
				_mm_storeh_pd(&X[i+2][j], sum);
			}

		for (i = from+1; i < to; i +=4)
			for (j = 1; j < n; j += 2)
			{	
				__m128d sum = Gauss_Zeid(i, j);
				_mm_storel_pd(&X[i][j], sum);
				_mm_storeh_pd(&X[i+2][j], sum);
			}

		// подсчет для черных точек
		// black
		for (i = from; i < to; i += 4)
			for (j = 1; j < n; j += 2)
			{	
				__m128d sum = Gauss_Zeid(i, j);
				_mm_storel_pd(&X[i][j], sum);
				_mm_storeh_pd(&X[i+2][j], sum);
			}

		for (i = from+1; i < to; i += 4)
			for (j = 0; j < n; j += 2)
			{	
				__m128d sum = Gauss_Zeid(i, j);
				_mm_storel_pd(&X[i][j], sum);
				_mm_storeh_pd(&X[i+2][j], sum);
			}
	}while(!checkEps());

	sum = getSum();
	printf("Summ = %.5f\n", sum);
	
	end = clock();
	workTime = end-start;
	workTime /= CLOCKS_PER_SEC;
	printf("Calculation takes: %.5f sec\n", workTime);
	return 0;
}

