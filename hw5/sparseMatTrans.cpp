#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<time.h>	// for random
#include<sys/time.h>


using namespace std;

void getMat(string fname, vector<double> &V, vector<int> &row_index, vector<int> &col_index, int size){
	// read from txt file
	ifstream file;
	file.open(fname);
	
	double val;
	row_index.push_back(0);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			file >> val;
			if(val > 0){
				V.push_back(val);
				col_index.push_back(j);
				row_index.push_back(i);
			}	
		}
	
	}

	file.close();
}


void transpose(vector<double> &V, vector<double> &VT,
		vector<int> &row_index, vector<int> &col_index,
		vector<int> &row_indexT, vector<int> &col_indexT){

	// transpose of CSR matrix is CSC matrix
	for(size_t i = 0; i < V.size(); i++){
		VT.push_back(V[i]);
		row_indexT.push_back(col_index[i]);
	}

	for(size_t i = 0; i < row_index.size(); i++){
		col_indexT.push_back(row_index[i]);
	}
	
}

void printMat(vector<double> &V, vector<int> &row_index, vector<int> &col_index){
	cout << "V: " << endl;
	for(size_t i = 0; i < V.size(); i++){
		cout << V[i] << " ";
	}
	cout << endl;

	cout << "row_index: " << endl;
	for(size_t i = 0; i < row_index.size(); i++){
		cout << row_index[i] << " ";
	}
	cout << endl;

	cout << "col_index: " << endl;
       for(size_t i = 0; i < col_index.size(); i++){
	      cout << col_index[i] << " "; 
       }
       cout << endl;
}

int main(){

	srand(time(NULL));

	struct timeval start, end;

	vector<double> V, VT;
	vector<int> row_index, col_index, row_indexT, col_indexT;

	int size = 4096;

	string fname = "myMatrix.txt";

	getMat(fname, V, row_index, col_index, size);
	//cout << "original: " << endl;
	//printMat(V, row_index, col_index);


	gettimeofday(&start, NULL);
	transpose(V, VT, row_index, col_index, row_indexT, col_indexT);
	gettimeofday(&end, NULL);
	

	double runtime;
	runtime = (end.tv_sec - start.tv_sec) * 1e6;
	runtime = (runtime + (end.tv_usec - start.tv_usec)) * 1e-6;	// runtime in seconds

	double bandwidth = size * size * sizeof(double) / runtime * 1e-6;

	printf("matrix size: %d \n", size);
	printf("transpose time: %f sec\n", runtime);
	printf("bandwith: %f GB/s \n", bandwidth);

	//cout << "transposed: " << endl;
	//printMat(VT, row_indexT, col_indexT);

	return 0;
}
