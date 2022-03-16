import matplotlib.pyplot as plt
import numpy as np

N, probability = np.loadtxt('probability.txt', unpack = True)

plt.figure(figsize=(10,7))
plt.grid(True)

plt.scatter(N, probability, marker = '.', color = 'm')

plt.xlabel(r'$N, \: number \: of \: tests$', fontsize = 16)
plt.ylabel(r'$probability$', fontsize = 16)
plt.title('Probability of getting each value from a discrete distribution (1, 100)')
# plt.savefig('Task_1.png')
plt.show()
