# Compressed Sparse Row or Column (CSR|CSC)

A <b>sparse</b> matrix or sparse array is a matrix in which <b>most of the elements are zero</b>.

## Description

<li>The compressed sparse row (CSR) represents a <b>matrix M by three (one-dimensional) arrays</b>, that respectively contain nonzero values, the extents of rows, and column indices.</li><br>

<li>CSC is similar to CSR except that values are read first by column, a row index is stored for each value, and column pointers are stored.</li>

## Purpose

This repo contents scripts that transform <b>sparse array --> CSC|CSR, DSCC|DCSR and GraphToC2</b>

## How to use ?

Just run <b>matrix_sparse.exe</b> program

```
./matrix_sparse.exe
```
