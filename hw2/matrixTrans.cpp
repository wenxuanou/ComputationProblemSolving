#include<iostream>
#include<stdio.h>
#include<cmath>
#include<time.h>

using namespace std;

double* genMatrix(int dim, int rank);

double* transpose2(double mat[], int dim);
double* transpose(double mat[], int dim, int rank);


void print2D(double mat[], int dim);
void printMat(double mat[], int dim, int rank);
void printStraight(double mat[], int dim, int rank);

int main(){
	cout << "run" << endl;

	int dim = 2, rank = 3; // rank >= 2
	
	// initialize matrix
	double* mat = genMatrix(dim, rank);

	//double* matTrans = transpose2(mat,dim);
	double* matTrans2 = transpose(mat, dim, rank);

	
	cout << "matrix:" << endl;
	//printMat(mat, dim, rank);
	printStraight(mat, dim, rank);
	

	/*	
	cout << "transpose:" << endl;
        print2D(matTrans, dim);	
	*/

	cout << "new transpose:" << endl;
	//printMat(matTrans2, dim, rank);	
	printStraight(matTrans2, dim, rank);




	return 0;
}

double* genMatrix(int dim, int rank){
	// generate vectorized tensor
	const int matSize = pow(dim, rank); // square tensor
	double* matrix = new double[matSize];
	srand (time(NULL));
	for(int id = 0; id < matSize; id++){
		//matrix[id] = rand() % 10; 
		matrix[id] = id + 1;
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
		int newId = 0;
		int temp = id;
		for(int countR = 1; countR <= rank; countR++){
			newId += temp / (int)pow(dim, rank - countR) * pow(dim, countR - 1); 
			
			//cout << temp / (int)pow(dim, rank - countR) << " ";
			
			temp = temp % (int)pow(dim, rank - countR);
		}
		//cout << endl;

		out[newId] = mat[id];

		//cout << "id: " << id << " newId: "<< newId << endl;

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
	
	int matSize = pow(dim,rank);

	for(int id = 0; id < matSize; id++){
		for(int count = 1; count < rank; count++){
			if(id % (int)pow(dim,count) == 0){
				cout << endl;
			}else{
				continue;
			}
		}
		cout << mat[id] << " ";
	}
	

	return;
}

void printStraight(double mat[], int dim, int rank){

	int matSize = pow(dim,rank);

	for(int id = 0; id < matSize; id++){
		cout << mat[id] << " ";
	}
	cout << endl;

	return;
}

