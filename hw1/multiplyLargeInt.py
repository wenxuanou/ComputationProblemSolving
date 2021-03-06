import numpy as np
from scipy.fft import fft, ifft
import random
import time

def genRandNum(l):
    num1 = ""
    num2 = ""
    for count in range(l):
        num1 += str(random.randint(0,9))
        num2 += str(random.randint(0,9))
    
    return num1, num2

def multiplyON2(a, b, l):
    output = "0"*(l*2)
    for countA in range(0, l):
        temp = "0"*(countA)
        carry = 0
        for countB in range(0, l):
            prod = int(a[l - countA - 1]) * int(b[l - countB - 1]) + carry
            carry = prod // 10
            prod = prod % 10
            temp = str(prod) + temp
        temp = str(carry) + temp; 
        temp = "0"*(l - countA - 1) + temp
        output = addStr(output,temp,l*2)
    return output


def multiplyFFT(a, b, l):
    arrA = []
    arrB = []

    for count in range(l):
        arrA.append(int(a[count]))
        arrB.append(int(b[count]))
    
    arrA = np.array(arrA)
    arrB = np.array(arrB)

    # pad zeros
    arrA = np.append(arrA, np.zeros((l,1)))
    arrB = np.append(arrB, np.zeros((l,1)))

    arrAFT = fft(arrA)
    arrBFT = fft(arrB)
    # elementwise multiplication
    outputFT = np.multiply(arrAFT, arrBFT)

    output = np.real(ifft(outputFT))
    
    # convert back to string, carry fix
    outputStr = ""
    l_out = 2*l
    carry = 0
    for count in range(1,l_out):
        temp = output[l_out - count - 1] + carry
        carry = int(temp // 10)
        temp = int(temp % 10)
        outputStr = str(temp) + outputStr 
    
    outputStr = str(carry) + outputStr
    
    return outputStr

def addStr(a,b,l):
    # a,b have same length len
    carry = 0
    output = ""
    for ll in range(0,l):
        sumVal = int(a[l - ll - 1]) + int(b[l - ll - 1]) + carry
        carry = sumVal // 10
        sumVal = sumVal % 10
        output = str(sumVal) + output
    return output

if __name__ == "__main__":
    
    file = open("runtime_python.csv","w")
    file.write("Length(2^n)|ON2time(sec)|FFTtime(sec)\n")
    for count in range(0,14):
        l = 2 ** count
        num1,num2 = genRandNum(l)
    
        start_time = time.time()
        outputON2 = multiplyON2(num1, num2, l)
        ON2_time = time.time() - start_time
        #print("outputON2: ", outputON2) 

        start_time = time.time()
        outputFFT = multiplyFFT(num1, num2, l)
        FFT_time = time.time() - start_time
        #print("outputFFT: ", outputFFT)
        
        #print(count, " ON2_time: ", ON2_time, " FFT_time: ", FFT_time)
        file.write(str(count)+", "+str(ON2_time)+", "+str(FFT_time)+" \n")
        print(count)

    file.close()
