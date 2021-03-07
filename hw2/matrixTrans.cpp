#include<iostream>
#include<cmath>
#include<time.h>

using namespace std;

double* genMatrix(int dim, int rank);

double* transpose2(double mat[], int dim);
double* transpose(double mat[], int dim, int rank);


void print2D(double mat[], int dim);
void printMat(double mat[], int dim, int rank);

int main(){
	cout << "run" << endl;

	int dim = 4, rank = 2; // rank >= 2
	
	// initialize matrix
	double* mat = genMatrix(dim, rank);

	double* matTrans = transpose2(mat,dim);
	double* matTrans2 = transpose(mat, dim, rank);

	
	cout << "matrix:" << endl;
	print2D(mat, dim);
	cout << endl;
	
	cout << "transpose:" << endl;
        print2D(matTrans, dim);	
	
	cout << "new transpose:" << endl;
	print2D(matTrans2, dim);	
	
	
	/*
	for(int id = 0; id < pow(dim,rank); id++){
		cout << mat[id] << " " << matTrans2[id] << endl;
	}
	*/

	return 0;
}

double* genMatrix(int dim, int rank){
	// generate vectorized tensor
	const int matSize = pow(dim, rank); // square tensor
	double* matrix = new double[matSize];
	srand (time(NULL));
	for(int id = 0; id < matSize; id++){
		matrix[id] = rand() % 10; 
	}

	return matrix;
}


double* transpose2(double mat[], int dim){
	// for rank 2 only
	const int matSize = dim * dim;
	double* out = new double [matSize];

	for(int id = 0; id < matSize; id++){
		int i = id / dim;
		int j = id % dim;
		out[j * dim + i] = mat[id];
	}	

	return out;
}

double* transpose(double mat[], int dim, int rank){
	// all tensor are stored as 1D vector, square tensor
	const int matSize = pow(dim,rank);
	double* out = new double[matSize];	

	for(int id = 0; id < matSize; id++){
		int rankCount = rank;
		int newId = 0;

		int temp = id % (int)pow(dim, rankCount);
		while(rankCount > 0){
			rankCount--;
			
			newId += temp / pow(dim, rankCount) * pow(dim, rank - rankCount - 1);

			//cout << newId << " ";
			
			temp = temp % (int)pow(dim, rankCount);
		}

		//cout << endl;
		//cout << "id: " << id << " new id: " << newId << endl;

		/*
		double tempVal = mat[id];
		mat[id] = mat[newId];
		mat[newId] = tempVal;
		*/

		out[newId] = mat[id];
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

void printMat(double mat[], int dim, int rank){
	/*
	int matSize = pow(dim,rank);

	for(int id = 0; id < matSize; id++){
		
	}
	*/

	return;
}

