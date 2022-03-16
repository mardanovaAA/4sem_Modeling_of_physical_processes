import matplotlib.pyplot as plt
import numpy as np
from io import StringIO



with open('Data.txt') as file:
	lines = file.readlines()

lines = list(map(lambda x: x.strip("\n").strip().replace(' ', ', '), lines))



plt.figure(figsize=(10,7))
plt.grid(True)


for line in lines:
	X = np.genfromtxt(StringIO(line), delimiter=', ')
	plt.scatter([X[0] for i in range(X.size - 1)], X[1:], marker = '.')
	

# data = np.loadtxt('Data.txt', unpack = False)



# flag = True;

	
# for X in data:
# 	plt.scatter([X[0] for i in range(X.size - 1)], X[1:], marker = '.', label = "r = " + str(X[0]))

plt.xlabel(r'$r$', fontsize = 16)
plt.legend()
plt.ylabel(r'$stabilization$', fontsize = 16)
plt.title('x from i')
plt.savefig('bifurcation.png')
plt.show()