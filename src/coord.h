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
#define Nbody_power2 Nbody*Nbody
#define Ndim_mul_Nbody Ndim*Nbody

enum{ Xcoord=0, Ycoord, Zcoord, Ndim };

// DEF double *pos[Ndim], *velo[Ndim];
// DEF double *f[Ndim], *vis, *mass, *radius;
// DEF double *delta_pos[3];
// DEF double *r;
// DEF double *delta_r;
// DEF double wind[Ndim];
// DEF int collisions;

// DEF double pos[Ndim][Nbody], velo[Ndim][Nbody];
// DEF double f[Ndim][Nbody], vis[Nbody], mass[Nbody], radius[Nbody];
// DEF double delta_pos[Ndim][Nbody_power2];
// DEF double r[Nbody];
// DEF double delta_r[Nbody_power2];
// DEF double wind[Ndim];
// DEF int collisions;

#define padding 0 // 64

DEF double vis[Nbody], mass[Nbody+padding];
DEF double pos[Ndim][Nbody+padding];
DEF double delta_r[Nbody_power2+padding];
DEF double velo[Ndim][Nbody+padding];
DEF double r[Nbody+padding];
DEF double f[Ndim][Nbody+padding];
DEF double wind[Ndim+padding];
DEF double radius[Nbody+padding];
DEF double delta_pos[Ndim][Nbody_power2+padding];
DEF int collisions;


#define G 2.0
#define M_central 1000.0
#define M_central_x_G M_central*G

void evolve(int Nstep, double dt);
