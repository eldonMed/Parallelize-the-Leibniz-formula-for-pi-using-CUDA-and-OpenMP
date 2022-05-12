#include <omp.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>


int main()
{
    long int i, n = 10000000;
    double sum = 0.0, term, pi;
    clock_t start, end;
    double cpu_time_used;


    omp_set_num_threads(4);
    printf("Enter number of iterations: %ld",n);
    start = clock();
#pragma omp parallel
    {
#pragma omp for private(i,term) reduction(+:sum)
        for (i = 0; i < n; i++)
        {
            term = pow(-1, i) / (2 * i + 1);
            sum += term;
        }
    }
    end = clock();
    pi = 4 * sum;

    printf("\nPI = %.10lf", pi);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nOPENMP took %f seconds to execute \n", cpu_time_used);
    return 0;
}