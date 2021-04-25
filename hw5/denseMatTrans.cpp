#include<cstdio>
#include<vector>
#include<sys/time.h>

using namespace std;

void getMat(vector< vector<double> > &mat, size_t size){
	double val = 0;
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size; j++, val++){
			mat[i][j] = val;
		}
	}

}	

void transpose(const vector< vector<double> > &mat, vector< vector<double> > &matTrans, size_t size){
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size; j++){
			matTrans[j][i] = mat[i][j];
		}
	}

}

void printMat(const vector< vector<double> > &mat, size_t size){
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size; j++){
			printf("%f ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

int main(){
		
	const size_t size = 5000;
	vector< vector<double> > mat(size, vector<double> (size));
	vector< vector<double> > matTrans(size, vector<double> (size));

	// timing
	struct timeval start, end;

	getMat(mat, size);
	
	gettimeofday(&start, NULL);	
	transpose(mat, matTrans, size);
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
