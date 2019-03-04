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
#define padding 64
#define B 64

DEF double vis[Nbody + padding], mass[Nbody + padding];
DEF double pos[Ndim][Nbody + padding];
DEF double delta_r[Npair + padding];
DEF double velo[Ndim][Nbody + padding];
DEF double r[Nbody + padding];
DEF double f[Ndim][Nbody + padding];
DEF double wind[Ndim + padding];
DEF double radius[Nbody + padding];
DEF double delta_pos[Ndim][Npair + padding];
DEF unsigned int collisions;


#define G 2.0
#define M_central 1000.0
#define M_central_x_G (M_central*G)

void evolve (int Nstep, double dt);

#endif
