#include<iostream>
#include<cmath>

using namespace std;

double* transpose2(double mat[], int dim);
void print2D(double mat[], int dim);


int main(){
	cout << "run" << endl;

	int dim = 4;
	double mat[dim * dim]; //rank 2
	
	// initialize matrix
	double val = 0;
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			mat[i*dim + j] = val;
			val++;
		}
	}

	double* matTrans = transpose2(mat,dim);

	cout << "matrix:" << endl;
	print2D(mat, dim);
	cout << endl;
	cout << "transpose:" << endl;
        print2D(matTrans, dim);	

	return 0;
}

double* transpose2(double mat[], int dim){
	// for rank 2 only
	double* out = new double[dim * dim];
	
	for(int j = 0; j < dim; j++){
		for(int i = 0; i < dim; i++){
			out[j*dim + i] = mat[i*dim + j];
		}
	}

	return out;
}

void print2D(double mat[], int dim){
	// print rank 2 tensor
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			cout << mat[i*dim + j] << " ";
		}
		cout << endl;
	}
	return;
}

