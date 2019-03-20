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
  double radius_sum, force_val, mass_square, r, delta_r;
  double delta_pos[Ndim + PADDING] __attribute__((aligned(64)));
  double tmp_f[Ndim + PADDING] __attribute__((aligned(64)));

  /*
  * Loop over timesteps.
  */
  // count = 1;
  for(step = 1;step<=count;step++){
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);
    
    #pragma simd aligned //linear(vis, mass)
    for(i=0; i<Nbody; i++) {

      /* calculate distance from central mass */
      r = add_norm(Ndim, pos[i]);

      for(l=0; l<Ndim; l++) {
        /* set the viscosity term in the force calculation */
        /* add the wind term in the force calculation */
        f[i][l] = visc_wind_force(vis[i], velo[i][l], wind[l]);
    
        /* calculate central force */
        f[i][l] -= force(G_mul_M_central*mass[i],pos[i][l],r);
      }
    }

    /*
    * add pairwise forces.
    */
    k = 0;
    for(i=0; i<Nbody; i++) {
      memset(tmp_f, 0, sizeof(tmp_f));
      #pragma simd aligned private(delta_r, delta_pos, force_val, mass_square, radius_sum) reduction(+:tmp_f, collisions)
      for(j=i+1; j<Nbody; j++) {

        /* calculate pairwise separation of particles */
        for(l=0; l<Ndim; l++) {
          delta_pos[l] = pos[i][l] - pos[j][l];
        }

        /* calculate norm of separation vector */
        delta_r = add_norm(Ndim, delta_pos);

        mass_square = G*mass[i]*mass[j];
        radius_sum = radius[i] + radius[j];

        /*  flip force if close in */
        if( delta_r >= radius_sum ) {
          for(l=0; l<Ndim; l++) {
            force_val = force(mass_square,delta_pos[l],delta_r);
            // f[i][l] -= force_val;
            tmp_f[l] -= force_val;
            f[j][l] += force_val;
          }
        }
        else {
          for(l=0; l<Ndim; l++) {
            force_val = force(mass_square,delta_pos[l],delta_r);
            // f[i][l] += force_val;
            tmp_f[l] -= force_val;
            f[j][l] -= force_val;
          }
          collisions++;
        }
        k++;
      }
      for(l=0; l<Ndim; l++)
        f[i][l] += tmp_f[l];
    }

    // #pragma simd aligned linear(mass)
    for(i=Nbody-1; i>=0; i--) {
      for(l=0; l<Ndim; l++) {
        /* update positions */
        pos[i][l] += + dt * velo[i][l];
        /* update velocities */
        velo[i][l] += + dt * (f[i][l]/mass[i]);
      }
    }
  }
}
