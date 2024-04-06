/*
 *
 * Control program for the MD update
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <memory.h>
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
  wind[0] = 0.9;
  wind[1] = 0.4;
  wind[2] = 0.0;

  /* set up multi dimensional arrays */
  
  memset(pos, 0, sizeof(pos));
  memset(velo, 0, sizeof(velo));
  memset(f, 0, sizeof(f));
  memset(vis, 0, sizeof(vis));
  memset(mass, 0, sizeof(mass));
  memset(radius, 0, sizeof(radius));
  memset(delta_pos, 0, sizeof(delta_pos));
  memset(r, 0, sizeof(r));

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
 * Run Nstep timesteps and time how long it takes
 */
 
   tstart=second();
   for(j=1;j<=Nsave;j++){
      start=second();
      evolve(Nstep,dt); 
      stop=second();
      printf("%d timesteps took %f seconds\n",Nstep,stop-start);
      printf("collisions %d\n",collisions);
      fflush(stdout);
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
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
