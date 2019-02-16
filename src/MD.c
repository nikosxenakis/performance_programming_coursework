/*
 *  Simple molecular dynamics code.
 *
 */
#include <stdio.h>
#include <math.h>
#include "coord.h"
#include "util.h"

void evolve(int count,double dt)
{
  int  step;
  int i,j,k,l;
  int collided;
  double Size;

  /*
   * Loop over timesteps.
  */
  for(step = 1;step<=count;step++)
  {
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);

    for(j=0;j<Ndim;j++)
    {
      /* set the viscosity term in the force calculation */
      visc_force(Nbody,f[j],vis,velo[j]);
      /* add the wind term in the force calculation */
      wind_force(Nbody,f[j],vis,wind[j]);
    }

    /* calculate distance from central mass */
    for(i=0;i<Nbody;i++)
    {
      r[i] = 0.0;
    }
        
    for(i=0;i<Ndim;i++)
    {
	   add_norm(Nbody,r,pos[i]);
    }
        
    for(i=0;i<Nbody;i++)
    {
      r[i] = sqrt(r[i]);
    }
    
    /* calculate central force */
    for(i=0;i<Nbody;i++)
    {
	    for(l=0;l<Ndim;l++)
      {
        f[l][i] = f[l][i] - 
          force(G*mass[i]*M_central,pos[l][i],r[i]);
	    }
	  }

    /* calculate pairwise separation of particles */
    for(i=0;i<Nbody;i++)
    {
      for(j=i+1;j<Nbody;j++)
      {
        for(l=0;l<Ndim;l++)
        {
          delta_pos[l][k] = pos[l][i] - pos[l][j];
        }
      }
    }

    /* calculate norm of separation vector */
    for(i=0;i<Npair;i++)
    {
      delta_r[i] = 0.0;
    }
    for(i=0;i<Ndim;i++)
    {
	    add_norm(Npair,delta_r,delta_pos[i]);
    }
    for(i=0;i<Npair;i++)
    {
      delta_r[i] = sqrt(delta_r[i]);
    }

    /*
     * add pairwise forces.
    */
    k = 0;
    for(i=0;i<Nbody;i++)
    {
      for(j=i+1;j<Nbody;j++)
      {
        Size = radius[i] + radius[j];
        collided=0;
        for(l=0;l<Ndim;l++)
        {
          double force_val = force(G*mass[i]*mass[j],delta_pos[l][k],delta_r[k]);
          /*  flip force if close in */
          if( delta_r[k] >= Size )
          {
            f[l][i] += - force_val;
            f[l][j] += force_val;
          }
          else
          {
            f[l][i] += force_val;
            f[l][j] += - force_val;
            collided=1;
          }
        }
        if( collided == 1 )
        {
          collisions++;
        }
        k = k + 1;
      }
    }

    for(i=0;i<Nbody;i++)
    {
      for(j=0;j<Ndim;j++)
      {
        /* update positions */
        pos[j][i] += dt * velo[j][i];
        /* update velocities */
        velo[j][i] += dt * (f[j][i]/mass[i]);
      }
    }

  }

}
