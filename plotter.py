import matplotlib.pyplot as plt
import numpy as np

x = np.array([0.1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) #thickness
y = np.array([4618, 6173, 6789, 7175, 7446, 7658, 7833, 7975, 8103, 8203, 8283]) #mean values from histograms
xerr = np.zeros(10)
yerr = np.array([1885, 1653, 1527, 1437, 1381, 1296, 1239, 1186, 1139, 1098, 1061]) #std deviation values from histograms

plt.errorbar(x, y, yerr, fmt = "o")
plt.xlabel("Thickness x [mm]")
plt.ylabel("Mean energy values [eV]")
plt.title("Mean energy as a function to thickness of Berylium ")
plt.savefig("thicknessVsMeanEnergyPlot.png")
