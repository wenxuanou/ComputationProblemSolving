#include<cstdio>
#include<CL/sycl.hpp>
#include"oneapi/mkl.hpp"
#include<sys/time.h>

template<size_t size>
void getMat(double mat[][size]){
	double val = 0;
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size; j++, val++){
			mat[i][j] = val;
		}
	}

}

template<size_t size>
void printMat(const double mat[][size]){
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size; j++){
			printf("%f ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

int main(){
	const size_t size = 100;
	double mat[size][size] = {0}, matTrans[size][size] = {0};

	// timing
	struct timeval start, end;

	getMat<size>(mat);

	gettimeofday(&start, NULL);
	mkl_dimatcopy('R', 'T', size, size, 1.0,  mat, size, size);
	gettimeofday(&end, NULL);

	double runtime;
	runtime = (end.tv_sec - start.tv_sec) * 1e6;
	runtime = (runtime + (end.tv_usec - start.tv_usec)) * 1e-6;

	double bandwidth = size * size * sizeof(double) / runtime * 1e-6;	// in GB/s


	printf("matrix size: %zu \n", size);
	printf("transpose time: %f sec\n", runtime);
	printf("bandwith: %f GB/s \n", bandwidth);

	return 0;
}
