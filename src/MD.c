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
  // int collided;
  double size;
  double tmp_val, tmp_val2, tmp_val3;

  // printf("vis: first: %p , last: %p, next: %p\n", &vis[0], &vis[Nbody-1], &vis[Nbody-1]+1);
  // printf("mass: first: %p , last: %p, next: %p\n", &mass[0], &mass[Nbody-1], &mass[Nbody-1]+1);
  // printf("pos: first: %p , last: %p, next: %p\n", &pos[0], &pos[Ndim-1][Nbody-1], &pos[Ndim-1][Nbody-1]+1);
  // printf("delta_r: first: %p , last: %p, next: %p\n", &delta_r[0], &delta_r[Nbody_power2-1], &delta_r[Nbody_power2-1]+1);
  // printf("velo: first: %p , last: %p, next: %p\n", &velo[0], &velo[Ndim-1][Nbody-1], &velo[Ndim-1][Nbody-1]+1);
  // printf("r: first: %p , last: %p, next: %p\n", &r[0], &r[Nbody-1], &r[Nbody-1]+1);
  // printf("f: first: %p , last: %p, next: %p\n", &f[0], &f[Ndim-1][Nbody-1], &f[Ndim-1][Nbody-1]+1);
  // printf("wind: first: %p , last: %p, next: %p\n", &wind[0], &wind[Ndim-1], &wind[Ndim-1]+1);
  // printf("radius: first: %p , last: %p, next: %p\n", &radius[0], &radius[Nbody-1], &radius[Nbody-1]+1);
  // printf("delta_pos: first: %p , last: %p, next: %p\n", &delta_pos[0], &delta_pos[Nbody-1][Nbody_power2-1], &delta_pos[Nbody-1][Nbody_power2-1]+1);

  /*
   * Loop over timesteps.
  */
  for(step = 1;step<=count;step++)
  {
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);

    /* calculate distance from central mass */
    for(i=0;i<Nbody;i++)
    {
      tmp_val = 0.0;

      for(k=0;k<Ndim;k++)
      {
        tmp_val += (pos[k][i] * pos[k][i]); // or pow(pos[k][i], 2)
      }

      r[i] = sqrt(tmp_val);

    }

    for(i=Ndim-1;i>=0;i--)
    {
      tmp_val = wind[i];
      for(j=Nbody-1;j>=0;j--)
      {
         // set the viscosity term in the force calculation 
        /* add the wind term in the force calculation */
        f[i][j] = - vis[j] * (velo[i][j] + tmp_val);
      }
    }

    /* calculate central force */
    for(i=0;i<Ndim;i++)
    {
      for(j=0;j<Nbody;j++)
      {
        f[i][j] -= force(M_central_x_G*mass[j],pos[i][j],r[j]);
	    }
	  }

    /* calculate pairwise separation of particles */
    for(l=0;l<Ndim;l++)
    {
      k = 0;
      for(i=0;i<Nbody;i++)
      {
        tmp_val = pos[l][i];
        for(j=i+1;j<Nbody;j++)
        {
          delta_pos[l][k] = tmp_val - pos[l][j];
          k = k + 1;
        }
      }
    }
    // for(l=Ndim-1;l>=0;l--)
    // {
    //   k = 0;
    //   for(i=Nbody-1;i>=0;i--)
    //   {
    //     tmp_val = pos[l][i];
    //     for(j=Nbody-1;j>=i+1;j--)
    //     {
    //       delta_pos[l][k] = tmp_val - pos[l][j];
    //       k = k + 1;
    //     }
    //   }
    // }

    /* calculate norm of separation vector */
    for(i=Npair-1;i>=0;i--)
    // for(i=0;i<Npair;i++)
    {
      tmp_val = 0.0;

      for(k=0;k<Ndim;k++)
      {
        tmp_val += (delta_pos[k][i] * delta_pos[k][i]); // or pow(delta_pos[k][i], 2)
      }

      delta_r[i] = sqrt(tmp_val);
    }

    /*
     * add pairwise forces.
    */
    k = 0;
    for(i=0;i<Nbody;i++)
    {
      for(j=i+1;j<Nbody;j++)
      {
        size = radius[i] + radius[j];
        tmp_val2 = G*mass[i]*mass[j];
        tmp_val3 = delta_r[k];

        if( tmp_val3 >= size )
        {
          for(l=0;l<Ndim;l++)
          {
            tmp_val = force(tmp_val2, delta_pos[l][k], tmp_val3);
            /*  flip force if close in */
            f[l][j] += tmp_val;
            f[l][i] += - tmp_val;
          }
        }
        else
        {
          // collided=0;

          for(l=0;l<Ndim;l++)
          {
            tmp_val = force(tmp_val2, delta_pos[l][k], tmp_val3);
            /*  flip force if close in */
            f[l][j] += - tmp_val;
            f[l][i] += tmp_val;
            // collided=1;
          }

          // if( collided == 1 )
          // {
            collisions++;
          // }
        }

        k = k + 1;
      }
    }

    for(i=Ndim-1;i>=0;i--)
    {
      for(j=Nbody-1;j>=0;j--)
      {
        /* update positions */
        pos[i][j] += dt * velo[i][j];
        /* update velocities */
        velo[i][j] += dt * (f[i][j]/mass[j]);
      }
    }

  }

}
