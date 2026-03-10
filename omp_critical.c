#include <stdio.h>
#include <omp.h>

float big_job(int i) {
    // Example computation
    return i * 2.0;
}

float calc(float B) {
    // Example computation
    return B / 2.0;
}

int main() {
    float result = 0.0;
    int nthrds;

    #pragma omp parallel
    {
        float B;
        int i, id;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        for (i = id; i < nthrds; i += nthrds) {
            B = big_job(i);
        }

        #pragma omp critical
        result += calc(B);
    }

    printf("Final result = %f\n", result);
    return 0;
}