import numpy as np

#FUNCTIONS

#Modelo
def model(x, log_rho_0, log_r_c, alpha, beta):

    #rho = rho_0/(((radius/r_c)**alpha)*((1+x/r_c)**beta))

    radius = 10**x
    r_c = 10**log_r_c

    log_rho = log_rho_0 - alpha*(x-log_r_c) - beta*(np.log10(radius+r_c)-log_r_c)

    return log_rho

#likelihood
def likelihood(y_obs, y_mod):
    chi_squared_y = (1.0/2.0)*np.sum((y_obs - y_mod)**2)
    return -chi_squared_y

#MCMC
def mcmc(x_d, y_d):

    #Initial guess
    log_rho_0_0 = 4
    log_r_c_0 = -1.0
    alpha_0 = 1
    beta_0 = 2

    x_fit_0 = x_d
    y_fit_0 = model(x_fit_0, log_rho_0_0, log_r_c_0, alpha_0, beta_0)


    #Empty arrays to save steps

    log_rho_0_walk = np.empty((0))
    log_r_c_walk = np.empty((0))
    alpha_walk = np.empty((0))
    beta_walk = np.empty((0))

    l_walk = np.empty((0))


    #Initial values

    log_rho_0_walk = np.append(log_rho_0_walk, log_rho_0_0)
    log_r_c_walk = np.append(log_r_c_walk, log_r_c_0)
    alpha_walk = np.append(alpha_walk, alpha_0)
    beta_walk = np.append(beta_walk, beta_0)

    l_walk = np.append(l_walk, likelihood(y_d, y_fit_0))


    #MCMC Loop

    n_steps = 50000

    for i in range(n_steps):

        log_rho_0_prime = np.random.normal(log_rho_0_walk[i], 0.1)
        log_r_c_prime = np.random.normal(log_r_c_walk[i], 0.1)
        alpha_prime = np.random.normal(alpha_walk[i], 0.1)
        beta_prime = np.random.normal(beta_walk[i], 0.1)

        y_previous = model(x_d, log_rho_0_walk[i], log_r_c_walk[i], alpha_walk[i], beta_walk[i])
        y_prime = model(x_d, log_rho_0_prime, log_r_c_prime, alpha_prime, beta_prime)

        l_previous = likelihood(y_d, y_previous)
        l_prime = likelihood(y_d, y_prime)

        a = l_prime / l_previous

        if(a <= 1.0):

            log_rho_0_walk = np.append(log_rho_0_walk, log_rho_0_prime)
            log_r_c_walk = np.append(log_r_c_walk, log_r_c_prime)
            alpha_walk = np.append(alpha_walk, alpha_prime)
            beta_walk = np.append(beta_walk, beta_prime)

            l_walk = np.append(l_walk, l_prime)

        else:

            b = np.random.random()

            if( np.log(b) <= -a):

                log_rho_0_walk = np.append(log_rho_0_walk, log_rho_0_prime)
                log_r_c_walk = np.append(log_r_c_walk, log_r_c_prime)
                alpha_walk = np.append(alpha_walk, alpha_prime)
                beta_walk = np.append(beta_walk, beta_prime)

                l_walk = np.append(l_walk, l_prime)

            else:

                log_rho_0_walk = np.append(log_rho_0_walk, log_rho_0_walk[i])
                log_r_c_walk = np.append(log_r_c_walk, log_r_c_walk[i])
                alpha_walk = np.append(alpha_walk, alpha_walk[i])
                beta_walk = np.append(beta_walk, beta_walk[i])

                l_walk = np.append(l_walk, l_previous)


    #Best values

    log_rho_0 = log_rho_0_walk[-1]
    log_r_c = log_r_c_walk[-1]
    alpha = alpha_walk[-1]
    beta = beta_walk[-1]

    #Standard Deviations (discarding first 50 steps)

    log_rho_0_std = np.std(log_rho_0_walk[50:])
    log_r_c_std = np.std(log_r_c_walk[50:])
    alpha_std = np.std(alpha_walk[50:])
    beta_std = np.std(beta_walk[50:])

    return log_rho_0, log_r_c, alpha, beta, log_rho_0_std, log_r_c_std, alpha_std, beta_std
