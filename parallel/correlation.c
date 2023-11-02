#include <upc_relaxed.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


#define N 2800
#define M 2800

#include "correlation.h"

//shared[N * N / THREADS] int data[N][N];

shared[] double (* data);
shared[] double (* corr);
shared[] double (* mean);
shared[] double (* stddev);

int main(int argc, char **argv){
	
	//data = upc_global_alloc(THREADS, (N * N / THREADS) * upc_elemsizeof( * data));
    //corr = upc_all_alloc(THREADS, (N * N / THREADS) * upc_elemsizeof( * corr));
    //mean = upc_all_alloc(THREADS, (N / THREADS) * upc_elemsizeof( * mean));
    //stddev = upc_all_alloc(THREADS, (N / THREADS) * upc_elemsizeof( * stddev));
	//int a = N * N / THREADS;
	
	//printf("valor %i", a);
	
	int i, j;

  	//double * float_n = N;

  	for (i = 0; i < N; i++)
    	for (j = 0; j < N; j++)
      		data[i * N + j] = i * j / N + i;
    

	// Kernel   		  		
    i = 0;
	j = 0;
	int k;

 	double eps = SCALAR_VAL(0.1);


	#pragma scop
	upc_forall (j = 0; j < N; j++; j){
      mean[j] = SCALAR_VAL(0.0);
      for (i = 0; i < N; i++){
	  	mean[j] += data[i * N + j];
      	mean[j] /= N;
  		}
	}
    
	upc_forall (j = 0; j < N; j++; j){
      stddev[j] = SCALAR_VAL(0.0);
      for (i = 0; i < N; i++)
        stddev[j] += (data[i * N + j] - mean[j]) * (data[i * N + j] - mean[j]);
      	stddev[j] /= N;
      	stddev[j] = SQRT_FUN(stddev[j]);
      	stddev[j] = stddev[j] <= eps ? SCALAR_VAL(1.0) : stddev[j];
    }
	
	upc_forall (i = 0; i < N; i++; i)
    	for (j = 0; j < N; j++){
        	data[i * N + j] -= mean[j];
        	data[i * N + j] /= SQRT_FUN(N) * stddev[j];
    }
	
  upc_forall (i = 0; i < N-1; i++; i) {
      corr[i * N + i] = SCALAR_VAL(1.0);
      for (j = i+1; j < N; j++){
          corr[i * N + j] = SCALAR_VAL(0.0);
          for (k = 0; k < N; k++)
            corr[i * N + j] += (data[k * N + i] * data[k * N + j]);
          	corr[j * N + i] = corr[i * N + j];
        }
    }
  corr[(N-1) * N + (N-1)] = SCALAR_VAL(1.0);
   
}




