#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hist(int th, int op)
{
	int n = 1000;
	int bins = 256;
	int* x = (int*)malloc(n * n * sizeof(int));  // NxN image?
	int* hist = (int*)malloc(bins * sizeof(int)); // 256 intensity level
	// init

#pragma omp parallel for
	for (int i = 0; i < n * n; i++) {
		x[i] = (int)(255.0 * rand() / RAND_MAX);
	}
	for (int i = 0; i < bins; i++) {
		hist[i] = 0;
	}	

	omp_set_num_threads(th);

	//atomic
	if (op == 0) 
	{
		double start = omp_get_wtime();

#pragma omp parallel for 
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int v = x[i * n + j];
#pragma omp atomic
				hist[v] ++;
			}
		}
		double stop = omp_get_wtime();
		printf("par hist time (atomic): %.6f\n", (stop - start));
	}

	if (op == 1)
	{
		double start = omp_get_wtime();

#pragma omp parallel for 
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int v = x[i * n + j];
#pragma omp critical
				hist[v] ++;
			}
		}
		double stop = omp_get_wtime();
		printf("par hist time (critical): %.6f\n", (stop - start));
	}
	

	free(x);
	free(hist);
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		printf("Hibas adatok! Program hivasa --> program_neve thread option\n");
		printf("Opciok: 0 - atomic, 1 - critical, 2 - reduce\n");
	}
	else {
		//db, szalon
		int th = atoi(argv[1]);
		int op = atoi(argv[2]);

		printf("%d %d\n", th, op);

		//0 - atomic
		//1 - critical
		//2 - reduce
		hist(th, op);

		printf("DONE\n");
	}

}