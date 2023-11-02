# Correlation-UPC

## Introduction

This project involves an analysis of the __correlation algorithm__ present in the __PolyBench collection__, parallelized using __UPC__, with the aim of analyzing and measuring the difference between the udp, smp, and mpi models. For comparison purposes the sequential algorithm was also implemented.

__In the folder <a href="https://github.com/Dinista/Correlation-UPC/tree/main/Docs">Docs</a> there's a Portuguese article that evaluates the algorithm's execution performance across various models, including udp, smp, and mpi, by a speed-up graph with different inputs__

## How it works

Correlation algorithm calculates the __correlation coefficients__, which are essentially __normalized covariance__, which uses a __matrix__ representation of the correlation coefficient.

### Input

_N×M_ matrix representing _N_ __data points__, each with _M_ attributes.

### Output

_M_ × _M_ matrix where the _i_, _j-th_ element represents the correlation coefficient between _i_ and _j_. The matrix is symmetric.

## How to use

Use Make file to compile and run parellel algorithm:
```bash
make par
# make seq
```
```bash
make run smp
# make run-udp
# make run-mpi
```
