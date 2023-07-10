import control as control
import numpy as np
import matplotlib.pyplot as plt
# class Planta:
#     def __init__(self,G,TimeDelay):
#         self.G = G
#         self.TimeDelay = TimeDelay
#         self.s = s
#     def GetG_delay(self):
#         return '{} * e^(-{}s)'.format(self.G,self.TimeDelay)
#     def GetG(self):
#         return self.G
#     def GetDelay(self):
#         return self.TimeDelay
        
# s = control.tf('s')
# G = -0.001334/s+0.01624
# # atraso 20.5
# planta = Planta(G,2)
# print(planta.GetG_delay())
Num = -0.001334

Den = [1,0.01624]

a= 5
Tfim = 100
Gs = control.tf(Num,Den,a)
print(Gs)
dt = 5 # passo da simulação
nt = a +1 #int ( Tfim / dt ) # Number of points of sim time
t = np.linspace(0,Tfim,nt)
u = 70 * np.ones(nt)
print(len(t),len(u))
T,Y= control.step_response() #forced_response(Gs,t,u , X0 =0.0)# odint
plt.plot(T, Y)
plt.show()
print(Gs)
# step(6s)