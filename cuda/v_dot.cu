#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define DIM_V 1000

__global__ void cu_add(double *d1, double *d2, double *d3, unsigned N) {
	unsigned i = blockDim.x * blockIdx.x + threadIdx.x;
	if (i < N)
		d3[i] = d1[i] + d2[i];
}

__global__ void cu_scl(double scl, double *d1, double *d2, unsigned N) {
	unsigned i = blockDim.x * blockIdx.x + threadIdx.x;
	if (i < N)
		d2[i] = scl * d1[i];
}

__global__ void cu_func(double *d1, double *d2, unsigned N) {
	unsigned i = blockDim.x * blockIdx.x + threadIdx.x;
	if (i < N)
		d2[i] = sin(d1[i])/d1[i];
}

__global__ void cu_razb(double a, double d, double* x, unsigned N) {
	unsigned i = blockDim.x * blockIdx.x + threadIdx.x;
	if (i < N)
		x[i] = a + d * ((double)i + 1./2.);
}

__global__ void cu_sum(double *d_dst, double *d_src, unsigned N, unsigned N_ofElements) {
	unsigned element, destination;
	
	destination = blockDim.x * blockIdx.x + threadIdx.x;
	d_dst[destination] = 0.;

	for (unsigned k = 0; k < N_ofElements; ++k) {
		element = destination * N_ofElements + k;
		if (element < N) {
			d_dst[destination] += d_src[element];
		}
	}
}

double e_sum(double *x, unsigned N) {
	unsigned threadsPerBlock, blocksPerGrid, sizeOfPart, sizeOfSum;
	size_t x_size, sum_size;
	double *d_x, *d_sum;
	double sum;

	sizeOfPart = (unsigned)floor(sqrt((double)N));
	sizeOfSum = (unsigned)ceil( ((double)N) / ((double)sizeOfPart) );
	blocksPerGrid = (unsigned)ceil( ((double)sizeOfSum) / ((double)1024) );
	threadsPerBlock = (sizeOfSum < 1024) ? sizeOfSum : 1024;

	//printf("sizeOfPart = %u\nsizeOfSum = %u\nblocksPerGrid = %u\nthreadsPerBlock = %u\n", sizeOfPart, sizeOfSum, blocksPerGrid, threadsPerBlock);
	x_size = N * sizeof(double);
	sum_size = sizeOfSum * sizeof(double);

	cudaMalloc(&d_x, x_size);
	cudaMalloc(&d_sum, sum_size);

	cudaMemcpy(d_x, x, x_size, cudaMemcpyHostToDevice);
	
	cu_sum<<<blocksPerGrid, threadsPerBlock>>>(d_sum, d_x, N, sizeOfPart);

	cudaFree(d_x);
	cudaMalloc(&d_x, sizeof(double));
	cu_sum<<<1,1>>>(d_x, d_sum, sizeOfSum, sizeOfSum);

	cudaMemcpy(&sum, d_x, sizeof(double), cudaMemcpyDeviceToHost);
	

	cudaFree(d_x);
	/*
	d_x = (double*)malloc(sum_size);
	cudaMemcpy(d_x, d_sum, sum_size, cudaMemcpyDeviceToHost);
	sum = 0.;
	for (unsigned i = 0; i < sizeOfSum; ++i) {
		sum += d_x[i];
	}
	free(d_x);
	*/
	cudaFree(d_sum);

	return sum;
}

double ntgrl(double a, double b, unsigned N) {
	double d, I;
	double *x;
	size_t size;

	d = (b - a)/(double)N;
	size = N * sizeof(double);

	cudaMalloc(&x, size);
	
	unsigned threadsPerBlock = 1024;
	unsigned blocksPerGrid = (N - 1) / threadsPerBlock + 1;

	cu_razb<<<blocksPerGrid, threadsPerBlock>>>(a, d, x, N);
	cu_func<<<blocksPerGrid, threadsPerBlock>>>(x, x, N);
	cu_scl<<<blocksPerGrid, threadsPerBlock>>>(d, x, x, N);
	
	I = e_sum(x, N);
	cudaFree(x);
	return I;
}

int main(void) {
	double I, a, b;
	unsigned N;
	printf("Enter a: "); scanf("%lf", &a);
	printf("Enter b: "); scanf("%lf", &b);
	printf("Enter precision N: "); scanf("%u", &N);
	I = ntgrl(a, b, N);
	printf("Ntgrl = %lf\n", I);
	return 0;
}
