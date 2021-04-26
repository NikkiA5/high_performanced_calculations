#include <iostream>
#include <omp.h>

double Square(){
	double a = 0;
	double b = 1;
	int steps = 10000;
	double step = (b-a)/(steps + 1);
	double sum = 0;
	for (auto i = 0; i < steps; i++){
			sum += step * ((4.0)/(1 + (a + i * step) * (a + i * step)));
		}
	return sum;
}

double Sparallel(){
	double a = 0;
	double b = 1;
	int steps = 10000;
	double step = (b-a)/(steps + 1);
	double sum = 0;

	#pragma omp parallel for reduction(+:sum) num_threads(10)

		for (auto i = 0; i < steps; i++){
			sum += step * ((4.0)/(1 + (a + i * step) * (a + i * step)));
		}

	return sum;
}

int  main() {
	double begin = omp_get_wtime();
	double res = Square();
	double Linend = omp_get_wtime();
	double Parres = Sparallel();
	double Parallend = omp_get_wtime();
	
	std::cout << "linear: " << res << "\t";
	std::cout << "parallel: " << Parres << "\n";
	std::cout << "\n";
	std::cout << "linear   time: " << (Linend- begin) << "\n";
	std::cout << "parallel time: " << (Parallend - Linend << "\n";
	
	return 0;
}
