/*
 *  Simple molecular dynamics code.
 *
 */
#include <stdio.h>
#include <math.h>
#include "coord.h"

void vis_force(int N,double *f, double *vis, double *vel);
void add_norm(int N,double *r, double *delta);
double force(double W, double delta, double r);
void wind_force(int N,double *f, double *vis, double vel);





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
    for(j=0;j<Ndim;j++){
      // visc_force(Nbody,f[j],vis,velo[j]);
      for(i=0;i<Nbody;i++){
        f[i][j] = -vis[i] * velo[i][j];
      }
    }

    /* add the wind term in the force calculation */
    for(j=0;j<Ndim;j++){
      // wind_force(Nbody,f[j],vis,wind[j]);
      for(i=0;i<Nbody;i++){
        f[i][j] += -vis[i] * wind[j];
      }
    }

    /* calculate distance from central mass */
    for(k=0;k<Nbody;k++){
      r[k] = 0.0;
    }
    for(i=0;i<Nbody;i++){
      // add_norm(Ndim,&r[i],pos[i]);
      for(k=0;k<Ndim;k++) {
        r[i] += pos[i][k]*pos[i][k];
      }
    }
    for(k=0;k<Nbody;k++){
      r[k] = sqrt(r[k]);
    }
    /* calculate central force */
    for(i=0;i<Nbody;i++){
      for(l=0;l<Ndim;l++){
        f[i][l] -= force(G*mass[i]*M_central,pos[i][l],r[i]);
      }
    }
    /* calculate pairwise separation of particles */
    k = 0;
    for(i=0;i<Nbody;i++){
      for(j=i+1;j<Nbody;j++){
        for(l=0;l<Ndim;l++){
          delta_pos[k][l] = pos[i][l] - pos[j][l];
        }
        k = k + 1;
      }
    }

    /* calculate norm of separation vector */
    for(k=0;k<Npair;k++){
      delta_r[k] = 0.0;
    }

    for(i=0;i<Ndim;i++) {
      // add_norm(Npair,delta_r,delta_pos[i]);
      for(k=0;k<Npair;k++) {
        delta_r[k] += delta_pos[k][i]*delta_pos[k][i];
      }
    }

    for(k=0;k<Npair;k++){
      delta_r[k] = sqrt(delta_r[k]);
    }

    /*
    * add pairwise forces.
    */
    k = 0;
    for(i=0;i<Nbody;i++){
      for(j=i+1;j<Nbody;j++){
        Size = radius[i] + radius[j];
        collided=0;
        for(l=0;l<Ndim;l++){
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
    for(i=0;i<Nbody;i++){
      for(j=0;j<Ndim;j++){
        pos[i][j] += + dt * velo[i][j];
      }
    }

    /* update velocities */
    for(i=0;i<Nbody;i++){
      for(j=0;j<Ndim;j++){
        velo[i][j] += + dt * (f[i][j]/mass[i]);
      }
    }

  }

}
