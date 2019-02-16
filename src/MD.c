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

    // for(j=0;j<Ndim;j++)
    // {
    //   /* set the viscosity term in the force calculation */
    //   visc_force(Nbody,f[j],vis,velo[j]);
    //   /* add the wind term in the force calculation */
    //   wind_force(Nbody,f[j],vis,wind[j]);
    // }

    for(i=0;i<Ndim;i++)
    {
      for(j=0;j<Nbody;j++)
      {
        /* set the viscosity term in the force calculation */
        /* add the wind term in the force calculation */
        f[i][j] = - vis[j] * (velo[i][j] + wind[i]);
      }
    }

    /* calculate distance from central mass */
    for(i=0;i<Nbody;i++)
    {
      r[i] = 0.0;

      for(k=0;k<Ndim;k++)
      {
        r[i] += (pos[k][i] * pos[k][i]); // or pow(pos[k][i], 2)
      }

      r[i] = sqrt(r[i]);
    }

    /* calculate central force */
    for(l=0;l<Ndim;l++)
    {
      for(i=0;i<Nbody;i++)
      {
        f[l][i] += - force(G*mass[i]*M_central,pos[l][i],r[i]);
	    }
	  }

    /* calculate pairwise separation of particles */
    for(l=0;l<Ndim;l++)
    {
      k = 0;
      for(i=0;i<Nbody;i++)
      {
        double pos_value = pos[l][i];
        for(j=i+1;j<Nbody;j++)
        {
          delta_pos[l][k] = pos_value - pos[l][j];
          k = k + 1;
        }
      }
    }

    /* calculate norm of separation vector */
    for(i=0;i<Npair;i++)
    {
      delta_r[i] = 0.0;

      for(k=0;k<Ndim;k++)
      {
        delta_r[i] += (delta_pos[k][i] * delta_pos[k][i]); // or pow(delta_pos[k][i], 2)
      }

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

        if( delta_r[k] >= Size )
        {
          for(l=0;l<Ndim;l++)
          {
            double force_val = force(G*mass[i]*mass[j],delta_pos[l][k],delta_r[k]);
            /*  flip force if close in */
            f[l][i] += - force_val;
            f[l][j] += force_val;
          }
        }
        else
        {
          for(l=0;l<Ndim;l++)
          {
            double force_val = force(G*mass[i]*mass[j],delta_pos[l][k],delta_r[k]);
            /*  flip force if close in */
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

    for(i=0;i<Ndim;i++)
    {
      for(j=0;j<Nbody;j++)
      {
        /* update positions */
        pos[i][j] += dt * velo[i][j];
        /* update velocities */
        velo[i][j] += dt * (f[i][j]/mass[j]);
      }
    }

  }

}
