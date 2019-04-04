/*
 *  Simple molecular dynamics code.
 *
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "coord.h"
#include "util.h"

void evolve(int Nstep, double dt, double pos[][Ndim], double velo[][Ndim], double f[][Ndim], double * restrict vis, \
 double * restrict radius, double * restrict mass, double * restrict wind) {

  int  step;
  int i,j,k,l;
  double radius_sum, force_val, mass_square, r, delta_r;
  double delta_pos[Ndim + PADDING] __attribute__((aligned(64)));
  double tmp_f[Ndim + PADDING] __attribute__((aligned(64)));

  /*
  * Loop over timesteps.
  */
  Nstep = 1;
  for(step = 1;step<=Nstep;step++){
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);
    
    // #pragma simd aligned linear(vis, mass)
    #pragma clang loop vectorize(enable) interleave(enable)
    for(i=0; i<Nbody; i++) {
      /* calculate distance from central mass */
      r = add_norm(Ndim, pos[i]);

      /* set the viscosity term in the force calculation */
      /* add the wind term in the force calculation */
      visc_wind_force(Ndim, f[i], vis[i], velo[i], wind);

      /* calculate central force */
      #pragma clang loop unroll(enable)
      for(l=0; l<Ndim; l++) {
        f[i][l] -= force(G_mul_M_central*mass[i],pos[i][l],r);
      }
    }

    /*
    * add pairwise forces.
    */
    k = 0;
    for(i=0; i<Nbody; i++) {
      memset(tmp_f, 0, Ndim*sizeof(double));
      // #pragma simd aligned private(delta_r, delta_pos, force_val, mass_square, radius_sum) reduction(+:tmp_f, collisions)
      #pragma clang loop vectorize(enable) interleave(enable)
      for(j=i+1; j<Nbody; j++) {

        /* calculate pairwise separation of particles */
        for(l=0; l<Ndim; l++) {
          delta_pos[l] = pos[i][l] - pos[j][l];
        }

        /* calculate norm of separation vector */
        delta_r = add_norm(Ndim, delta_pos);

        radius_sum = radius[i] + radius[j];
        mass_square = G*mass[i]*mass[j];

        /*  flip force if close in */
        if( delta_r >= radius_sum ) {
          for(l=0; l<Ndim; l++) {
            force_val = force(mass_square,delta_pos[l],delta_r);
            tmp_f[l] -= force_val;
            f[j][l] += force_val;
          }
        }
        else {
          for(l=0; l<Ndim; l++) {
            force_val = force(mass_square,delta_pos[l],delta_r);
            tmp_f[l] += force_val;
            f[j][l] -= force_val;
          }
          collisions++;
        }
        k = k + 1;
      }
      for(l=0; l<Ndim; l++)
        f[i][l] += tmp_f[l];
    }

    // #pragma simd aligned linear(mass)
    #pragma clang loop vectorize(enable) interleave(enable)
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
