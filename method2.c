#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000;

int main (){
    int i, tthreads, id;
    double step, pi = 0.0, sum = 0.0, x;
    step = 1.0/(double)num_steps;

    // Start timing
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        tthreads = omp_get_num_threads();
        id = omp_get_thread_num();
        for (i=id; i<num_steps; i+=tthreads){
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
    }
    pi = step * sum;

    // End timing
    double end_time = omp_get_wtime();

    printf("Parallel pi (with race condition) = %.15f\n", pi);
    printf("Time taken (seconds) = %f\n", end_time - start_time);

    return 0;
}