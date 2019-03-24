/*
 *
 * Control program for the MD update
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DECL
#include "coord.h"

double second(void); 
int main(int argc, char *argv[]){
  int i,j;
  FILE *in, *out;
  double tstart,tstop;
  double start,stop;
  char name[80];
  /*  timestep value */
  double dt=0.02;

  /*  number of timesteps to use. */
  int Nstep=100;
  int Nsave=5;
  
  if( argc > 1 ){
    Nstep=atoi(argv[1]);
  }

  double pos[Nbody][Ndim] __attribute__((aligned(64)));
  double velo[Nbody][Ndim] __attribute__((aligned(64)));
  double f[Nbody][Ndim] __attribute__((aligned(64)));
  double vis[Nbody] __attribute__((aligned(64)));
  double radius[Nbody] __attribute__((aligned(64)));
  double mass[Nbody] __attribute__((aligned(64)));
  double wind[Ndim + PADDING] __attribute__((aligned(64))) = {0.9, 0.4, 0.0};

/* read the initial data from a file */

  collisions=0;
  in = fopen("input.dat","r");

  if( ! in ){
    perror("input.dat");
    exit(1);
  }

  for(i=0;i<Nbody;i++){
    fscanf(in,"%16le%16le%16le%16le%16le%16le%16le%16le%16le\n",
      mass+i,radius+i,vis+i,
      &pos[i][Xcoord], &pos[i][Ycoord], &pos[i][Zcoord],
      &velo[i][Xcoord], &velo[i][Ycoord], &velo[i][Zcoord]);
  }
  fclose(in);

/*
 * Run Nstep timesteps and time how long it took
 */
 
   tstart=second();
   for(j=1;j<=Nsave;j++){
      start=second();
      // Nstep = 1;
      evolve(Nstep,dt,pos,velo,f,vis,radius,mass,wind); 
      stop=second();
      printf("%d timesteps took %f seconds\n",Nstep,stop-start);
      printf("collisions %d\n",collisions);

/* write final result to a file */
      sprintf(name,"output.dat%03d",j*Nstep);
      out = fopen(name,"w");

      if( ! out ){
	perror(name);
	exit(1);
      }

      for(i=0;i<Nbody;i++){
	fprintf(out,"%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E\n",
		mass[i],radius[i],vis[i],
		pos[i][Xcoord], pos[i][Ycoord], pos[i][Zcoord],
		velo[i][Xcoord], velo[i][Ycoord], velo[i][Zcoord]);
      }
      fclose(out);
  }
  tstop=second();
  printf("%d timesteps took %f seconds\n",Nsave*Nstep,tstop-tstart);

}

double second()
{
/* struct timeval { long        tv_sec; 
            long        tv_usec;        };

struct timezone { int   tz_minuteswest;
             int        tz_dsttime;      };     */

        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

