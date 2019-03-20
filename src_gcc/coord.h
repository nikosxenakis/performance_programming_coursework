/*
 * This file defines static arrays that contains the primary coordinates
 * of the particles,
 *
 *  Nbody	Number of particles
 *  Npair	Number of particle pairs
 *  pos		Position of the particles
 *  r           distance of partice from central mass 
 * vel		velocity of the particles
 *  f		Forces acting on each particle
 *  visc		viscosity coefficient for each particle
 *  mass		mass of each particle
 *  delta_pos	seperation vector for each particle pair
 *  delta_r		seperation for each particle pair
 */
#ifndef COORD
#define COORD

#ifdef DECL
#define DEF
#else
#define DEF extern
#endif

#define Nbody (4*1024)
#define  Npair ((Nbody*(Nbody-1))/2)
#define Ndim_mul_Nbody (Ndim*Nbody)

enum
{ Xcoord = 0, Ycoord, Zcoord, Ndim };

// cache line size
#define CACHE_LINE_SIZE 64

#define PADDING (CACHE_LINE_SIZE - Ndim*sizeof(double)) / sizeof(double)

#define G 2.0
#define M_central 1000.0
#define M_central_x_G (M_central*G)

DEF unsigned int collisions;

void evolve (int Nstep, double dt, double f[][Ndim] , double pos[][Ndim] , const double *vis, \
  double velo[][Ndim] , double *mass, const double *radius, const double *wind);

#endif
