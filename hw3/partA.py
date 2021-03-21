import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy import integrate

def lorenzSys(P,sigma,rho,beta):
	dP = np.zeros((1,3))
	dP[0,0] = sigma * (P[1] - P[0])
	dP[0,1] = P[0] * (rho - P[2]) - P[1]
	dP[0,2] = P[0] * P[1] - beta * P[2]

	return dP

def randVec():
	# modified from random 3D unit vector code
	# https://gist.github.com/andrewbolster/10274979
	phi = np.random.uniform(0,np.pi*2)
	costheta = np.random.uniform(-1,1)
	theta = np.arccos( costheta )
	r = np.random.uniform(0,0.3)
	
	vec = np.zeros((1,3))
	vec[0,0] = np.sin( theta) * np.cos( phi )
	vec[0,1] = np.sin( theta) * np.sin( phi )
	vec[0,2] = np.cos( theta )
	vec = vec * r

	return vec

if __name__ == "__main__":
	# parameters
	beta = 8/3
	rho = 28
	sigma = 10
	# starting point
	x0 = 1
	y0 = 1
	z0 = 1
	# iteration
	#iteration = 2000
	iteration = 1000

	for simNum in range(0,1000):
		# buffers
		P = np.zeros((iteration,3))
		P[0,0] = x0
		P[0,1] = y0
		P[0,2] = z0
	
		# small random perturb
		P[0,:] = P[0,:] + randVec()
	
		# compute values
		for count in range(1,iteration):
			dP = lorenzSys(P[count - 1,:],sigma,rho,beta)
			P[count,:] = P[count - 1,:] + 0.01 * dP	
	
		if simNum == 100 or simNum == 500:
			# plot
			fig = plt.figure()
			ax = plt.axes(projection='3d')
			ax.plot3D(P[:,0],P[:,1],P[:,2])
			#plt.show()	# show() does not work without X11 support
			plt.savefig("plot" + str(simNum) + ".pdf")
	
		# save result
		filename = "data/simulation" + str(simNum) + ".csv"
		np.savetxt(filename,P,delimiter=",")

