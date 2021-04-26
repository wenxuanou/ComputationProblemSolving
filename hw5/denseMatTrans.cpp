#include<cstdio>
#include<vector>
#include<sys/time.h>

using namespace std;

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
void transpose(const double mat[][size], double matTrans[][size]){
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size; j++){
			matTrans[j][i] = mat[i][j];
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
		
	const size_t size = 512;
	double mat[size][size] = {0};
	double matTrans[size][size] = {0};

	// timing
	struct timeval start, end;

	getMat<size>(mat);
	
	gettimeofday(&start, NULL);	
	transpose<size>(mat, matTrans);
	gettimeofday(&end, NULL);		

	double runtime;
	runtime = (end.tv_sec - start.tv_sec) * 1e6;
	runtime = (runtime + (end.tv_usec - start.tv_usec)) * 1e-6;

	double bandwidth = size * size * sizeof(double) / runtime * 1e-6;	// in GB/s

	// print matrix
	/*
	printf("mat: \n");
	printMat(mat, size);
	printf("matTrans: \n");	
	printMat(matTrans, size);
	*/

	printf("matrix size: %zu \n", size);
	printf("transpose time: %f sec\n", runtime);	
	printf("bandwith: %f GB/s \n", bandwidth);


	return 0;
}
