import matplotlib.pyplot as plt
import numpy as np

archivos = []

for i in range(0,88):
    archivos.append('Datos500/datosRg' + str(int(i+1)) + '-500c.gg')
    print(archivos[i])

color = ['orange']

X = []
for ir in range(1,501):
    X.append(ir)
    print(ir)

Y = [None] * 88
for i in range(88):
    Y[i] = [None] * 500


fil = 0
for a in archivos:
    for line in open(a, 'r'):
        values = [float(s) for s in line.split()]
        Y[fil].append(values[1])
    fil += 1

prom = [None] * 500
for i in range(500):
    prom[i] = 0

for i in range(0,500):
    for j in range(0,88):
        prom[i] = prom[i] + Y[j][i]
    prom[i] = prom[i]/88

varia = [None] * 500

for i in range(0, 500):
    for j in range(0, 88):
        varia[i] += (Y[j][i]-prom[i])**2
    varia[i] = varia[i]/88

plt.plot(X, varia, color=color[0])

plt.show()
