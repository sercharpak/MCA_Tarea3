from numpy import *
from scipy.special import erf

#FUNCTIONS

#Modelo
def model(x, log_rho_0, log_r_c, alpha, beta):

    rho = 10.0**log_rho_0
    r_c = 10.0**log_r_c

    return rho_0/(((x/r_c)**alpha)*((1+x/r_c)**beta))

#likelihood
def likelihood(y_obs, y_mod):
    chi_squared_y = (1.0/2.0)*sum((y_obs - y_mod)**2)
    return -chi_squared_y

#MCMC
def mcmc(x_d, y_d):

    #Initial guess
    log_rho_0_0 = 3
    log_r_c_0 = -0.5
    alpha_0 = 1
    beta_0 = 2

    x_fit0 = x_d
    y_fit0 = model(x_fit0_0, log_rho_0_0, log_r_c_0, alpha_0, beta_0)


    #Empty arrays to save steps

    log_rho_0_walk = empty((0))
    log_r_c_walk = empty((0))
    alpha_walk = empty((0))
    beta_walk = empty((0))

    l_walk = empty((0))


    #Initial values

    log_rho_0_walk = append(log_rho_0_walk, log_rho_0_0)
    log_r_c_walk = append(log_r_c_walk, log_r_c_0)
    alpha_walk = append(alpha_walk, alpha_0)
    beta_walk = append(beta_walk, beta_0)

    l_walk = append(l_walk, likelihood(y_d, y_fit0))


    #MCMC Loop

    n_steps = 20000

    for i in range(n_steps):

        log_rho_0_prime = random.normal(log_rho_0_walk[i], 0.1)
        log_r_c_prime = random.normal(log_r_c_walk[i], 0.1)
        alpha_prime = random.normal(alpha_walk[i], 0.1)
        beta_prime = random.normal(beta_walk[i], 0.1)

        y_previous = model(x_d, log_rho_0_walk[i], log_r_c_walk[i], alpha_walk[i], beta_walk[i])
        y_prime = model(x_d, log_rho_0_prime, log_r_c_prime, alpha_prime, beta_prime)

        l_previous = likelihood(y_d, y_previous)
        l_prime = likelihood(y_d, y_prime)

        a = l_prime / l_previous

        if(a <= 1.0):

            log_rho_0_walk = append(log_rho_0_walk, log_rho_0_prime)
            log_r_c_walk = append(log_r_c_walk, log_r_c_prime)
            alpha_walk = append(alpha_walk, alpha_prime)
            beta_walk = append(beta_walk, beta_prime)

            l_walk = append(l_walk, l_prime)

        else:

            b = random.random()

            if( log(b) <= -a):

                log_rho_0_walk = append(log_rho_0_walk, log_rho_0_prime)
                log_r_c_walk = append(log_r_c_walk, log_r_c_prime)
                alpha_walk = append(alpha_walk, alpha_prime)
                beta_walk = append(beta_walk, beta_prime)

                l_walk = append(l_walk, l_prime)

            else:

                log_rho_0_walk = append(log_rho_0_walk, log_rho_0_walk[i])
                log_r_c_walk = append(log_r_c_walk, log_r_c_walk[i])
                alpha_walk = append(alpha_walk, alpha_walk[i])
                beta_walk = append(beta_walk, beta_walk[i])

                l_walk = append(l_walk, l_previous)


    #Best values

    log_rho_0 = log_rho_0_walk[-1]
    log_r_c = log_r_c_walk[-1]
    alpha = alpha_walk[-1]
    beta = beta_walk[-1]

    rho = 10.0**log_rho_0
    r_c = 10.0**log_r_c

    #Standard Deviations (discarding first 50 steps)

    log_rho_0_std = std(log_rho_0_walk[50:])
    log_r_c_std = std(log_r_c_walk[50:])
    alpha_std = std(alpha_walk[50:])
    beta_std = std(beta_walk[50:])

    rho_std = 10.0**log_rho_0_std
    r_c_std = 10.0**log_r_c_std

    return rho_0, r_c, alpha, beta, rho_0_std, r_c_std, alpha_std, beta_std
