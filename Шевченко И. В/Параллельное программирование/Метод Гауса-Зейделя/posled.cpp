#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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


// Вычисление точек по методу Гаусса-Зейделя
// в узле i, j
double Gauss_Zeid(int i, int j)
{
	double sum = 0;
	if (i != 0)
		sum += X[i-1][j];
	else
		sum += X0[j];

	if (i != n-1)
		sum += X[i+1][j];
	else
		sum += X1[j];


	if (j != 0)
		sum += X[i][j-1];
	else
		sum += Y0[i];

	if (j != n-1)
		sum += X[i][j+1];
	else
		sum += Y1[i];

	sum /= 4;
	return sum;
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
		for (i = from; i < to; i += 2)
			for (j = 0; j < n; j += 2)
				X[i][j] = Gauss_Zeid(i, j);

		for (i = from+1; i < to; i +=2)
			for (j = 1; j < n; j += 2)
				X[i][j] = Gauss_Zeid(i, j);

		// подсчет для черных точек
		// black
		for (i = from; i < to; i += 2)
			for (j = 1; j < n; j += 2)
				X[i][j] = Gauss_Zeid(i, j);

		for (i = from+1; i < to; i += 2)
			for (j = 0; j < n; j += 2)
				X[i][j] = Gauss_Zeid(i, j);
	}while(!checkEps());

	sum = getSum();
	printf("Summ = %.5f\n", sum);
	
	end = clock();
	workTime = end-start;
	workTime /= CLOCKS_PER_SEC;
	printf("Calculation takes: %.5f sec\n", workTime);
	return 0;
}

