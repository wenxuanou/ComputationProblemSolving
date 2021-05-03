#include<cstdio>
#include<cstdlib>
#include<sys/time.h>

using namespace std;

void getMat(double *mat, size_t size){
	double val = 0;
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size; j++, val++){
			mat[i * size + j] = val;
		}
	}

}	

void transpose(double *mat, double *matTrans, size_t size, size_t blockWidth){
	
	for(size_t i = 0; i < size / blockWidth; i++){
		for(size_t j = 0; j < size / blockWidth; j++){
			for(size_t ii = 0; ii < blockWidth; ii++){
				for(size_t jj = 0; jj < blockWidth; jj++){
                        		
					matTrans[(j * blockWidth + jj) * size + (i * blockWidth + ii)] = 
						mat[(i * blockWidth + ii) * size + (j * blockWidth + jj)];
                		
				}
        		}
		}
	}
	

}

void printMat(double *mat, size_t size){
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size; j++){
			printf("%f ", mat[i * size + j]);
		}
		printf("\n");
	}
	printf("\n");

}

int main(){
		
	const size_t size = 4096;	// 2^20 total element
	size_t blockWidth = size / 8;

	double* mat = (double*)malloc(size * size * sizeof(double));
	double* matTrans = (double*)malloc(size * size * sizeof(double));



	// timing
	struct timeval start, end;

	getMat(mat, size);
	
	gettimeofday(&start, NULL);	
	transpose(mat, matTrans, size, blockWidth);
	gettimeofday(&end, NULL);		

	double runtime;
	runtime = (end.tv_sec - start.tv_sec) * 1e6;
	runtime = (runtime + (end.tv_usec - start.tv_usec)) * 1e-6;	// runtime in seconds

	double bandwidth = size * size * sizeof(double) / runtime * 1e-6;	// in GB/s

	// print matrix
	/*
	printf("mat: \n");
	printMat(mat, size);
	printf("matTrans: \n");	
	printMat(matTrans, size);
	*/

	printf("matrix size: %zu \n", size);
	printf("blockWidth: %zu \n", blockWidth);
	printf("transpose time: %f sec\n", runtime);	
	printf("bandwith: %f GB/s \n", bandwidth);


	free(mat);
	free(matTrans);

	return 0;
}
