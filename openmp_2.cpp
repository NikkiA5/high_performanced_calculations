#include <iostream>
#include <omp.h>

void reset_vector(double *v, int n){
	for (int i = 0; i < n; i++)	{
		v[i] = 0;
	}
}

void print_vector(double *v, int n){
	for (int i = 0; i < n; i++)	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

int main(){
	
	int rows_num = 10000;
	int cols_num = 10000;
	int rows_in_vect = cols_num;
	
	double tlin = 0;
	double trows = 0;
	double tcols = 0;
	double time_blocks = 0;
	
	double start = 0;
	
	double **A = new double*[rows_num];
	double *b = new double[rows_in_vect];
	double *rows = new double[rows_in_vect];
	double *cols = new double[rows_in_vect];
	double *blocks = new double[rows_in_vect];
	
	
	
	//matrix
	for (int i = 0; i < rows_num; i++){
		A[i] = new double[cols_num];
		for (int j = 0; j < cols_num; j++){
			A[i][j] = rand()%100;
		}
	}
	
	//vect
	for (int i = 0; i < rows_in_vect; i++){
		b[i] = rand()%100;
	}
	//rows&cols
	for (int i = 0; i < rows_in_vect; i++){
		cols[i] = 0;
		rows[i] = 0;
	}
	
	//linear multyplication
	start = omp_get_wtime();
	for(int i = 0; i < rows_num; i++)	{
		for(int j = 0; j < cols_num; j++){ 
			rows[i] += A[i][j]*b[j];
		}
	}
	tlin = omp_get_wtime() - start;
	std::cout << "time: " << tlin << std::endl;
	print_vector(rows, rows_in_vect);
	reset_vector(rows, rows_in_vect);
	
	//parallel miltiplication
	for(int count_threads = 5; count_threads <= 10; count_threads++){
		//rows
		start = omp_get_wtime();
		#pragma omp parallel for shared(A,b,rows) num_threads(count_threads)
		for(int i = 0; i < rows_num; i++){
			for(int j = 0; j < cols_num; j++){
                #pragma omp atomic 
                rows[i] += A[i][j]*b[j];
            }
		}
		trows = omp_get_wtime() - start;
		print_vector(rows, rows_in_vect);
		reset_vector(rows, rows_in_vect);
		
		
		//cols
		start = omp_get_wtime();
		#pragma omp parallel for shared(A,b,cols) num_threads(count_threads)
		for(int i = 0; i < cols_num; i++){
			for(int j = 0; j < rows_num; j++){
                #pragma omp atomic 
                cols[j] += A[j][i]*b[i];
            }
		} 
		tcols = omp_get_wtime() - start;
		print_vector(cols, rows_in_vect);
		reset_vector(cols, rows_in_vect);
		
		//blocks
		start = omp_get_wtime();
		int bh = rows_in_vect / count_threads;
        int bw = cols_num / count_threads;
        #pragma omp parallel for shared(A, b, blocks) num_threads(count_threads)
        for(int block = 0; block < count_threads*count_threads; block++) {
            int i = block / count_threads;
            int j = block % count_threads;

            for(int ih = i*bh; ih < (i+1)*bh; ih++){
                for(int jw = j*bw; jw < (j+1)*bw; jw++){
                    #pragma omp atomic
                    blocks[ih] += A[ih][jw] * b[jw];
                }
            }
        }
		time_blocks = omp_get_wtime() - start;
		print_vector(blocks, rows_in_vect);
		reset_vector(blocks, rows_in_vect);
		
		
		std::cout << "count_threads: " << count_threads << ", time: ";
		std::cout << trows << " "  << " " << time_blocks <<std::endl;
		
	}
	return 0;
}
