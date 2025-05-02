#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000     
#define NUM_BUCKETS 8   

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int* data = malloc(N * sizeof(int));
    int* sorted = malloc(N * sizeof(int));
    int min = 0, max = 10000;

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        data[i] = rand() % (max + 1);
    }
    int bucket_range = (max - min + 1) / NUM_BUCKETS;

    int* buckets[NUM_BUCKETS];
    int bucket_sizes[NUM_BUCKETS] = {0};
    int bucket_capacities[NUM_BUCKETS];

    for (int i = 0; i < NUM_BUCKETS; i++) {
        bucket_capacities[i] = N / NUM_BUCKETS * 2;
        buckets[i] = malloc(bucket_capacities[i] * sizeof(int));
    }

    #pragma omp parallel for shared(buckets, bucket_sizes)
    for (int i = 0; i < N; i++) {
        int value = data[i];
        int bucket_index = (value - min) / bucket_range;
        if (bucket_index >= NUM_BUCKETS) bucket_index = NUM_BUCKETS - 1;

        #pragma omp critical
        {
            int idx = bucket_sizes[bucket_index]++;
            buckets[bucket_index][idx] = value;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < NUM_BUCKETS; i++) {
        qsort(buckets[i], bucket_sizes[i], sizeof(int), compare);
    }

    int index = 0;
    for (int i = 0; i < NUM_BUCKETS; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            sorted[index++] = buckets[i][j];
        }
        free(buckets[i]);
    }

    printf("Sorting complete.\n");

    /*
    for (int i = 1; i < N; i++) {
        if (sorted[i] < sorted[i - 1]) {
            printf("Error at index %d!\n", i);
            break;
        }
    }
    */

    free(data);
    free(sorted);
    return 0;
}

//gcc -fopenmp histogram_sort.c -o histogram_sort
./histogram_sort
