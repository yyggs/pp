#!/bin/sh

#SBATCH --nodes=1
#SBATCH --time=00:20:0
#SBATCH --partition=standard
#SBATCH --qos=short
#SBATCH --exclusive
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --account=m23oc-s2484724

module load oneapi
module load compiler
module load intel-20.4/compilers
# module load intel-20.4/vtune
# Run the parallel program
./MD

#vtune -collect=uarch-exploration -r vtune_results ./MD


