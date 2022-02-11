#!/bin/bash
#SBATCH -N 1
#SBATCH -p RM
#SBATCH --ntasks-per-node 16
#SBATCH -t 01:00:00

# echo commands to stdout 
set -x
cd ~/Assignment-2-ForceZac


gcc -std=c99 -o dftw_sequential dftw_sequentail.c -lm
./dftw_sequential 1

gcc -std=c99 -o pi_sequential pi_sequential.c -lm
./pi_sequential 1

gcc -std=c99 -o dftw_openmp dftw_openmp.c -fopenmp -lm
./dftw_openmp 1 1

gcc -std=c99 -o pi_openmp pi_openmp.c -fopenmp -lm
./pi_openmp 1 1
