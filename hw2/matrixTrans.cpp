#include<iostream>
#include<iomanip>
#include<sys/time.h>
#include<cmath>
#include<time.h>

using namespace std;

unsigned char* genMatrix(int dim, int rank);

double* transpose2(double mat[], int dim);
unsigned char* transpose(unsigned char mat[], int dim, int rank);


void printMat(double mat[], int dim, int rank);
void printStraight(unsigned char mat[], int dim, int rank);


int main(){
	cout << "run" << endl;

	// set up timing
	struct timeval start, end;

	int dim = 2, rank = 23; // rank >= 2	
	// initialize matrix
	unsigned char* mat = genMatrix(dim, rank);

	gettimeofday(&start, NULL);

	unsigned char* matTrans2 = transpose(mat, dim, rank);
	
	gettimeofday(&end, NULL);

	// runtime
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
	cout << std::setprecision(6) << "runtime: " << time_taken << " sec" << endl;


	// print matrix
	/*
	cout << "matrix:" << endl;
	//printMat(mat, dim, rank);
	printStraight(mat, dim, rank);

	cout << "transpose:" << endl;
	//printMat(matTrans2, dim, rank);	
	printStraight(matTrans2, dim, rank);
	*/



	return 0;
}

unsigned char* genMatrix(int dim, int rank){
	// generate vectorized tensor
	const int matSize = pow(dim, rank); // square tensor
	unsigned char* matrix = new unsigned char[matSize];
	srand (time(NULL));
	for(int id = 0; id < matSize; id++){
		matrix[id] = rand() % 10; 
		//matrix[id] = id + 1;
	}

	return matrix;
}


unsigned char* transpose(unsigned char mat[], int dim, int rank){
	// all tensor are stored as 1D vector, square tensor
	const int matSize = pow(dim,rank);
	unsigned char* out = new unsigned char[matSize];	

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

