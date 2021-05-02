#include<cstdio>
#include<vector>
#include<cstdlib>
#include<time>	// for random
#include<sys/time.h>

using namespace std;

void getMat(vector<double> &V, vector<int> &row_index, vector<int> &col_index){
	// read from npz file


}


void transpose(vector<double> &V, vector<double> &VT
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


int main(){

	srand(time(NULL));

	vector<double> V, VT;
	vector<int> row_index, col_index, row_indexT, col_indexT;

	



	return 0;
}
