/*
 *  Simple molecular dynamics code.
 *  2022
 */
#include <stdio.h>
#include <math.h>
#include "coord.h"


void evolve(int count,double dt){
  int step;
  int i,j,k,l;
  int have_collided;
  double size;

  for(step = 1;step<=count;step++){
    printf("timestep %d\n",step);
    printf("collisions %d\n",collisions);

    // calculate distance and force
    for (i = 0; i < Nbody; ++i) {
      r[i] = 0;
      for (int dim = 0; dim < Ndim; ++dim) {
          r[i] += pos[i][dim] * pos[i][dim];
      }
      r[i] = sqrt(r[i]);
      for (int dim = 0; dim < Ndim; ++dim) {
          f[i][dim] = -vis[i] * velo[i][dim] - vis[i] * wind[dim] - G * mass[i] * M_central * pos[i][dim] / (r[i] * r[i] * r[i]);
      }
    }
    /* calculate pairwise separation of the particles */
    /* calculate norm of separation vector */
    k = 0;
    for (i = 0; i < Nbody; ++i) {
      for (j= i+1 ; j < Nbody; ++j){
        delta_r = 0.0;
        for (l=0;l<Ndim;l++){
          delta_pos[k][l] = pos[i][l] - pos[j][l];
          delta_r += delta_pos[k][l] * delta_pos[k][l];
        }
        delta_r = sqrt(delta_r);
    
  /*
  * add pairwise forces.
  */
        size = radius[i] + radius[j];
        have_collided = 0;

        for(l=0;l<Ndim;l++){
          if(delta_r >= size){
            f[i][l] -= G * mass[i] * mass[j] * delta_pos[k][l] / (delta_r * delta_r * delta_r);
            f[j][l] += G * mass[i] * mass[j] * delta_pos[k][l] / (delta_r * delta_r * delta_r);
          }else{
            f[i][l] += G * mass[i] * mass[j] * delta_pos[k][l] / (delta_r * delta_r * delta_r);
            f[j][l] -= G * mass[i] * mass[j] * delta_pos[k][l] / (delta_r * delta_r * delta_r);
            collisions++;
          }
         }
        if (have_collided == 1)
        {
          collisions++;
        }
        
        k++;
      }

      // update positions and velocities
      for(l=0;l<Ndim;l++){
        pos[i][l] = pos[i][l] + dt * velo[i][l];
        velo[i][l] = velo[i][l] + dt * (f[i][l] / mass[i]);
      }
    }
  }
}