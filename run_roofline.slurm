#!/bin/bash

# Slurm job options (name, compute nodes, job time)
#SBATCH --job-name=roofline
#SBATCH --time=0:40:0
#SBATCH --exclusive
#SBATCH --nodes=1
#SBATCH --tasks-per-node=36
#SBATCH --cpus-per-task=1

# Replace [budget code] below with your budget code (e.g. t01)
#SBATCH --account=m23oc-s2484724
# We use the "standard" partition as we are running on CPU nodes
#SBATCH --partition=standard
# We use the "standard" QoS as our runtime is less than 4 days
#SBATCH --qos=standard

module load intel-20.4/compilers
module load intel-20.4/vtune
module load intel-20.4/advisor

# Change to the submission directory
cd $SLURM_SUBMIT_DIR

# Set the number of threads to 1
#   This prevents any threaded system libraries from automatically
#   using threading.
export OMP_NUM_THREADS=1
mkdir -p opt_results
advixe-cl -collect survey -project-dir opt_results -- ./MD
advixe-cl -collect tripcounts -flop -project-dir opt_results -- ./MD
advixe-cl -collect roofline -project-dir opt_results -- ./MD

mkdir -p orig_results
advixe-cl -collect survey -project-dir orig_results -- ./MD
advixe-cl -collect tripcounts -flop -project-dir orig_results -- ./MD
advixe-cl -collect roofline -project-dir orig_results -- ./MD
