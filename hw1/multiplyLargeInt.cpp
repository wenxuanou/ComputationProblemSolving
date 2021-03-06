#include<iostream>
#include <iomanip>
#include<string>
#include<sys/time.h>
#include<fstream>
#include<cmath>

#include<fftw3.h>

// macros for complex number
#define REAL 0
#define IMAG 1

using namespace std;

string multiplyON2(string a, string b);
string multiplyFFT(string a, string b);
string addResult(string output, string buff);
string removeZeros(string s);

void fft(fftw_complex *in, fftw_complex *out, const int len);
void ifft(fftw_complex *in, fftw_complex *out, const int len);

void displayComplex(fftw_complex *x, const int len);

string genRandStr(int len);

int main(){
	int maxLen = 16; // 2^maxLen	

	//timing code grabbed from geeksforgeeks.org
	struct timeval start,end;
	double timeTaken;
	
	ofstream dataFile("runtime_cpp.csv");
	dataFile<<"Length (2^n)|ON2 time (sec)|FFT time (sec)"<<endl;

	for(int len = 0; len < maxLen; len++){
		string a = genRandStr(pow(2,len));
		string b = genRandStr(pow(2,len));
		
		dataFile<<len<<", ";

		//timer
		gettimeofday(&start, NULL);
		ios_base::sync_with_stdio(false);
		//ON2 algorithm
		string result1 = multiplyON2(a,b);
		gettimeofday(&end, NULL);
		result1 = removeZeros(result1);

		//cout<<"result1: "<<result1<<endl;
		//time lapsed
		timeTaken = (end.tv_sec - start.tv_sec) * 1e6;
    		timeTaken = (timeTaken + (end.tv_usec - start.tv_usec)) * 1e-6;
		
		dataFile<<setprecision(6)<<timeTaken<<", ";
		
		//timer
		gettimeofday(&start,NULL);
		ios_base::sync_with_stdio(false);
		//FFT algorithm
		string result2 = multiplyFFT(a,b);
		gettimeofday(&end, NULL);
		result2 = removeZeros(result2);

		//cout<<"result2: "<<result2<<endl;
		//time lapsed
		timeTaken = (end.tv_sec - start.tv_sec) * 1e6; 
    		timeTaken = (timeTaken + (end.tv_usec - start.tv_usec)) * 1e-6;
		
		dataFile<<setprecision(5)<<timeTaken<<" "<<endl;
	}

	dataFile.close();
	return 0;
}

string multiplyON2(string a, string b){
	
	string output(a.length()+b.length(),'0');	// initialize to 0
	
	for(size_t countA = 0; countA < a.length(); countA++){
		int carry = 0;
	        string buff(output.length(),'0');
		
		//multiplication
		for(size_t countB = 0; countB < b.length(); countB++){
			int digitA = a[b.length() - countA - 1] - '0';
			int digitB = b[b.length() - countB - 1] - '0';
			int temp = digitA * digitB + carry;
			carry = temp / 10;
			buff[buff.length()-countA-countB-1] = temp % 10 + '0';
		}
		buff[buff.length()-countA-b.length()-1] = carry + '0';
		//cout<<"countA: "<<countA<<" buffer: "<<buff<<endl;

		//accumulate result
		output = addResult(output,buff);
	}
	return output;
}

string multiplyFFT(string a, string b){
	
	//convert to fftw number array
	const size_t lenA = a.length();
	const size_t lenB = b.length();
	//pad to twice the length, zeros at tail
	fftw_complex aIn[lenA*2] = {0}, aOut[lenA*2] = {0};
	fftw_complex bIn[lenB*2] = {0}, bOut[lenB*2] = {0};
	
	for(size_t i=0; i<lenA; i++){
		aIn[i][REAL] = a[i] - '0';
	}
	for(size_t i=0; i<lenB; i++){
		bIn[i][REAL] = b[i] - '0';
	}
	
	//fft
	fft(aIn,aOut,lenA*2);
	fft(bIn,bOut,lenB*2);
	
	//point-wise multiplication, assume a and b has same length
	fftw_complex outputFFT[lenA*2] = {0}; //same length as padded a
	fftw_complex output[lenA*2] = {0};
	string outputStr;
	
	for(size_t i=0; i<lenA*2; i++){
		outputFFT[i][REAL] = aOut[i][REAL]*bOut[i][REAL] - aOut[i][IMAG]*bOut[i][IMAG];
		outputFFT[i][IMAG] = aOut[i][REAL]*bOut[i][IMAG] + aOut[i][IMAG]*bOut[i][REAL];
	}
	ifft(outputFFT,output,lenA*2);
	
	//carry fix
	int countDigit = lenA*2-2; //drop zero at the end
	int carry = 0;
	while(countDigit >= 0){
		int num = output[countDigit][REAL] + carry;
		carry = num / 10;
		num = num % 10;
		outputStr.insert(outputStr.begin(),'0'+num);
		countDigit--;
	}
	outputStr.insert(outputStr.begin(),'0'+carry);

	return outputStr;
}

string addResult(string output, string buff){
	//output and buff have same length
	//carry must be zero for the largest digit	
	int carry = 0;
	for(size_t count = 0; count < output.length(); count++){
		int temp = (output[output.length()-count-1] - '0') + (buff[output.length()-count-1] - '0') + carry;
		carry = temp / 10;
		output[output.length()-count-1] = temp % 10 + '0';
	}

	return output;
}

string removeZeros(string s){
	size_t count = 0;
	while((s[count] - '0' == 0) && (count < s.length())){
		++count;
	}
	if(count < s.length()){
		//cout<<"substring start: "<<count<<endl;
		return s.substr(count);
	}else{
		return "0";
	}
}

void fft(fftw_complex *in, fftw_complex *out, const int len){
	fftw_plan p;
	p = fftw_plan_dft_1d(len,in,out,FFTW_FORWARD,FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	fftw_cleanup();
}

void ifft(fftw_complex *in, fftw_complex *out, const int len){
	fftw_plan p;
	p = fftw_plan_dft_1d(len,in,out,FFTW_BACKWARD,FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	fftw_cleanup();
	//scale the output, copied from youtube tutorial
	for(int i=0; i<len; ++i){
		out[i][REAL] /= len;
		out[i][IMAG] /= len;
	}
}

void displayComplex(fftw_complex *x, const int len){
	//copied from youtube tutorial
	//display complex number in a+bi form
	cout<<"[";
	for(int i=0; i<len; ++i){
		if(x[i][IMAG]<0){
			cout<<x[i][REAL]<<"-"<<abs(x[i][IMAG])<<"i ";
		}else{
			cout<<x[i][REAL]<<"+"<<abs(x[i][IMAG])<<"i ";
		}
	}
	cout<<"]"<<endl;
}

string genRandStr(int len){
	//generate random string of number of given length, len > 0
	int count = 0;
	string s;
	while(count < len-1){
		s.push_back('0' + (rand() % 10));
		count++;
	}
	s.insert(s.begin(),'0'+(rand() % 10 + 1)); //make sure the leftmost digit is nonzero
	
	return s;
}
