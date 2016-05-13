import sys, warnings
import numpy as np
import matplotlib.pyplot as plt
from mcmc import mcmc, model

warnings.filterwarnings("ignore")

plt.rc('text', usetex=True, fontsize=24)

def radius(data):
    E_pot = data[:,6]
    min_pot = np.argmin(E_pot)
    #print "min_pot", min_pot
    x = data[:,0] - data[min_pot, 0]
    y = data[:,1] - data[min_pot, 1]
    z = data[:,2] - data[min_pot, 2]
    r = np.sqrt(x**2 + y**2 +z**2)
    r = np.sort(r)
    return r[1:]

if (len(sys.argv) != 2):
    sys.exit('Usage: python fit.py n_bodies')

#data

n_bodies = int(sys.argv[1])

data_final = np.loadtxt('./state_final_{}.dat'.format(n_bodies))

#x
r_final = radius(data_final)
log_r_final = np.log10(r_final)

h, c = np.histogram(log_r_final, bins=10)
log_r_center = 0.5 * (c[1:]+c[:-1])

#y
log_rho = np.log10(h)-2.0*log_r_center #log(rho) = log(m)-2*log(r)


#plot data

plt.figure(figsize=(12,8))

plt.plot(log_r_center, log_rho, label='$\mathrm{data}$')

plt.xlabel(r'$\log{(r)}$')
plt.ylabel(r'$\log{(\rho (r))}$')
plt.legend(loc='lower left')

plt.savefig('./mcmc_plots/density_profile_data.png')


#fit
#$\rho(r) = \frac{\rho_0}{(\frac{r}{r_c})^\alpha (1+\frac{r}{r_c})^\beta}$

log_rho_0_0 = 4
log_r_c_0 = -1.0
alpha_0 = 1
beta_0 = 2

fit_0 = model(log_r_center, log_rho_0_0, log_r_c_0, alpha_0, beta_0)


# plot first guess

plt.figure(figsize=(12,8))

plt.plot(log_r_center, log_rho, label='$\mathrm{data}$')
plt.plot(log_r_center, fit_0, label='$\mathrm{first\;guess}$')

plt.xlabel(r'$\log{(r)}$')
plt.ylabel(r'$\log{(\rho (r))}$')
plt.legend(loc='lower left')

plt.savefig('./mcmc_plots/density_profile_firstguess.png')


#fit

log_rho_0, log_r_c, alpha, beta, log_rho_0_std, log_r_c_std, alpha_std, beta_std = mcmc(log_r_center, log_rho)

fit = model(log_r_center, log_rho_0, log_r_c, alpha, beta)


#plot fit

plt.figure(figsize=(12,8))

plt.plot(log_r_center, log_rho, label='$\mathrm{data}$')
plt.plot(log_r_center, fit, label='$\mathrm{fit}$')

plt.xlabel(r'$\log{(r)}$')
plt.ylabel(r'$\log{(\rho (r))}$')
plt.legend(loc='lower left')

plt.savefig('./mcmc_plots/density_profile_fit.png')


#best values

print('log(rho_0) = {} +/- {}'.format(log_rho_0, log_rho_0_std))
print('log(r_c) = {} +/- {}'.format(log_r_c, log_r_c_std))
print('alpha = {} +/- {}'.format(alpha, alpha_std))
print('beta = {} +/- {}'.format(beta, beta_std))
