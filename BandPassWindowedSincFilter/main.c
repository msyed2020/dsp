#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define SIG_LENGTH  320
#define KERNEL_LENGTH   29

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

}