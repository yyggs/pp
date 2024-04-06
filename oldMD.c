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

    
  // calculate distance from central mass 
  for (i = 0; i < Nbody; ++i)
  {
    r[i] = 0;
    r[i] += (pos[i][0] * pos[i][0] + pos[i][1] * pos[i][1] + pos[i][2] * pos[i][2]);
    r[i] = sqrt(r[i]);
  }

  // calculate central force
  for (i = 0; i < Nbody; ++i)
  {
    f[i][0] = -vis[i] * velo[i][0] - vis[i] * wind[0] - G * mass[i] * M_central * pos[i][0] / (r[i] * r[i] * r[i]);
    f[i][1] = -vis[i] * velo[i][1] - vis[i] * wind[1] - G * mass[i] * M_central * pos[i][1] / (r[i] * r[i] * r[i]);
    f[i][2] = -vis[i] * velo[i][2] - vis[i] * wind[2] - G * mass[i] * M_central * pos[i][2] / (r[i] * r[i] * r[i]);
  }

  /* calculate pairwise separation of the particles */
  /* calculate norm of separation vector */

  k = 0;
  for(i=0;i<Nbody;i++){
    for(j=i+1;j<Nbody;j++){
      delta_pos[k][0] = pos[i][0] - pos[j][0];
      delta_pos[k][1] = pos[i][1] - pos[j][1];
      delta_pos[k][2] = pos[i][2] - pos[j][2];
      delta_r[k] = 0;
      delta_r[k] += (delta_pos[k][0] * delta_pos[k][0] + delta_pos[k][1] * delta_pos[k][1] + delta_pos[k][2] * delta_pos[k][2]);
      delta_r[k] = sqrt(delta_r[k]);
      ++k;
    }
  }


/*
 * add pairwise forces.
 */
  k = 0;
  for (i = 0; i < Nbody; ++i) {
    for (j = i + 1; j < Nbody; ++j) {
        size = radius[i] + radius[j];
        have_collided = 0;

        double force_x = G * mass[i] * mass[j] * delta_pos[k][0] / (delta_r[k] * delta_r[k] * delta_r[k]);
        double force_y = G * mass[i] * mass[j] * delta_pos[k][1] / (delta_r[k] * delta_r[k] * delta_r[k]);
        double force_z = G * mass[i] * mass[j] * delta_pos[k][2] / (delta_r[k] * delta_r[k] * delta_r[k]);
        
        int sign = 2*(delta_r[k] < size) - 1;
        
        f[i][0] += force_x * sign;
        f[i][1] += force_y * sign;
        f[i][2] += force_z * sign;
        f[j][0] -= force_x * sign;
        f[j][1] -= force_y * sign;
        f[j][2] -= force_z * sign;
        
        have_collided |= (delta_r[k] < size);

        collisions += have_collided;
        k++;
    }
}


    for (i = 0; i < Nbody; ++i)
    {
      pos[i][0] = pos[i][0] + dt * velo[i][0];
      pos[i][1] = pos[i][1] + dt * velo[i][1];
      pos[i][2] = pos[i][2] + dt * velo[i][2];
      velo[i][0] = velo[i][0] + dt * (f[i][0] / mass[i]);
      velo[i][1] = velo[i][1] + dt * (f[i][1] / mass[i]);
      velo[i][2] = velo[i][2] + dt * (f[i][2] / mass[i]);
    }
  }
}