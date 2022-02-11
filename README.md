## Student Name: Zachary Force


# Assignment 2

In this project, you'll enhance two sequential programs, **pi_sequential.c** and **dftw_sequential.c** with OpenMP directives. The resulting source codes are to be named **pi_openmp.c** and **dftw_openmp.c** accordingly. Each should compile successfully when compiled with **-Wall** and **-Werror** flags.

### Task 1: pi_openmp.c:  5 points

- Using only the **#pragma parallel** directive to create a OpenMP implementation of **pi_sequential.c** called **pi_openmp.c**. Chanages to the general programming workflow of **pi_sequential.c** should be minimal. 
- **pi_openmp.c** will have one additional command line argument that represents the number of threads. 
- Result Pi value of **pi_openmp.c** and **pi_sequential.c** should be the same. 

### Task 2: dftw_openmp.c: 5 points

- Using only the **#pragma parallel** directive to create a OpenMP implementation of **dftw_sequential.c** called **dftw_openmp.c**. Chanages to the general programming workflow of **dftw_sequential.c** should be minimal. 
- **dftw_openmp.c** will have one additional command line argument that represents the number of threads. 
- Result error check and initial value of the DFT output array of **dftw_openmp.c** and **dftw_sequential.c** should be the same. 

### Task 3: XSEDE scripting: 10 points

- Create a directory structure on XSEDE that contains **pi_sequential.c**, **pi_openmp.c**, **dftw_sequential.c**, **dftw_openmp.c**, and **asg2.sh**. 
- **asg2.sh** is a SLURM submission script and it should enable the followings:
  - Request a node from XSEDE with 16 cores for one hour. 
  - For **pi** and **dftw**, compile both sequential and openmp versions. 
  - For **pi** and **dftw**, first run the sequential version, then run the openmp version with 1, 2, 4, 8, and 16 threads. 



## Submission

- Edit the README.md to add your name to the top of the file
- Submit the URL of your assignment git repository, as provided through GitHub Classroom to D2L. 
- The assignment git repository should have the four additional required files: **pi_openmp.c**, **dftw_openmp.c**, **asg2.sh**, and the SLURM output file from XSEDE. 
- Besides these four files, you must not make any changes to the existing C files or test script.
- The last commit to your git repository must be made prior to the deadline of the assignment. Any subsequent commit will not be considered. 
