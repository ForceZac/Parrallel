#include <math.h>
#include <stdio.h>
#include <stdint.h>  /* for uint64  */
#include <time.h>    /* for clock_gettime */
#include <stdlib.h>
#include <omp.h>

double f(double x) {
  return (6.0/sqrt(1-x*x));
}

double pi = 0.0;

int main(int argc, char *argv[]) {
  uint64_t execTime; /*time in nanoseconds */
  struct timespec tick, tock;
int nthreads=atoi(argv[2]);
double sum=0;

  if (argc != 2) {
    printf("Usage: pi_sequential [number_of_points]\n");
  }

  int numPoints = atoi(argv[1]);
  double step = 0.5/numPoints;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tick);
omp_set_num_threads(nthreads);
  double x = 0.0d;
 int i=0;
#pragma omp parallel default(shared) private(i,x) reduction(+:sum) 
{
#pragma omp for
  for (int i = 0; i < numPoints; i++) {
    x = x + step;  // next x
   sum+= step*f(x);//add to local sum
  }
}
pi= sum;

  clock_gettime(CLOCK_MONOTONIC_RAW, &tock);
  execTime = 1000000000 * (tock.tv_sec - tick.tv_sec) + tock.tv_nsec - tick.tv_nsec;

  printf("elapsed process CPU time = %llu nanoseconds\n", (long long unsigned int) execTime);
  printf("%.20f\n", pi);

  return 0;
}
