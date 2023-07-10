#LUIZ DA SILVA MOURA 
#11611EMT028
import control as control
from matplotlib import pyplot as plt
import numpy as np
import math

def aval_model(person):
    y, T = model(person)
    return fa(y,T, 20)
#função de avaliação do desenpenho do controlador quanto maior o valor pior o desempenho
def fa(y,t, setpoint):
    ITAE = 0.0
    IAE = 0.0
    ISE = 0.0
    for cal, time in zip(y, t):
        error = cal - setpoint
        ITAE =  ITAE + (time*np.abs(error))
        IAE = IAE + np.abs(error)
        ISE = ISE + (np.abs(error)*np.abs(error))
    if(math.isnan(ITAE +IAE + ISE)):
        print('aqui')
        print(IAE)
        print(IAE)
        print(ISE)
    if((ITAE +IAE + ISE) ==  0):
        return 0
    return(1/(ITAE +IAE + ISE))


def model(people):
    #declarando variavel independente
    kp = people[0]
    ki = people[1]
    kd = people[2]
    print('aqi',people)
    s = control.tf('s')
    #Variaveis do PID
    Pid = kp*(1 + (1/(ki*s)) +(kd*s))
    pi = 25#posição inicial 
    dg = 70#posição final
    time_end = 1000 #tempo final de simulação
    dt = 0.01 # passo da simulação

    G =  ((-0.001381/0.0181 )/(1 + ((1/0.0181) *s)))
    #G = 0.20742/(1 + 35*s);


    nt = int ( time_end / dt ) + 1 # Number of points of sim time
    Ts = control.feedback(G*Pid,1)
    t = np.linspace(0,time_end,nt)
    u = dg * np.ones(nt)
    # T,y= control.forced_response(Ts,t,u , X0 = pi)
    T,y= control.forced_response(Ts,t,u)
    return (y, T)
def plot(PIDs):
    print('ah')
    legend = []
    plt.figure()
    i=0
    for pid in PIDs:
        y,T = model(pid)
        plt.plot(T, y, lw=2)
        legend.append("G {}".format(i))
        i = i +1
    plt.legend(legend)
    plt.xlabel('Tempo (s)')
    plt.ylabel('y')
    plt.grid()
    plt.show()
if __name__ == '__main__':
    print('teste')