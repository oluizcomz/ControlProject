"""
Esse codigo simula o comportamento do aeropendulo em malha aberta
"""
# Importando bibliotecas
from scipy.integrate import odeint
from numpy import zeros, ones, arange, pi, sin, sqrt
import matplotlib.pyplot as plt

# Definindo dinamica da planta
def din_aeropend(y, t, input):
    # Definindo estados
    a =  -0.001334
    b = 0.01624
    x1 = y
    # Dinamica do pendulo
    x1p = (a*input) - (b*x1)
    return x1p


# Parametros de simulacao
Ta = 0.1  # intervalo de amostragem
Tsim = 1200  # tempo de simulacao
kend = int(Tsim/Ta)
Tdelay = 14

# Scopes
input = zeros(kend)  # rad/s
temp = zeros(kend)  # posicao angular
erro = zeros(kend)  # erro de rastreamento

temp_ref = zeros(kend)  # referencia p/ posicao angular

# Valores de equilibrio
temp_init = 35
input_init = 0

#controlador 
ka = 0.0347
A = 0.02613
input_before = 0.0
# Loop
for k in range(kend-1):

    # Entrada da planta
    
    temp_ref[k] = -5
    erro[k] =  temp[k] - temp_ref[k]
        # Acao de controle (controlador PI+V)
    if(k-int(Tdelay/Ta)> 0):
        input[k] = (ka*erro[k]) - (A*erro[k-1]) + input_before
        # parcela = (ka*erro[k]) - (A*erro[k-1]) 
        input_before = input[k]
    #saturação
    if(input[k]< 18):
        input[k] = 0
    if(input[k]> 85):
        input[k] = 85
    
    # Evoluindo a din. da planta
    x0 = [temp[k],]   # condicao inicial
    sol = odeint(din_aeropend, x0, [0.0, Ta], args=(input[k-int(Tdelay/Ta)] + input_init,))
    temp[k + 1] = sol[:, 0][-1]

# Plotando resultados
fig1 = plt.figure()
time = arange(0, Tsim, Ta)
plt.plot(time, (temp + temp_init), lw=2, label=r'temperatura (°C)')
plt.xlabel('Tempo (s)')
plt.legend()
plt.grid(True)

fig2 = plt.figure()
plt.plot(arange(0, Tsim-Ta, Ta), input[0:-1] + input_init, 'r--', lw=2, label=r'entrada(pwm)')
plt.xlabel('Tempo (s)')
plt.legend()
plt.grid(True)

fig3 = plt.figure()
plt.plot(arange(0, Tsim-Ta, Ta), erro[0:-1], 'r--', lw=2, label=r'erro')
plt.xlabel('Tempo (s)')
plt.legend()
plt.grid(True)

plt.show()
print(f"aqui { (ka*A*5)}")