import matplotlib.pyplot as plt
import numpy as np

number, sequence, average = np.loadtxt('Task_2.txt', unpack = True)

plt.figure(figsize=(17,10))
plt.grid(True)

for i in range(len(number)):
	plt.scatter(number[i], average[i], marker = '.', color = 'm')
	plt.text(number[i], average[i]+0.2, str(int(sequence[i])))



plt.ylabel(r'$average\:number$', fontsize = 16)
plt.title('Average amount of random numbers to get consequence')
# plt.savefig('Task_2.png')
plt.show()
