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
  int collided;
  double Size;
  /*
  * Loop over timesteps.
  */
  count = 1;
  for(step = 1;step<=count;step++){
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);

    /* set the viscosity term in the force calculation */
    for(i=0; i<Nbody; i++) {
      // visc_force(Ndim, f[i], vis[i], velo[i]);
      for(l=0; l<Ndim; l++) {
        f[i][l] = -vis[i] * velo[i][l];
      }
    }

    /* add the wind term in the force calculation */
    for(i=0; i<Nbody; i++) {
      wind_force(Ndim, f[i], vis[i], wind);
    }

    /* calculate distance from central mass */
    for(i=0; i<Nbody; i++) {
      r[i] = 0.0;
    }
    for(i=0; i<Nbody; i++) {
      add_norm(Ndim,&r[i],pos[i]);
    }
    for(i=0; i<Nbody; i++) {
      r[i] = sqrt(r[i]);
    }
    /* calculate central force */
    for(i=0; i<Nbody; i++) {
      for(l=0; l<Ndim; l++) {
        f[i][l] -= force(G*mass[i]*M_central,pos[i][l],r[i]);
      }
    }
    /* calculate pairwise separation of particles */
    k = 0;
    for(i=0; i<Nbody; i++) {
      for(j=i+1; j<Nbody; j++) {
        for(l=0; l<Ndim; l++) {
          delta_pos[k][l] = pos[i][l] - pos[j][l];
        }
        k = k + 1;
      }
    }

    /* calculate norm of separation vector */
    for(k=0; k<Npair; k++){
      delta_r[k] = 0.0;
    }

    for(k=0; k<Npair; k++) {
      add_norm(Ndim, &delta_r[k], delta_pos[k]);
    }

    for(k=0; k<Npair; k++) {
      delta_r[k] = sqrt(delta_r[k]);
    }

    /*
    * add pairwise forces.
    */
    k = 0;
    for(i=0; i<Nbody; i++) {
      for(j=i+1; j<Nbody; j++) {
        Size = radius[i] + radius[j];
        collided=0;
        for(l=0; l<Ndim; l++) {
          /*  flip force if close in */
          if( delta_r[k] >= Size ){
            f[i][l] -= force(G*mass[i]*mass[j],delta_pos[k][l],delta_r[k]);
            f[j][l] += force(G*mass[i]*mass[j],delta_pos[k][l],delta_r[k]);
          }
          else{
            f[i][l] += force(G*mass[i]*mass[j],delta_pos[k][l],delta_r[k]);
            f[j][l] -= force(G*mass[i]*mass[j],delta_pos[k][l],delta_r[k]);
            collided=1;
          }
        }
        if( collided == 1 ){
          collisions++;
        }
        k = k + 1;
      }
    }

    /* update positions */
    for(i=0; i<Nbody; i++) {
      for(l=0; l<Ndim; l++) {
        pos[i][l] += + dt * velo[i][l];
      }
    }

    /* update velocities */
    for(i=0; i<Nbody; i++) {
      for(l=0; l<Ndim; l++) {
        velo[i][l] += + dt * (f[i][l]/mass[i]);
      }
    }

  }

}
