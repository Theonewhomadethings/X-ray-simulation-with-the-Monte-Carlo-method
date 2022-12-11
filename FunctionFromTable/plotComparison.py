import matplotlib.pyplot as plt
import numpy as np

originalData = np.loadtxt("Formatdata.txt")
plt.plot(originalData[:,0], originalData[:,1], 'r-')
plt.xlabel("Photon Energy [ev] ")
plt.ylabel("Photons / sec ")
plt.title("Photon energy spectrum from synchotron radiation source.")
#plt.legend()
plt.savefig("pythonPlot1.png")
