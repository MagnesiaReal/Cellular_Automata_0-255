import matplotlib.pyplot as plt

archivos = ['EsteesunVirusDesv.gg']
color = ['green']


i = 0
for a in archivos:
    X, Y = [], []
    for line in open(a, 'r'):
        values = [float(s) for s in line.split()]
        X.append(values[0])
        Y.append(values[1])
        plt.plot(X, Y, color=color[0])
    i = i +1

plt.show()
