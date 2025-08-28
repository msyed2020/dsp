// compile: gcc main.c waveforms.c -o idft -lm

// Inverse Discrete Fourier Transform

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double outputReX[SIG_LENGTH / 2];
double outputImX[SIG_LENGTH / 2];
void calcInverseDFT(double *IDFTOutArr, double *sigSrcReXArr, double *sigSrcImXArr, int IDFTLength);

int main() {

    FILE *fptr, *fptr2, *fptr3;
    calcDFT((double *) &InputSignal_f32_1kHz_15kHz[0], (double *) &outputReX[0],
    (double *) &outputImX[0], (int) SIG_LENGTH);
    fptr = fopen("input_signal.dat", "w");
    fptr2 = fopen("output_rex.dat", "w");
    fptr3 = fopen("output_imx.dat", "w");

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(fptr, "\n%f", InputSignal_f32_1kHz_15kHz[i]);
    }

    for (int i = 0; i < SIG_LENGTH / 2; i++) {
        fprintf(fptr2, "\n%f", outputReX[i]);
        fprintf(fptr3, "\n%f", outputImX[i]);
    }

    fclose(fptr);
    fclose(fptr2);
    fclose(fptr3);

    return 0;
}

void calcInverseDFT(double *IDFTOutArr, double *sigSrcReXArr, double *sigSrcImXArr, int IDFTLength) {
    double PI = 3.14159265359;

    int i;
    int k;

    for (k = 0; k < IDFTLength / 2; k++) {
        sigDestReXArr[k] /= (IDFTLength / 2);
        sigDestImXArr[k] = -sigDestImXArr[k] / (IDFTLength / 2); 
    }
}