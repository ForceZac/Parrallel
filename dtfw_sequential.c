#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define PI2 6.28318530718
#define R_ERROR 0.01

/* Function declarations */
int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N);
int fillInput(double* xr, double* xi, int N);
int setOutputZero(double* Xr_o, double* Xi_o, int N);
int checkResults(double* xr, double* xi, double* xr_check, double* xi_check, double* Xr_o, double* Xi_r, int N);

int main(int argc, char* argv[]){
  if (argc != 2) {
    printf("Usage: dftw__sequential [size_of_input_array]\n");
  }

  int N = atoi(argv[1]); /* size of input array*/

  // Allocate array for input vector
  double* xr = (double*) malloc (N *sizeof(double));
  double* xi = (double*) malloc (N *sizeof(double));
  fillInput(xr,xi,N);

  // for checking purposes
  double* xr_check = (double*) malloc (N *sizeof(double));
  double* xi_check = (double*) malloc (N *sizeof(double));
  setOutputZero(xr_check,xi_check,N);

  // Allocate array for output vector
  double* Xr_o = (double*) malloc (N *sizeof(double));
  double* Xi_o = (double*) malloc (N *sizeof(double));
  setOutputZero(Xr_o,Xi_o,N);

  // DFT
  int idft = 1;
  DFT(idft,xr,xi,Xr_o,Xi_o,N);
  // IDFT
  idft = -1;
  DFT(idft,Xr_o,Xi_o,xr_check,xi_check,N);

  // check the results: easy to make correctness errors with openMP
  checkResults(xr,xi,xr_check,xi_check,Xr_o, Xi_o, N);

  // take out the garbage
  free(xr);
  free(xi);
  free(Xi_o);
  free(Xr_o);
  free(xr_check);
  free(xi_check);
  return 0;
}

// DFT/IDFT routine
// idft: 1 direct DFT, -1 inverse IDFT (Inverse DFT)
int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N) {
  int k, n;
  for (k = 0; k < N; k++) {
    for (n = 0; n < N; n++) {
      // Real part of X[k]
      Xr_o[k] += xr[n] * cos(n * k * PI2 / N) + idft*xi[n]*sin(n * k * PI2 / N);
      // Imaginary part of X[k]
      Xi_o[k] += -idft*xr[n] * sin(n * k * PI2 / N) + xi[n] * cos(n * k * PI2 / N);
    }
  }

  // normalize if you are doing IDFT
  if (idft == -1){
    for (n = 0; n < N; n++) {
      Xr_o[n] /=N;
      Xi_o[n] /=N;
    }
  }
  return 0;
}

/**
 * Do not parallelize this function, as rand() does
 * not behave properly when threaded.
 **/
int fillInput(double* xr, double* xi, int N) {
  int n;
  srand(1871);
  for(n = 0; n < N; n++) {
    // Generate random discrete-time signal x in range (-1,+1)
    xr[n] = ((double)(2.0 * rand()) / RAND_MAX) - 1.0;
    xi[n] = ((double)(2.0 * rand()) / RAND_MAX) - 1.0;
  }
  return 0;
}

// set to zero the output vector
int setOutputZero(double* Xr_o, double* Xi_o, int N){
  int n;
  for(n = 0; n < N; n++){
    Xr_o[n] = 0.0;
    Xi_o[n] = 0.0;
  }
  return 0;
}

// check if x = IDFT(DFT(x))
int checkResults(double* xr, double* xi, double* xr_check, double* xi_check, double* Xr_o, double* Xi_r, int N){
  int err_count = 0;
  int n;
  for(n = 0; n < N; n++) {
    if ((fabs(xr[n] - xr_check[n]) > R_ERROR) || (fabs(xi[n] - xi_check[n]) > R_ERROR)) {
      err_count += 1;
    }
  }
  if (err_count != 0) {
    printf("Errors exist!\n");
  } else {
    printf("No errors!\n");
    printf("Xre[0] = %f\n",Xr_o[0]);
  }
  return 0;
}
