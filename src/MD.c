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
  unsigned int step;
  int i, ii, j, jj, k, l;
  double size;
  double tmp_val, tmp_val2, tmp_val3;
  /*
   * Loop over timesteps.
  */
  // count=1;
  for(step = 1;step<=count;++step)
  {
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);

    /* calculate distance from central mass */
    for(i=0;i<Nbody;++i)
    {
      tmp_val = 0.0;
      for(k=0;k<Ndim;++k)
      {
        tmp_val += pow(pos[k][i], 2);
      }
      r[i] = sqrt(tmp_val);
    }


    for(j=0;j<Ndim;++j){
      visc_force(Nbody,f[j],vis,velo[j]);
      wind_force(Nbody,f[j],vis,wind[j]);
    }

    /* calculate central force */
    for(i=0;i<Ndim;++i)
    {
      for(j=0;j<Nbody;++j)
      {
        f[i][j] -= force(M_central_x_G*mass[j], pos[i][j], r[j]);
	    }
	  }

    /* calculate pairwise separation of particles */
    for(l=0;l<Ndim;++l)
    {
      k = 0;
      for(i=0;i<Nbody;++i)
      {
        tmp_val = pos[l][i];
        for(j=i+1;j<Nbody;++j)
        {
          // pos[l][j] += tmp_val;
          delta_pos[l][k] = tmp_val - pos[l][j];
          k = k + 1;
        }
      }
    }

// printf("%d\n", k);
// 8386560 
// 4*1024=4096



// 2048*4096 = 8386560

              // 8388608
// 4096 * ( 4096-1  + ... + 0 ) = 4096 * 8392704

          // printf("%d , %d \n", k, Npair);
// k max = 34376515584

// Nobody - 1  +   Nobody - 2  + ... +  Nbody - Nobody =
// Nbody * Nbody - (1 + ... + Nobody) =
// Nbody * Nbody - (Nbody+1)*(Nbody/2) =
// 4096 * 4096 - (4096+1)*(2048) =
// 8386560

    // for(l=0;l<Ndim;l++)
    // {
    //   for (k=0;k<8386560;k++)
    //   {
    //     // i = k/Nbody;
    //     i = k >> 12;
    //     j = k - (i << 12);
    //     delta_pos[l][k] = pos[l][i] - pos[l][j];
    //     // printf("%d, %d, %d, %d\n", Nbody, k, i, j);
    //   }
    // }

    // for(l=0;l<Ndim;++l)
    // {
    //   k = 0;
    //   for(i=0;i<Nbody;++i)
    //   {
    //     tmp_val = pos[l][i];
    //     for(j=i+1;j<Nbody;++j)
    //     {
    //       delta_pos[l][k] = tmp_val;
    //       k = k + 1;
    //     }
    //   }
    // }

    // for(l=0;l<Ndim;++l)
    // {
    //   k = 0;
    //   for(i=0;i<Nbody;++i)
    //   {
    //     for(j=i+1;j<Nbody;++j)
    //     {
    //       delta_pos[l][k] -= pos[l][j];
    //       k = k + 1;
    //     }
    //   }
    // }

    /* calculate norm of separation vector */
    for(i=Npair-1;i>=0;--i)
    {
      tmp_val = 0.0;
      for(k=0;k<Ndim;++k)
      {
        tmp_val += pow(delta_pos[k][i], 2);
      }
      delta_r[i] = sqrt(tmp_val);
    }

    /*
     * add pairwise forces.
    */

    k = 0;
    for(i=0;i<Nbody;++i)
    {
        for(j=i+1;j<Nbody;++j)
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
                f[l][i] -= tmp_val;
              }
            }
            else
            {
              for(l=0;l<Ndim;l++)
              {
                tmp_val = force(tmp_val2, delta_pos[l][k], tmp_val3);

                /*  flip force if close in */
                f[l][j] -= tmp_val;
                f[l][i] += tmp_val;
              }
              collisions++;
            }
            k = k + 1;
        }
      }

    for(i=Ndim-1;i>=0;--i)
    {
      for(j=Nbody-1;j>=0;--j)
      {
        /* update positions */
        pos[i][j] += dt * velo[i][j];
        /* update velocities */
        velo[i][j] += dt * (f[i][j]/mass[j]);
      }
    }

  }

}
