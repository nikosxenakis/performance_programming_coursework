/*
 *  Simple molecular dynamics code.
 *
 */
#include <stdio.h>
#include <math.h>
#include "coord.h"
#include "util.h"

void evolve(int count,double dt) {
  int  step;
  int i,j,k,l;
  double radious_sum, force_val, mass_square;
  /*
  * Loop over timesteps.
  */
  count = 1;
  for(step = 1;step<=count;step++){
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);
    
    for(i=0; i<Nbody; i++) {

      /* calculate distance from central mass */
      r[i] = 0.0;
      add_norm(Ndim,&r[i],pos[i]);
      r[i] = sqrt(r[i]);

      /* set the viscosity term in the force calculation */
      /* add the wind term in the force calculation */
      visc_wind_force(Ndim, f[i], vis[i], velo[i], wind);

      /* calculate central force */
      for(l=0; l<Ndim; l++) {
        f[i][l] -= force(G_mul_M_central*mass[i],pos[i][l],r[i]);
      }
    }

    /*
    * add pairwise forces.
    */
    k = 0;
    for(i=0; i<Nbody; i++) {
      for(j=i+1; j<Nbody; j++) {

        /* calculate pairwise separation of particles */
        for(l=0; l<Ndim; l++) {
          delta_pos[k][l] = pos[i][l] - pos[j][l];
        }

        /* calculate norm of separation vector */
        delta_r[k] = 0.0;
        add_norm(Ndim, &delta_r[k], delta_pos[k]);
        delta_r[k] = sqrt(delta_r[k]);

        radious_sum = radius[i] + radius[j];
        mass_square = G*mass[i]*mass[j];

        /*  flip force if close in */
        if( delta_r[k] >= radious_sum ) {
          for(l=0; l<Ndim; l++) {
            force_val = force(mass_square,delta_pos[k][l],delta_r[k]);
            f[i][l] -= force_val;
            f[j][l] += force_val;
          }
        }
        else {
          for(l=0; l<Ndim; l++) {
            force_val = force(mass_square,delta_pos[k][l],delta_r[k]);
            f[i][l] += force_val;
            f[j][l] -= force_val;
          }
          collisions++;
        }
        k = k + 1;
      }
    }

    
    for(i=0; i<Nbody; i++) {
      for(l=0; l<Ndim; l++) {
        /* update positions */
        pos[i][l] += + dt * velo[i][l];
        /* update velocities */
        velo[i][l] += + dt * (f[i][l]/mass[i]);
      }
    }
  }
}
