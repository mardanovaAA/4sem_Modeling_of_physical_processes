import matplotlib.pyplot as plt
import numpy as np

number_step, average_displacement, average_abs_displacement, average_square_displacement = np.loadtxt('rand_walk.txt', unpack = True)

plt.figure(figsize=(10,7))
plt.grid(True)

plt.scatter(number_step, average_displacement, marker = '.', label = "average displacement")
plt.scatter(number_step, average_abs_displacement, marker = '.', label = "average abs displacement")
# plt.scatter(number_step, average_square_displacement, marker = '.', label = "average square displacement")

plt.xlabel(r'$N, \: number \: of \: step$', fontsize = 16)
plt.legend()
plt.ylabel(r'$Displacement$', fontsize = 16)
plt.title('Average Displacement')
# plt.savefig('Task_1.png')
plt.show()

coordinates = np.loadtxt('huge_step.txt', unpack = True)

plt.figure(figsize=(10,7))
plt.grid(True)

plt.hist(coordinates, bins = 50, density=True, facecolor='pink')


plt.title('Coordinates on step 1000')
plt.ylabel('density')

plt.show()
