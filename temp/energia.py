import numpy as np 

inicial = np.loadtxt('./state_0_1000.dat')
final = np.loadtxt('./state_4999_1000.dat')

energia_k_i = np.sum(inicial[:,6])
energia_w_i = np.sum(inicial[:,7])

energia_k_f = np.sum(final[:,6])
energia_w_f = np.sum(final[:,7])

e_i = energia_k_i+energia_w_i
e_f = energia_k_f+energia_w_f

print(e_i)
print(e_f)
print((e_f-e_i)/e_i)
