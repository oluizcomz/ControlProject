import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math
import control as control
from scipy.signal import butter, lfilter, freqz,lfilter_zi
from tabulate import tabulate
from scipy import signal
from asyncio.windows_events import NULL
from sklearn.metrics import r2_score

##planta
gain = -0.001334 
polo1 = -0.01624

Num = -gain

Den = [1,-polo1 ]

# G = control.tf(Num,Den)
# C = control.tf([1, 0.247],[1,0]) 
# # C = control.tf([1, 0.124],[1,0])
# C2 = 1# control.tf([0, 1],[1,0])
# print(F"G:{G}")
# print(F"C:{C} * 0.0347")
# print(F"C2:{C2}")
# control.rlocus(G*C * C2)
# plt.show()

## requisitos
ms = 0.09 # maximo sobresinal de 6 porcento 
tr = 350 # tempo de subida de 350 segundos 
eps = math.sqrt((math.log(ms)**2) / ((math.pi**2) + (math.log(ms)**2)))
print(f"eps: {eps}")
wn = (math.pi - math.acos(eps))/(tr *  math.sqrt( 1 -(eps**2)))
print(f"wn: {wn}")
s1 = complex(-eps * wn ,   wn *  math.sqrt( 1 -(eps**2)))
s2 = complex(-eps * wn ,  -wn *  math.sqrt( 1 -(eps**2)))
print(f"S1: {s1}")
print(f"S2: {s2}")



##controlador
teta1 = math.atan (-s1.imag/ (polo1 - s1.real))
teta2 = math.pi - math.atan (-s1.imag / s1.real)
print(f"teta1: {teta1*180/math.pi}, teta1: {teta2*180/math.pi}")
alfa = math.pi - (teta1 + teta2)
print(f"alfa: {alfa*180/math.pi}")
zeroC = s1.real - (s1.imag / math.tan(alfa))
print(f"zero controlador: {zeroC}")
G = - 0.01334/ (s1 +0.01624)
c = (zeroC+ s1)/s1
gainC = 1/abs(G*c)
print(f"ganho controlador {gainC}" )
Ccont = control.tf([gainC, -gainC*zeroC], [1,0])
print(f"C(S) = {Ccont}")


# Convertendo para o dominio discreto
Ta = 0.1
Cd = control.c2d(Ccont, Ta, 'zoh')
print(f"C(z) = {Cd}")

# G = control.tf(Num,Den)
# print(G)
# control.rlocus(G*Ccont)
# plt.plot(s1.real,s1.imag)
# plt.show()