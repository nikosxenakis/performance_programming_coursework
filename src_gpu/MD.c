/*
 *  Simple molecular dynamics code.
 *
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "coord.h"
#include "util.h"

void evolve (int Nstep, double dt, double f[][Ndim] , double pos[][Ndim] , const double * restrict vis, \
  double velo[][Ndim] , double * restrict mass, const double * restrict radius, const double * restrict wind) {

  int i, j, k, l;
  unsigned int step;
  double size, force_val, mass_square, radious_add, delta_r, r;
  double delta_pos[Ndim + PADDING] __attribute__((aligned(64)));
  double tmp_f[Ndim + PADDING] __attribute__((aligned(64)));

  /*
   * Loop over timesteps.
  */
  // Nstep=1;
  for(step = 1;step<=Nstep;++step)
  {
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);

    /* calculate distance from central mass */
    #pragma simd aligned linear(vis, mass)
    for(i=0; i<Nbody; ++i) {

      r = add_norm(Ndim, pos[i]);

      for(l=0; l<Ndim; l++) {
        f[i][l] = visc_wind_force(vis[i], velo[i][l], wind[l]);
        f[i][l] -= force(M_central_x_G*mass[i], pos[i][l], r);
      }

    }

    k = 0;

    for(i=0; i<Nbody; ++i) {
      memset(tmp_f, 0, sizeof(tmp_f));
      #pragma simd aligned private(delta_r, delta_pos, force_val, mass_square, radious_add) reduction(+:tmp_f, collisions)
      for(j=Nbody-1; j>=i+1; --j) {
        for(l=0;l<Ndim;++l) 
          delta_pos[l] = pos[i][l] - pos[j][l];
        delta_r = add_norm(Ndim, delta_pos);


        mass_square = G*mass[i]*mass[j];
        radious_add = radius[i] + radius[j];

        if( delta_r >= radious_add ) {
          for(l=0;l<Ndim;l++) {
            force_val = force(mass_square, delta_pos[l], delta_r);
            f[j][l] += force_val;
            tmp_f[l] -= force_val;
          }
        }
        else {
          for(l=0; l<Ndim; l++) {
            force_val = force(mass_square, delta_pos[l], delta_r);
            f[j][l] -= force_val;
            tmp_f[l] += force_val;
          }
          collisions++;
        }

        k = k + 1;
      }
      for(l=0; l<Ndim; l++)
        f[i][l] += tmp_f[l];
    }

    #pragma simd aligned linear(mass)
    for(i=Nbody-1; i>=0; --i) {
      for(l=0; l<Ndim; ++l) {
        /* update positions */
        pos[i][l] += dt * velo[i][l];        
        /* update velocities */
        velo[i][l] += dt * (f[i][l]/mass[i]);
      }
    }

  }
}
