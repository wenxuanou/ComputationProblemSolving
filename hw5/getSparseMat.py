import numpy as np
from scipy import sparse
import random


numElem = 10
length = 5  # square matrix length*length

D = np.zeros((length,length))

for elem in range(1, numElem+1):
    i = random.randint(0,length-1)
    j = random.randint(0,length-1)
    D[i,j] = elem


print("D:")
print(D)

mat = sparse.csr_matrix(D)

print("row output")
print(mat)

print("to array")
print(mat.toarray())

# save csr matrix
sparse.save_npz("myMatrix.npz", mat)


