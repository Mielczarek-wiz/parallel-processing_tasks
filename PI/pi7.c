#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char *argv[])
{
        clock_t spstart, spstop, ppstart, ppstop;

        double sswtime, sewtime, pswtime, pewtime;
        // volatile

        double x, pi, sum = 0.0;
        int i;
        volatile double partial_sums[50];
        for (i = 0; i < 50; i++)
                partial_sums[i] = 0.0;

        // RÓWNOLEGLE

        sum = 0.0;
        double step = 1. / (double)num_steps;
        
        for (int j = 0; j < 50; j ++)
        {
                printf("%d ", j+1);
                pswtime = omp_get_wtime();
                ppstart = clock();
#pragma omp parallel private(x) num_threads(2)
                {
                        int id = omp_get_thread_num();
                        int access_address = id == 0 ? j : j + 1;
                       
                        partial_sums[access_address] = 0.0;
#pragma omp for
                        for (i = 0; i < num_steps; i++)
                        {
                                x = (i + .5) * step;
                                
                                partial_sums[access_address] += (4.0 / (1. + x * x));
                        }
                        #pragma omp atomic
                        sum += partial_sums[access_address];
                }
                ppstop = clock();
                pewtime = omp_get_wtime();
                printf("%f ", ((double)(ppstop - ppstart) / CLOCKS_PER_SEC));
                printf("%f\n", pewtime - pswtime);
        }

        for (i = 0; i < 2; i++)
        {
                sum += partial_sums[i];
        }
        pi = sum * step;
        
        ppstop = clock();
        pewtime = omp_get_wtime();

        return 0;
}