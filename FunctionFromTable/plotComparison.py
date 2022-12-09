import matplotlib.pyplot as plt
import numpy as np

originalData = np.genfromtxt("formatData.txt")
print(originalData)
plt.plot(originalData[:,0], originalData[:,1], 'r-')
plt.xlabel("Photon Energy [ev] ")
plt.ylabel("Photons / sec ")
#plt.legend()
plt.savefig("pythonPlot.png")
