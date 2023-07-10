import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 
import os
from numpy import arange
# Plotando resultados
path = './ControlProject/EstinaDelay/Dados/30p70.csv'
# for diretorio, subpastas, arquivos in os.walk(path):
#     print(diretorio)
#     for arquivo in arquivos:
#         print(arquivo)
bd = pd.read_csv(path, delimiter=';')
temp  = np.array(bd['temp'].values)
time = np.array(bd['time(s)'].values)
plt.plot(time, temp)
plt.xlabel('time')
plt.ylabel('temp')
plt.grid(True)
plt.show()