#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void lowPassWindowSincFilter(double *sig_src_arr,
                            double *sig_dest_arr,
                            double *fltr_kernel_dest,
                            double cutoffFreq,
                            int filterLength,
                            int inputSigLength);

/*

Cutoff frequency is normalized. Must be between
0 and 0.5, where 0.5 represents the Nyquist frequency

*/

int main() {

    return 0;
}

void lowPassWindowSincFilter(double *sig_src_arr,
                            double *sig_dest_arr,
                            double *fltr_kernel_dest,
                            double cutoffFreq,
                            int filterLength,
                            int inputSigLength)
{

// Calculate low pass filter kernel

double M_PI = 3.14159265358979f;

for (int i = 0; i < filterLength; i++) {
    if ((i - filterLength) / 2 == 0) {
        fltr_kernel_dest[i] = 2 * M_PI * cutoffFreq;
    }
    else {
        fltr_kernel_dest[i] = sin(2 * M_PI * cutoffFreq * (i - filterLength / 2)) / (i - filterLength / 2);
        fltr_kernel_dest[i] *= (0.54 - 0.46*cos(2 * M_PI * i / filterLength));
    }
}

for (int j = filterLength; j < inputSigLength; j++) {
    sig_dest_arr[j] = 0;
    for (int i = 0; i < filterLength; i++) {
        sig_dest_arr[j] += sig_src_arr[j - 1] * fltr_kernel_dest[i];
    }
}

}