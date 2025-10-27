#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define SIG_LENGTH  320
#define KERNEL_LENGTH   29

extern double InputSignal_f32_1kHz_15kHz[320];
double outputSignal[SIG_LENGTH - KERNEL_LENGTH];
double outputFilter[KERNEL_LENGTH];
double stateLowerCutoffBuff[KERNEL_LENGTH];
double stateUpperCutoffBuff[KERNEL_LENGTH];

void bandPassWindowedSinc(
                        double *lowerCutoffStateBuff,
                        double *upperCutoffStateBuff,
                        double *filterKernelDestinationArr,
                        double lowerCutoff,
                        double upperCutoff,
                        int filterLength,
                        double *sigSrcArr,
                        double *sigDestArr,
                        int inputSigLength);

int main() {
    

    return 0;
}

void bandPassWindowedSinc(
                        double *lowerCutoffStateBuff,
                        double *upperCutoffStateBuff,
                        double *filterKernelDestinationArr,
                        double lowerCutoff,
                        double upperCutoff,
                        int filterLength,
                        double *sigSrcArr,
                        double *sigDestArr,
                        int inputSigLength)
{
    // Calculating the first low pass filter kernel
    for (int i = 0; i < filterLength; i++) {

        if (i - filterLength / 2 == 0) {
            lowerCutoffStateBuff[i] = 2 * M_PI * lowerCutoff;
        }
        if (i - filterLength / 2 != 0) {
            lowerCutoffStateBuff[i] = sin(2 * M_PI * lowerCutoff * (i - filterLength / 2)) / (i - filterLength / 2);
            lowerCutoffStateBuff[i] *= (0.42 - 0.5*cos(2 * M_PI * i / filterLength) + 0.08*cos(4 * M_PI * i / filterLength));
        }
    }

    // Calculating the second low pass filter kernel

    for (int i = 0; i < filterLength; i++) {
        if (filterLength / 2 == 0) {
            upperCutoffStateBuff[i] = 2 * M_PI * upperCutoff;
        }
        if (filterLength / 2 != 0) {
            upperCutoffStateBuff[i] = sin(2 * M_PI * upperCutoff * (i - filterLength / 2)) / (i - filterLength / 2);
            upperCutoffStateBuff[i] = upperCutoffStateBuff[i] * (0.42 - 0.5 * cos(2 * M_PI * i / filterLength) + 0.08 * cos(4 * M_PI * i / filterLength));
        }
    }

    // Change low pass filter kernel to a high pass filter kernel using Spectral Inversion

    for (int i = 0; i < filterLength; i++) {
        upperCutoffStateBuff[i] = -(upperCutoffStateBuff[i]);
    }
    upperCutoffStateBuff[filterLength / 2] += 1;

    // Add low pass filter kernel to high pass filter kernel to form a band reject filter kernel

    for (int i = 0; i < filterLength; i++) {
        filterKernelDestinationArr[i] = lowerCutoffStateBuff[i] + upperCutoffStateBuff[i];
    }

    // Change band reject filter into bandpass filter using spectral inversion

    for (int i = 0; i < filterLength; i++) {
        filterKernelDestinationArr[i] = -(filterKernelDestinationArr[i]);
    }    
    filterKernelDestinationArr[filterLength / 2] += 1;

    for (int j = filterLength; j < inputSigLength; j++) {
        sigDestArr[j] = 0;
        for (int i = 0; i < filterLength; i++) {
            sigDestArr[j] += sigSrcArr[j - i] * filterKernelDestinationArr[i];
        }
    }
}