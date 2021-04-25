#include<iostream>
#include<iomanip>
#include<vector>
#include<cstdlib>
#include<sys/time.h>
#include<time.h>

#include<omp.h>


using namespace std;

template<int n>
void getMagicMatrix(vector< vector<int> > &mat){
	// grab code from https://www.geeksforgeeks.org/magic-square/
	// Siamese method
	
	// initialize position for 1
	int i = n / 2;
    	int j = n - 1;
	// fill in all values one by one
	for (int num = 1; num <= n * n; ) {
		if(i == -1 && j == n){	
		// if row index is -1 and col at n, new position be (0, n-2)
			j = n - 2;
            		i = 0;
		}else{
			// if col out of right side, wrap to left bound at zero
			if(j == n){ j = 0; }
			// if row out of up side, wrap to botton
			if(i < 0){ i = n - 1; }
		}

		if(mat[i][j] != 0){
			// if number already inserted at position, go to down left location
			j -= 2;	
			i++;
			continue;
		}else{
			// if no number at position, insert a number
			mat[i][j] = num++;
		}
		
		// step up right to insert next number	
		j++;
		i--;		
	}

	return;
}

/*
bool checkIfMagic(int* mat, size_t n, const float sumVal){
	bool isMagic = true;
	// check diagonal
	float sum1 = 0, sum2 = 0;
	for(size_t countN = 0; countN < n; countN++){
		sum1 += mat[countN][countN];
		sum2 += mat[(n - 1) - countN][(n - 1) - countN];
	}
	isMagic = (sum1 == sumVal) && (sum2 == sumVal);

	// check col and row
	//#pragma omp parallel for
	for(size_t countN = 0; countN < n; countN++){
		sum1 = 0; sum2 = 0;
		for(size_t countNN = 0; countNN < n; countNN++){
			sum1 += mat[countN][countNN];
			sum2 += mat[countNN][countN];	
		}
		isMagic &= (sum1 == sumVal) && (sum2 == sumVal);
	}

	return isMagic;	
}
*/

int main(){
	const int n = 9; // matrix size, assume only odd dimension 

	// set up timing
	struct timeval start, end;

	//int mat[n][n] = {};		
	vector< vector<int> > mat(
		n,
		vector<int>(n,0));

	gettimeofday(&start, NULL);
			
	// recursive, fit each value at index one by one
	getMagicMatrix<n>(mat);
	
	gettimeofday(&end, NULL);

	// runtime
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
		
	cout << "n: " << n << " ";
	cout << std::setprecision(6) << "runtime: " << time_taken << " sec" << endl;
	cout << endl;	
		
	/*	
	cout << "generated matrix: " << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;	
	*/		

	return 0;
}

