import numpy as np
from scipy import sparse
import random


length = 4096  # square matrix length*length
numElem = int(length / 4)


D = np.zeros((length,length))

for elem in range(1, numElem+1):
    i = random.randint(0,length-1)
    j = random.randint(0,length-1)
    D[i,j] = elem


#print("D:")
#print(D)

mat = sparse.csr_matrix(D)

matArray = mat.toarray()

#print("row output")
#print(mat)

#print("to array")
#print(matArray)

# save csr matrix
sparse.save_npz("myMatrix.npz", mat)

np.savetxt("myMatrix.txt", matArray)
