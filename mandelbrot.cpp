#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void mandelbrotSet(int N, int t, int op)
{
	int iter_limit = 10000;
	double c_re = 0.2;
	double c_im = 0.4;

	//SIMA
	if (op == 0)
	{
		int i, j = 0;
		int k = 1;
		omp_set_num_threads(t);
		double start = omp_get_wtime();

#pragma omp parallel for //schedule(dynamic) private(i,j,k)
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				int color = 0;
				// bound test
				double z_re = (double)i / N;
				double z_im = (double)j / N;
				double sum_re = z_re * z_re - z_im * z_im + c_re;
				double sum_im = 2 * z_re * z_im + c_im;
				for (k = 1; k < iter_limit; k++) {
					double temp = sum_re;
					sum_re += sum_re * sum_re - sum_im * sum_im + c_re;
					sum_im += 2 * temp * sum_im + c_im;
					if ((sum_re * sum_re + sum_im * sum_im) > 4) {
						break;
					}
					color = k;
				}
			}
		}
		double end = omp_get_wtime();

		printf("Mandelbrot omp sima: %.6f\n", (end - start));
	}

	//dynamic
	if (op == 1)
	{
		int i, j = 0;
		int k = 1;

		omp_set_num_threads(t);
		double start = omp_get_wtime();

#pragma omp parallel for schedule(dynamic) private(i,j,k)
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				int color = 0;
				// bound test
				double z_re = (double)i / N;
				double z_im = (double)j / N;
				double sum_re = z_re * z_re - z_im * z_im + c_re;
				double sum_im = 2 * z_re * z_im + c_im;
				for (k = 1; k < iter_limit; k++) {
					double temp = sum_re;
					sum_re += sum_re * sum_re - sum_im * sum_im + c_re;
					sum_im += 2 * temp * sum_im + c_im;
					if ((sum_re * sum_re + sum_im * sum_im) > 4) {
						break;
					}
					color = k;
				}
			}
		}
		double end = omp_get_wtime();

		printf("Mandelbrot omp dynamic: %.6f\n", (end - start));
	}

	//guided
	if (op == 2)
	{
		int i, j = 0;
		int k = 1;

		omp_set_num_threads(t);
		double start = omp_get_wtime();

#pragma omp parallel for schedule(guided) private(i,j,k)
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				int color = 0;
				// bound test
				double z_re = (double)i / N;
				double z_im = (double)j / N;
				double sum_re = z_re * z_re - z_im * z_im + c_re;
				double sum_im = 2 * z_re * z_im + c_im;
				for (k = 1; k < iter_limit; k++) {
					double temp = sum_re;
					sum_re += sum_re * sum_re - sum_im * sum_im + c_re;
					sum_im += 2 * temp * sum_im + c_im;
					if ((sum_re * sum_re + sum_im * sum_im) > 4) {
						break;
					}
					color = k;
				}
			}
		}
		double end = omp_get_wtime();

		printf("Mandelbrot omp guided: %.6f\n", (end - start));
	}

}

int main(int argc, char* argv[])
{
	if (argc != 4) {
		printf("Hibas adatok! Program hivasa --> program_neve db thread option\n");
		printf("Opciok: 0 - sima, 1 - dynamic, 2 - guided\n");
	}
	else {
		//db, szalon
		int db = atoi(argv[1]);
		int th = atoi(argv[2]);
		int op = atoi(argv[3]);

		printf("%d %d %d\n", db, th, op);

		//0 - sima
		//1 - dynamic
		//2 - guided
		mandelbrotSet(db, th, op);

		printf("DONE\n");
	}

}