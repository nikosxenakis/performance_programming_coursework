/*
 *  Simple molecular dynamics code.
 *
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "coord.h"
#include "util.h"

#include <assert.h>

void evolve (int Nstep, double dt, double f[][Ndim] , double pos[][Ndim] , const double * restrict vis, \
  double velo[][Ndim] , double * restrict mass, const double * restrict radius, const double * restrict wind, unsigned int collisions) {

  unsigned int step;
  int i, j, k, l;
  double size, force_val, mass_square, radious_add, delta_r, r;
  double delta_pos[Ndim + PADDING_NDIM] __attribute__((aligned(CACHE_LINE_SIZE)));
  double tmp_f[Ndim + PADDING_NDIM] __attribute__((aligned(CACHE_LINE_SIZE)));

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

      // r = add_norm(Ndim, pos[i]);
      r = 0.0;
      for(l=0; l<Ndim; l++)
        r += pow(pos[i][l], 2);
      r = sqrt(r);

      // wind_visc_force(Ndim, f[i], vis[i], velo[i], wind);
      for(l=0; l<Ndim; l++) {
        f[i][l] = - vis[i] * (velo[i][l] + wind[l]);
        f[i][l] -= force(M_central_x_G*mass[i], pos[i][l], r);
      }

    }

    k = 0;

    for(i=0; i<Nbody; ++i) {
      memset(tmp_f, 0, sizeof(tmp_f));
      #pragma simd aligned private(delta_r, delta_pos, force_val, mass_square, radious_add) reduction(+:tmp_f)
      for(j=Nbody-1; j>=i+1; --j) {

        delta_r = 0.0;
        for(l=0;l<Ndim;++l) {
          delta_pos[l] = pos[i][l] - pos[j][l];
          delta_r += pow(delta_pos[l], 2);
        }
        delta_r = sqrt(delta_r);

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
