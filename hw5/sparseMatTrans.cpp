#include<cstdio>
#include<vector>
#include<cstdlib>
#include<time>	// for random
#include<sys/time.h>

using namespace std;

void getMat(vector<double> &V, vector<int> &row_index, vector<int> &col_index,
		int size, int numElem){

	double num;
	int currentElem = 0;
	row_index.push_back(currentRow);
	for(int i = 0; i < numElem; i++){
		V.push_back(num);

		col_index.push_back(rand() % size);
		
		// row_index counts number of elements in each row
		if(i < numElem - 1){
			currentRow += ;
			row_index.push_back(currentRow);
		}
	}

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

	int size = 5;
	int numElem = 10;
	vector<double> V, VT;
	vector<int> row_index, col_index, row_indexT, col_indexT;

	



	return 0;
}
