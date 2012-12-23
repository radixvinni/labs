#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <emmintrin.h>

#define pi 3.14159265
#define e exp(1.0)

// первая точка матрицы - чёрная
// матрица узлов решетки
double XB[3000][3000];
double XR[3000][3000];
// старые значения узлов для посчета eps
double X_oldB[3000][3000];
double X_oldR[3000][3000];
// граничные условия
double X0_B[3000], Y0[6000], X1_B[3000], Y1[6000];
double X0_R[3000], X1_R[3000];


double eps;

int n;	/* Размерность матрицы n*n*/

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
// первая точка матрицы - чёрная
// первая точка X0 - красная
// первая точка X1 - чёрная
//(первая=нулевая)

// чётный ряд начинается с черного узла

// Вычисление двух точек по методу Гаусса-Зейделя
// в красных чётных узлах i,j и i,j+2
__m128d Gauss_Zeid_Red_odd(int i, int j)
{
	__m128d sum;
	if (i != 0)
		sum = _mm_loadu_pd(&XB[i-1][j]);
	else
		sum = _mm_loadu_pd(&X0_B[j]);

	// первый(нулевой) ряд чётный, последний нечётный
	sum = _mm_add_pd(sum , _mm_loadu_pd(&XB[i+1][j]));

	//чётный ряд начинается с черного узла
	// Y0 не используем
	sum = _mm_add_pd(sum , _mm_loadu_pd (&XB[i][j]));
	
	if (j+2 != n/2)
		sum = _mm_add_pd(sum , _mm_loadu_pd(&XB[i][j+1]));
	else
		sum = _mm_add_pd(sum , _mm_setr_pd(XB[i][j+1],Y1[i]));

	return _mm_div_pd(sum , _mm_setr_pd(4.0, 4.0));
}
// в красных нечётных узлах i,j и i,j+2
__m128d Gauss_Zeid_Red_even(int i, int j)
{
	__m128d sum;
	// первый(нулевой) ряд чётный, последний нечётный
	sum = _mm_loadu_pd(&XB[i-1][j]);

	if (i+1 != n)
		sum = _mm_add_pd(sum , _mm_loadu_pd(&XB[i+1][j]));
	else
		sum = _mm_add_pd(sum , _mm_loadu_pd(&X1_B[j]));


	//чётный ряд начинается с черного узла, нечетный с красного
	if (j != 0)
		sum = _mm_add_pd(sum , _mm_loadu_pd (&XB[i][j]));
	else
		sum = _mm_add_pd(sum , _mm_setr_pd(Y0[i],XB[i][j]));

	sum = _mm_add_pd(sum , _mm_loadu_pd(&XB[i][j]));//да, да, именно i,j

	return _mm_div_pd(sum , _mm_setr_pd(4.0, 4.0));
}
// в черных чётных узлах
__m128d Gauss_Zeid_Black_odd(int i, int j)
{
	__m128d sum;
	// первый(нулевой) ряд чётный, последний нечётный
	if (i != 0)
		sum = _mm_loadu_pd(&XR[i-1][j]);
	else
		sum = _mm_loadu_pd(&X0_R[j]);

	sum = _mm_add_pd(sum , _mm_loadu_pd(&XR[i+1][j]));

	//чётный ряд начинается с черного узла, нечетный с красного
	if (j != 0)
		sum = _mm_add_pd(sum , _mm_loadu_pd (&XR[i][j]));
	else
		sum = _mm_add_pd(sum , _mm_setr_pd(Y0[i],XR[i][j]));

	sum = _mm_add_pd(sum , _mm_loadu_pd(&XR[i][j]));//да, да, именно i,j
	
	return _mm_div_pd(sum , _mm_setr_pd(4.0, 4.0));
}
// в черных нечётных узлах
__m128d Gauss_Zeid_Black_even(int i, int j)
{
	__m128d sum;
	// первый(нулевой) ряд чётный, последний нечётный
	sum = _mm_loadu_pd(&XR[i-1][j]);

	if (i+1 != n)
		sum = _mm_add_pd(sum , _mm_loadu_pd(&XR[i+1][j]));
	else
		sum = _mm_add_pd(sum , _mm_loadu_pd(&X1_R[j]));

	//чётный ряд начинается с черного узла, нечетный с красного
	sum = _mm_add_pd(sum , _mm_loadu_pd (&XR[i][j]));

	if (j+2 != n/2)
		sum = _mm_add_pd(sum , _mm_loadu_pd(&XR[i][j+1]));
	else
		sum = _mm_add_pd(sum , _mm_setr_pd(XR[i][j+1],Y1[i]));

	return _mm_div_pd(sum , _mm_setr_pd(4.0, 4.0));
}

// инициализации начальных значений X и Х_old
// первая точка матрицы - чёрная
// первая точка X0 - красная
// Y0,Y1 - все точки в одном массиве
void init_x()
{
	int i = 0, j = 0;
	while(i < n)
	{
		j = 0;
		while(j < n/2)
		{
			XB[i][j] = 0;
			X_oldR[i][j] = 0;
			XB[i][j] = 0;
			X_oldR[i][j] = 0;
			j++;
		}
		if (i%2)
		{
			X0_B[i/2] = x_0(i);
			X1_B[i/2] = x_1(i);
		}
		else
		{
			X0_R[i/2] = x_0(i);
			X1_R[i/2] = x_1(i);
		}
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
		while(j < n/2)
		{
			if (fabs(XB[i][j] - X_oldB[i][j]) > eps)
				return false;
			if (fabs(XR[i][j] - X_oldR[i][j]) > eps)
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
		while(j < n/2)
		{
			X_oldB[i][j] = XB[i][j];
			X_oldR[i][j] = XR[i][j];
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
		for (int j = 0; j < n/2; ++j)
		{
			sum += XB[i][j];
			sum += XR[i][j];
		}
	}
	return sum;
}

int main(int argc, char* argv[])
{
	time_t end;
	double workTime;
	int i = 0, j = 0;
	n = 1000;
	eps = 0.005;
	init_x();
	double sum = 0;
	time_t start=clock();
	int iter=0;
	do{
		// скопировать X
		copy_X();
		// подсчет для четных черных точек
		for (i = 0; i < n; i += 2)
			for (j = 0; j < n/2; j += 2)
				_mm_storeu_pd(&XB[i][j], Gauss_Zeid_Black_odd(i, j));
		//для нечетных чёрных
		for (i = 1; i < n; i += 2)
			for (j = 0; j < n/2; j += 2)
				_mm_storeu_pd(&XB[i][j], Gauss_Zeid_Black_even(i, j));

		// подсчет для четных красных точек
		for (i = 0; i < n; i += 2)
			for (j = 1; j < n/2; j += 2)
				_mm_storeu_pd(&XR[i][j], Gauss_Zeid_Red_odd(i, j));
		for (i = 1; i < n; i += 2)
			for (j = 1; j < n/2; j += 2)
				_mm_storeu_pd(&XR[i][j], Gauss_Zeid_Red_even(i, j));
		iter++;
	}while(!checkEps());

	sum = getSum();
	printf("Summ = %.5f\n", sum);
	end = clock();
	workTime = end-start;
	workTime /= CLOCKS_PER_SEC;
	printf("Iter: %i, Calculation takes: %.5f sec\n", iter, workTime);
	return 0;
}

