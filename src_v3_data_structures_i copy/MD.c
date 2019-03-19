/*
 *  Simple molecular dynamics code.
 *
 */
#include <stdio.h>
#include <math.h>
#include "coord.h"

void vis_force (int N, double *f, double *vis, double *vel);
void add_norm (int N, double *r, double *delta);
double force (double W, double delta, double r);
void wind_force (int N, double *f, double *vis, double *vel);

void
evolve (int count, double dt, double pos[][Ndim], double velo[][Ndim],
	double f[][Ndim], double *restrict vis, double *restrict radius,
	double *restrict mass, double delta_pos[][Ndim], double *restrict r,
	double *restrict delta_r, double *restrict wind)
{
  int step;
  int i, j, k, l;
  int collided;
  double Size;
	
	/*
	* Loop over timesteps.
	*/
  // count = 1;
	for (step = 1; step <= count; step++)
	{
		printf ("timestep %d\n", step);
		printf ("collisions %d\n", collisions);

		// /* set the viscosity term in the force calculation */
		// for (i = 0; i < Nbody; i++)
		// {
		// 	visc_force (Ndim, f[i], vis, velo[i]);
		// }

		// /* add the wind term in the force calculation */
		// for (i = 0; i < Nbody; i++)
		// {
		// 	wind_force (Ndim, f[i], vis, wind);
		// }
		for(i=0; i<Nbody; ++i) {
		  for(l=0; l<Ndim; l++) {
		    f[i][l] = - vis[i] * (velo[i][l] + wind[l]);
		  }
		}




		/* calculate distance from central mass */
		// for (i = 0; i < Nbody; i++)
		// {
		// 	r[i] = 0.0;
		// }
		// for (i = 0; i < Nbody; i++)
		// {
		// 	add_norm (Ndim, &r[i], pos[i]);
		// }
		// for (i = 0; i < Nbody; i++)
		// {
		// 	r[i] = sqrt (r[i]);
		// }
		for(i=0; i<Nbody; ++i) {
		  r[i] = 0.0;
		  for(l=0; l<Ndim; l++)
		    r[i] += pow(pos[i][l], 2);
		  r[i] = sqrt(r[i]);
		}

		/* calculate central force */
		for (i = 0; i < Nbody; i++)
		{
			for (l = 0; l < Ndim; l++)
			{
				f[i][l] -= force (G * mass[i] * M_central, pos[i][l], r[i]);
			}
		}




		/* calculate pairwise separation of particles */
		k = 0;
		for (i = 0; i < Nbody; i++)
		{
			for (j = i + 1; j < Nbody; j++)
			{
				for (l = 0; l < Ndim; l++)
				{
					delta_pos[k][l] = pos[i][l] - pos[j][l];
				}
				k = k + 1;
			}
		}

		/* calculate norm of separation vector */
		// for (i = 0; i < Npair; i++)
		// {
		// 	delta_r[i] = 0.0;
		// }
		// for (i = 0; i < Npair; i++)
		// {
		// 	add_norm (Ndim, &delta_r[i], delta_pos[i]);
		// }
		// for (i = 0; i < Npair; i++)
		// {
		// 	delta_r[i] = sqrt (delta_r[i]);
		// }
		for(i=0; i<Npair; ++i) {
		  delta_r[i] = 0.0;
		  for(l=0; l<Ndim; l++)
		    delta_r[i] += pow(delta_pos[i][l], 2);
		  delta_r[i] = sqrt(delta_r[i]);
		}

		/*
		* add pairwise forces.
		*/
		k = 0;
		for (i = 0; i < Nbody; i++)
		{
			for (j = i + 1; j < Nbody; j++)
			{
				Size = radius[i] + radius[j];
				collided = 0;
				for (l = 0; l < Ndim; l++)
				{
					/*  flip force if close in */
					if (delta_r[k] >= Size)
					{
						f[i][l] -= force (G * mass[i] * mass[j], delta_pos[k][l], delta_r[k]);
						f[j][l] += force (G * mass[i] * mass[j], delta_pos[k][l], delta_r[k]);
					}
					else
					{
						f[i][l] += force (G * mass[i] * mass[j], delta_pos[k][l], delta_r[k]);
						f[j][l] -= force (G * mass[i] * mass[j], delta_pos[k][l], delta_r[k]);
						collided = 1;
					}
				}
				if (collided == 1)
				{
					collisions++;
				}
				k = k + 1;
			}
		}

		/* update positions */
		for (i = 0; i < Nbody; i++)
		{
			for (j = 0; j < Ndim; j++)
			{
				pos[i][j] += dt * velo[i][j];
			}
		}

		/* update velocities */
		for (i = 0; i < Nbody; i++)
		{
			for (j = 0; j < Ndim; j++)
			{
				velo[i][j] += dt * (f[i][j] / mass[i]);
			}
		}
    }
}
