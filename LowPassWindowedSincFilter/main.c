// THIS CODE IS BROKEN AND FOR LOGISTICAL/PERSONAL REASONS,
// WILL NOT BE FIXED


// TOMORROWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

// I HAD A LONG DAY

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SIG_LENGTH 320
#define KERNEL_LENGTH 29

extern double InputSignal_f32_1kHz_15kHz[320];
double outputSignal[SIG_LENGTH - KERNEL_LENGTH];
double outputKernel[KERNEL_LENGTH];

void lowPassWindowSincFilter(double *sig_src_arr,
                            double *sig_dest_arr,
                            double *fltr_kernel_dest,
                            double cutoffFreq,
                            int filterLength,
                            int inputSigLength);

// compile: compile: gcc main.c waveforms.c -o lpwsf -lm

/*

Cutoff frequency is normalized. Must be between
0 and 0.5, where 0.5 represents the Nyquist frequency

*/

int main() {

    FILE *fptr1, *fptr2, *fptr3;
    lowPassWindowSincFilter((double *) InputSignal_f32_1kHz_15kHz,
                            (double *) outputSignal,
                            (double *) outputKernel,
                            (double) 0.2,
                            (int) KERNEL_LENGTH,
                            (int) SIG_LENGTH);
    fptr1 = fopen("output_signal.dat", "w");
    fptr2 = fopen("input_signal.dat", "w");
    fptr3 = fopen("output_kernel.dat", "w");

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(fptr2, "\n%lf", InputSignal_f32_1kHz_15kHz[i]);
        if (i > KERNEL_LENGTH) {
            fprintf(fptr1, "\n%lf", outputSignal[i]);
        }
        if (i < KERNEL_LENGTH) {
            fprintf(fptr3, "\n%lf", outputKernel[i]);
        }
        
    }

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);

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


for (int i = 0; i < filterLength; i++) {
    if ((i - filterLength - 1) / 2 == 0) {
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
        sig_dest_arr[j] += sig_src_arr[j - i] * fltr_kernel_dest[i];
    }
}

}