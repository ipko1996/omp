#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void matrixMatrixMulti(int N, int t)
{
	//INIT
	//Lefoglalas
	int** A = (int**)malloc(N * sizeof(int*));
	int** B = (int**)malloc(N * sizeof(int*));
	int** C = (int**)malloc(N * sizeof(int*));
	int i, j, k = 0;
	for (i = 0; i < N; i++)
		A[i] = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
		B[i] = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
		C[i] = (int*)malloc(N * sizeof(int));
	//A[i][j] --> *(*(arr+i)+j)

	//Ertekadas
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			A[i][j] = 2; //vagy *(*(arr+i)+j) = ++count
			B[i][j] = 3;
			C[i][j] = 0;
		}

	{
		//A gepedben levo magok szama
		//int id = omp_get_num_procs();
		//printf("%d", id);
	}

	//Szalak beallitasa
	omp_set_num_threads(t);

	double start = omp_get_wtime();

#pragma omp parallel for private(i,j,k) shared(A,B,C)
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			for (k = 0; k < N; ++k) {
				C[i][j] += sin(A[i][k] * B[k][j]);
			}
		}
	}

	double end = omp_get_wtime();

	printf("Matrix-matrix with omp: %.6f\n", (end - start));

	{
		//Eredmenytomb kiirisa
		//for (int i = 0; i < N; i++) {
		//	printf("\n");
		//	for (int j = 0; j < N; j++)
		//		printf("%d ", C[i][j]);
		//}

		//Memoria felszabaditas
	}

	for (i = 0; i < N; i++)
		free(A[i]);
	free(A);
	for (i = 0; i < N; i++)
		free(B[i]);
	free(B);
	for (i = 0; i < N; i++)
		free(C[i]);
	free(C);

	printf("\n");
}

void matrixMatrixMultiBlock(int N, int t)
{
	int** A = (int**)malloc(N * sizeof(int*));
	int** B = (int**)malloc(N * sizeof(int*));
	int** C = (int**)malloc(N * sizeof(int*));
	int i, j, k = 0;
	for (i = 0; i < N; i++)
		A[i] = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
		B[i] = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
		C[i] = (int*)malloc(N * sizeof(int));

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			A[i][j] = 2;
			B[i][j] = 3;
			C[i][j] = 0;
		}

	omp_set_num_threads(t);

	double start = omp_get_wtime();

#pragma omp parallel for collapse(2) private(i,j,k) shared(A,B,C)
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			for (k = 0; k < N; ++k) {
				C[i][j] += sin(A[i][k] * B[k][j]);
			}
		}
	}

	double end = omp_get_wtime();

	printf("Matrix-matrix with omp collapse: %.6f\n", (end - start));

	for (i = 0; i < N; i++)
		free(A[i]);
	free(A);
	for (i = 0; i < N; i++)
		free(B[i]);
	free(B);
	for (i = 0; i < N; i++)
		free(C[i]);
	free(C);
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		printf("Hibas adatok! Program hivasa --> program_neve N thread\n");
	}
	else {
		//db, thread
		int db = atoi(argv[1]);
		int th = atoi(argv[2]);

		printf("%d %d\n", db, th);
		matrixMatrixMulti(db, th);
		matrixMatrixMultiBlock(db, th);

		printf("DONE\n");
	}
}

//int main()
//{
//	int n;
//	int th;
//	printf("Matrix merete (n): ");
//#pragma warning(suppress : 4996)
//	scanf("%d", &n);
//	printf("Magok szama: ");
//#pragma warning(suppress : 4996)
//	scanf("%d", &th);
//
//	printf("%d %d\n", n, th);
//	matrixMatrixMulti(n, th);
//	matrixMatrixMultiBlock(n, th);
//
//
//	printf("DONE\n");
//}