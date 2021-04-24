#include<iostream>
#include<sys/time.h>
#include<time.h>
#include<iomanip>
#include<vector>
#include<algorithm>

#include<omp.h>

using namespace std;

bool checkIfMagic(vector< vector<int> > &mat, size_t n){
        float sumVal = n * (n * n + 1.0f) / 2.0f; 
	bool isMagic = true;
        // check diagonal
        float sum1 = 0, sum2 = 0;
        for(size_t countN = 0; countN < n; countN++){
        	sum1 += mat[countN][countN];
        	sum2 += mat[(n - 1) - countN][(n - 1) - countN];
        }
        isMagic = (sum1 == sumVal) && (sum2 == sumVal);
    
        // check col and row
        #pragma omp parallel for shared(isMagic)                            
	for(size_t countN = 0; countN < n; countN++){    
        	sum1 = 0; sum2 = 0;
		for(size_t countNN = 0; countNN < n; countNN++){
			sum1 += mat[countN][countNN];
			sum2 += mat[countNN][countN];
		}
		
		#pragma omp atomic	
                isMagic &= (sum1 == sumVal) && (sum2 == sumVal);
	}

	return isMagic;
}

void findMagic(vector< vector<int> > &mat, int n, vector<int> &unTested){
	do{	
		// load in
		#pragma omp parallel for collapse(2)
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				mat[i][j] = unTested[i * n + j];
			}
		}
		
	}while(next_permutation(unTested.begin(),unTested.end()) && !checkIfMagic(mat, n));
	return;
}



int main(){
	int n = 2;
	vector< vector<int> > mat(
		n,
		vector<int>(n,0)); 
	float sumVal = n * (n * n + 1.0f) / 2.0f;
	cout << "sumVal: " << sumVal << endl;
		
	// set up timing
	struct timeval start, end;

	// populate
	vector<int> numbers;
	for(int num = 1; num <= n * n; num++){
		numbers.push_back(num);
	}	

	gettimeofday(&start, NULL);
	
	findMagic( mat, n, numbers);		

	gettimeofday(&end, NULL);

	// runtime
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
	cout << std::setprecision(6) << "runtime: " << time_taken << " sec" << endl;

	// print matrix
	cout << "generated matrix: " << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}






