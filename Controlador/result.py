import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 
import os
from numpy import arange
# Plotando resultados
path = './ControlProject/Controlador/dadosResult/result.csv'
# for diretorio, subpastas, arquivos in os.walk(path):
#     print(diretorio)
#     for arquivo in arquivos:
#         print(arquivo)
bd = pd.read_csv(path, delimiter=';', names=[ 'temp','pwm','time(s)','ref','error',''])
temp  = np.array(bd['temp'].values)
time = np.array(bd['time(s)'].values)
input = np.array(bd['pwm'].values)
# ref = np.array(bd['ref'].values)
# error = input - ref
plt.plot(time, temp)
plt.xlabel('time')
plt.ylabel('temp')
plt.grid(True)

fig2 = plt.figure()
plt.plot(time, input, 'r--', lw=2, label=r'entrada(pwm)')
plt.xlabel('Tempo (s)')
plt.legend()
plt.grid(True)

# fig3 = plt.figure()
# plt.plot(time, error, 'r--', lw=2, label=r'erro')
# plt.xlabel('Tempo (s)')
# plt.legend()
# plt.grid(True)
plt.show()