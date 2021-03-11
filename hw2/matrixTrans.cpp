#include<iostream>
#include<iomanip>
#include<sys/time.h>
#include<cstdlib>
#include<cmath>
#include<time.h>

#include<omp.h>

#define NUM_THREADS 4


using namespace std;

void genMatrix(char* mat, unsigned long dim, int rank);

void transpose(char* mat, unsigned long dim, int rank);

void printMat(char* mat, unsigned long dim, int rank);
void printStraight(char* mat, unsigned long dim, int rank);


int main(){
	cout << "run" << endl;
	cout << "core used: " << NUM_THREADS << endl;

	// set up timing
	struct timeval start, end;

	//int rank = 2; 
	const int power = 32;
	const unsigned long matSize = pow(2,power); // 4GB size. 2^32
	char* mat = (char*) malloc(matSize);
	for(int rank = 2; rank <= power; rank *= 4 ){	// *= 4

		cout << "rank: " << rank << " ";

		// compute matrix dimension
		double root = 1.0 / rank;
		unsigned long dim = floor(pow(matSize,root));	

		// initialize matrix
		genMatrix(mat, dim, rank);

		/*
		cout << endl;
		cout << "matrix:" << endl;
                printStraight(mat, dim, rank);
		*/
	
		// timing
		gettimeofday(&start, NULL);

		transpose(mat, dim, rank);
	
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
	*/
	/*
	cout << "transpose:" << endl;
	//printMat(matTrans2, dim, rank);	
	printStraight(mat, dim, rank);
	*/

	}

	free(mat);

	return 0;
}

void genMatrix(char* matrix, unsigned long dim, int rank){
	// generate vectorized tensor
	const unsigned long matSize = pow(dim, rank); // square tensor

	srand (time(NULL));
	for(unsigned long id = 0; id < matSize; id++){
		matrix[id] = rand() % 10 + '0'; 
		//matrix[id] = id + 1;
	}

	return;
}


void transpose(char* mat, unsigned long dim, int rank){
	// all tensor are stored as 1D vector, square tensor
	const unsigned long matSize = pow(dim,rank);
	//unsigned char* out = new unsigned char[matSize];	
	
	#pragma omp parallel for num_threads(NUM_THREADS)	
	for(unsigned long id = 0; id < matSize; id ++){
		unsigned long newId = 0;
		unsigned long temp = id;
		for(int countR = 1; countR <= rank; countR++){
			newId += temp / (unsigned long)pow(dim, rank - countR) * pow(dim, countR - 1); 	
			temp = temp % (unsigned long)pow(dim, rank - countR);
		}
		
		if(newId >= id){
			char tempVal = mat[newId];
			mat[newId] = mat[id];
			mat[id] = tempVal;
		}			
	}
	return;
}


void printMat(char* mat, unsigned long dim, int rank){
	
	unsigned long matSize = pow(dim,rank);

	for(unsigned long id = 0; id < matSize; id++){
		for(int count = 1; count < rank; count++){
			if(id % (unsigned long)pow(dim,count) == 0){
				cout << endl;
			}else{
				continue;
			}
		}
		cout << mat[id] << " ";
	}
	

	return;
}

void printStraight(char* mat, unsigned long dim, int rank){

	unsigned long matSize = pow(dim,rank);
	cout << "print matrix size: " << matSize << endl;
	for(unsigned long id = 0; id < matSize; id++){
		cout << "id: " << id << " " << mat[id] << " ";
	}
	cout << endl;

	return;
}

