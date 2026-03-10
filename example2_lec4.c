#include <stdio.h>
#include <omp.h>

int main(){

    //Runtime library function to request the number of threads in the parallel region
    omp_set_num_threads(4);
    #pragma omp parallel

    //Start of the parallel region
    {

        int ID = omp_get_thread_num();
        printf("Hello World!(Thread %d)\n", ID);
    } //End of the parallel region
}