// OpenCL kernel for vector addition.
__kernel
void updateWeigth( __global float *a, __global float *b, __global float *c )
{
	// The global id tells us the index of the vector for this thread.
	int i = get_global_id(0);
	int j = get_global_id(1);
	int M = get_global_size(1);

	c[i*M+j] = (a[i] * b[j]) + c[i*M+j];
}