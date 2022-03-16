import numpy as np
import matplotlib.pyplot as plt

numbers = np.loadtxt("number_1.txt")

plt.hist(numbers, bins = 50, density=True, facecolor='pink')


plt.title('Int_distribution')
plt.ylabel('Probability_density')

plt.savefig('Int_distribution.png')

plt.show()