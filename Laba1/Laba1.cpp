#include <iostream>
#include <omp.h>
#include <time.h>

#define N 1500
#define M 700
#define L 1500
using namespace std;

// Умножение матриц
void array_multiplication(double** A, double** B, double** C) {
#pragma omp parallel for shared(A, B, C)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < L; j++) {
			C[i][j] = 0.0;
			for (int k = 0; k < M; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int i, j;

	double** a, ** b, ** c;
	double t1, t2;

	// инициализация матриц
	a = new double* [N];
	for (i = 0; i < N; i++)
		a[i] = new double[N];

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			a[i][j] = i + j;

	b = new double* [L];
	for (i = 0; i < M; i++)
		b[i] = new double[L];

	for (i = 0; i < M; i++)
		for (j = 0; j < L; j++)
			b[i][j] = i + j;

	// умножение матриц и вывод времени
	for (int l = 1; l <= omp_get_num_procs(); l++) {
		c = new double* [N];
		for (i = 0; i < N; i++)
			c[i] = new double[N];
		string threads = "потоков";
		if (l == 1)
			threads = "потока";
		cout << "Начато умножение с использованием " << l << " " << threads << endl;
		omp_set_num_threads(l);
		t1 = omp_get_wtime();
		array_multiplication(a, b, c);
		t2 = omp_get_wtime();
		cout << "Время умножения матриц: " << t2 - t1 << endl;
		cout << "" << endl;
	}
}