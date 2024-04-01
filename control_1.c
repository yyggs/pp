/*
 *
 * 控制分子动力学更新的程序
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
    /* 时间步长值 */
    double dt=0.02;

    /* 要使用的时间步数 */
    int Nstep=100;
    int Nsave=5;
  
    if( argc > 1 ){
        Nstep=atoi(argv[1]);
    }
    wind[Xcoord] = 0.9;
    wind[Ycoord] = 0.4;
    wind[Zcoord] = 0.0;
    /* 设置多维数组 */
    r = calloc(Nbody,sizeof(double));
    delta_r = calloc(Nbody*Nbody,sizeof(double));
    mass = calloc(Nbody,sizeof(double));
    radius = calloc(Nbody,sizeof(double));
    vis = calloc(Nbody,sizeof(double));
    f[0] = calloc(Ndim*Nbody,sizeof(double));
    pos[0] = calloc(Ndim*Nbody,sizeof(double));
    velo[0] = calloc(Ndim*Nbody,sizeof(double));
    delta_pos[0] = calloc(Ndim*Nbody*Nbody,sizeof(double));
    for(i=1;i<Ndim;i++){
        f[i] = f[0] + i * Nbody;
        pos[i] = pos[0] + i * Nbody;
        velo[i] = velo[0] + i * Nbody;
        delta_pos[i] = delta_pos[0] + i*Nbody*Nbody;
    }

    /* 从文件中读取初始数据 */
    collisions=0;
    in = fopen("input.dat","r");

    if( ! in ){
        perror("input.dat");
        exit(1);
    }

    for(i=0;i<Nbody;i++){
        fscanf(in,"%16le%16le%16le%16le%16le%16le%16le%16le%16le\n",
            mass+i,radius+i,vis+i,
            &pos[Xcoord][i], &pos[Ycoord][i], &pos[Zcoord][i],
            &velo[Xcoord][i], &velo[Ycoord][i], &velo[Zcoord][i]);
    }
    fclose(in);

    /*
    * 运行 Nstep 个时间步，并计算所需时间
    */
 
    tstart=second();
    for(j=1;j<=Nsave;j++){
        start=second();
        evolve(Nstep,dt); 
        stop=second();
        printf("%d 个时间步长花费了 %f 秒\n",Nstep,stop-start);
        printf("碰撞次数 %d\n",collisions);
        fflush(stdout);
        /* 将最终结果写入文件 */
        sprintf(name,"output.dat%03d",j*Nstep);
        out = fopen(name,"w");

        if( ! out ){
            perror(name);
            exit(1);
        }

        for(i=0;i<Nbody;i++){
            fprintf(out,"%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E\n",
                mass[i],radius[i],vis[i],
                pos[Xcoord][i], pos[Ycoord][i], pos[Zcoord][i],
                velo[Xcoord][i], velo[Ycoord][i], velo[Zcoord][i]);
        }
        fclose(out);
    }
    tstop=second();
    printf("%d 个时间步长花费了 %f 秒\n",Nsave*Nstep,tstop-tstart);
}

double second()
{
    struct timeval tp;
    struct timezone tzp;
    int i;

    i = gettimeofday(&tp,&tzp);
    return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
