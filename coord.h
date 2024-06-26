/*
 * This file defines static arrays that contains the primary coordinates
 * of the particles,
 *
 *  Nbody 	  Number of particles
 *  Npair	  Number of particle pairs
 *  pos		  Position of the particles
 *  r             Distance of partice from central mass 
 *  vel		  Velocity of the particles
 *  f		  Forces acting on each particle
 *  vis           Viscosity coefficient for each particle
 *  mass	  Mass of each particle
 *  delta_pos     Separation vector for each particle pair
 *  delta_r	  Separation for each particle pair
 */

#ifdef DECL
#define DEF
#else
#define DEF extern
#endif
#define Nbody 4*1024
#define  Npair ((Nbody *(Nbody -1))/2)

enum{ Xcoord=0, Ycoord, Zcoord, Ndim };
      
DEF double pos[Nbody][Ndim];
DEF double velo[Nbody][Ndim];
DEF double f[Nbody][Ndim];
DEF double vis[Nbody];
DEF double mass[Nbody];
DEF double radius[Nbody];
DEF double delta_pos[Npair][3];
DEF double r[Nbody];
DEF double wind[Ndim];
DEF double delta_r;
DEF int collisions;

#define G 2.0
#define M_central 1000.0

void evolve(int Nstep, double dt);
