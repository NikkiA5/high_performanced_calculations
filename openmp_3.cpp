#include <omp.h>
#include <iostream>

void bubbleSort(double *A, int n) {
    double time;
    time = omp_get_wtime()*1000;
    for(int i = 0; i < n; i++) {
        double t = 0;
        if(i % 2 == 0) {
            for(int j = 0; j < n; j += 2) {
                if(j < n-1) {
                    if(A[j] > A[j+1])
					{
						int t = A[j];
						A[j] = A[j+1];
						A[j+1] = t;
					}
                }
            }
        } else {
            for (int j = 1; j < n; j += 2) {
                if (j < n-1) {
                    if(A[j] > A[j+1])
					{
						int t = A[j];
						A[j] = A[j+1];
						A[j+1] = t;
					}
                }	
            }	
        }
    }
    std::cout << "Bubble_time: " << 1000*omp_get_wtime() - time << "\n";
}

void parallelBubbleSort(double *A, int n) {
    double time;
    time = 1000 * omp_get_wtime();
    for(int i = 0; i < n; i++) {
        double t = 0;
        if(i % 2 == 0) {
            #pragma omp parallel for private(t)

            for(int j = 0; j < n; j += 2){
                if(j < n - 1){
                    if(A[j] > A[j+1]){
						int t = A[j];
						A[j] = A[j+1];
						A[j+1] = t;
					}
                }
            }

        }else{
            #pragma omp parallel for private(t)

            for (int j = 1; j < n; j += 2){
                if (j < n - 1){
                    if(A[j] > A[j+1]){
						int t = A[j];
						A[j] = A[j+1];
						A[j+1] = t;
					}
                }	
            }	

        }
    }
    std::cout << "Paralleled Buble_time: " << 1000*omp_get_wtime() - time << "\n";
}

int main() {

    for(int i = 0; i < 11; i++){
        double array[1000];
        for(int i = 0; i < 100; i++){
            array[i] = rand()%1000;
        }
        std::cout << i << "length: 1000" << "\n";
        bubbleSort(array, 100);
        parallelBubbleSort(array, 100);
        std::cout << "\n";
    }

    for(int i = 0; i < 6; i++) {
        int n = rand() % 2000 + 100;
        double array[n];
        for(int i = 0; i < n; i++) {
            array[i] = rand()%1000;
        }
        std::cout << i << "length: 1000" << n << "\n";
        bubbleSort(array, n);
        parallelBubbleSort(array, n);
        std::cout << "\n";
    }

    return 0;
}