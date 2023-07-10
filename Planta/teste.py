#!/usr/bin/env python
# -*- coding: utf-8 -*-


from pylab import *

#-----------------Constantes-------------#
m=1.0 	 # kg       	Massa
k=20.0 	 # N/m      	Constante da mola
b=10    # N/(m/s)      Constante do amortecedor
F=1      # N		Entrada constante degrau unitário



#-------------- Matrizes das equacoes de estado -----------#
# 	X'=Ax+BU
#       Y=Cx
# G = -0.001334/s+0.01624 => - 1 /  749,63 * s  + 0.01624 /0.001334
A=[[0.,1.],[-0.01624, -1]]   # Matriz de estado
B=[0,-0.001334]
U=700		# Matriz de entrada
C=[1.,0]
x=[0.,0.]                # Condição inicial nula


A=matrix(A)		# Cria objetos matrizes
B=matrix(B) ; B=B.transpose()
C=matrix(C) ; 
x=matrix(x) ;  x=x.transpose()
print('matriz')
print(A)
print(B)

h=0.001 #s  segundos  Intervalo de tempo de amostragem(discretização)
tf=10  #s  segundos  Tempo final da simulação

t=arange(0,tf,h)

# Matrizes para sistema discreto
#
#	x[n+1]=Ad.x[n]+Bd.u[n] 	;;  Ad=(I+hA)
#       y[n]=C.x[n]                 Bd=hB
#

Ad=eye(2)+h*A   
Bd=h*B

xx=[[],[]] 	# Lista com valores de x

for tk in t:
	x=Ad*x+Bd*U
	xx[0].append(x.item(0))
	xx[1].append(x.item(1))


xx[0]=array(xx[0])
xx[1]=array(xx[1])

plot(t,xx[0])
plot(t,xx[1])
show()