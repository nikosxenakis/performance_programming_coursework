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

#ifdef DECL
#define DEF
#else
#define DEF extern
#endif
#define Nbody 4*1024
#define  Npair ((Nbody*(Nbody-1))/2)
#define G_mul_M_central G*M_central

enum{ Xcoord=0, Ycoord, Zcoord, Ndim };

DEF int collisions;

#define PADDING 64

#define G 2.0
#define M_central 1000.0

void evolve(int Nstep, double dt, double pos[][Ndim], double velo[][Ndim], double f[][Ndim], const double * restrict vis, \
  const double * restrict radius, const double * restrict mass, double * restrict wind) ;
