#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000;
double step;

#define NUM_THREADS 75
int main (){
    int i, nthreads;
    double pi, sum[NUM_THREADS];
    step = 1.0/(double)num_steps;

    // Start timing
    double start_time = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i, id, tthreads; double x;
        tthreads = omp_get_num_threads();
        id = omp_get_thread_num();
        if (id==0) nthreads=tthreads;
        for (i=id, sum[id]=0.0;i< num_steps; i=i+tthreads){
            x = (i+0.5)*step;
            sum[id] = sum[id] + 4.0/(1.0+x*x);
        }
    }

    // Combine thread-local sums
    for (i=0, pi=0.0;i<nthreads;i++)
        pi += step * sum[i];

    // End timing
    double end_time = omp_get_wtime();

    printf("Parallel pi = %.15f\n", pi);
    printf("Time taken (seconds) = %f\n", end_time - start_time);

    return 0;
}