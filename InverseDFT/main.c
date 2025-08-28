// compile: gcc main.c waveforms.c -o idft -lm

// Inverse Discrete Fourier Transform

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double outputReX[SIG_LENGTH / 2];
double outputImX[SIG_LENGTH / 2];
double outputIDFT[SIG_LENGTH];

void calcDFT(double * sigSrcArr, double * sigDestReXArr, double * sigDestImXArr, int sig_length);
void calcInverseDFT(double *IDFTOutArr, double *sigSrcReXArr, double *sigSrcImXArr, int IDFTLength);

int main() {

    FILE *fptr, *fptr2, *fptr3, *fptr4;
    calcDFT((double *) &InputSignal_f32_1kHz_15kHz[0], (double *) &outputReX[0],
    (double *) &outputImX[0], (int) SIG_LENGTH);

    calcInverseDFT((double *) &outputIDFT[0], (double *) &outputReX[0], (double *) &outputImX[0], (int) SIG_LENGTH);

    fptr = fopen("input_signal.dat", "w");
    fptr2 = fopen("output_rex.dat", "w");
    fptr3 = fopen("output_imx.dat", "w");
    fptr4 = fopen("output_idft.dat", "w");

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

void calcDFT(double * sigSrcArr, double * sigDestReXArr, double * sigDestImXArr, int sig_length) {
    int i, j, k;
    double PI = 3.14159265359;

    for (j = 0; j < sig_length / 2; j++) {
        sigDestReXArr[j] = 0;
        sigDestImXArr[j] = 0;
    }

    for (k = 0; k < (sig_length / 2); k++) {
        for (i = 0; i < sig_length; i++) {
            sigDestReXArr[k] += sigSrcArr[i]*cos(2 * PI * k * i / sig_length);
            sigDestImXArr[k] -= sigSrcArr[i]*sin(2 * PI * k * i / sig_length);
        }
    }
}

void calcInverseDFT(double *IDFTOutArr, double *sigSrcReXArr, double *sigSrcImXArr, int IDFTLength) {
    double PI = 3.14159265359;

    int i;
    int k;

    for (k = 0; k < IDFTLength / 2; k++) {
        sigSrcReXArr[k] /= (IDFTLength / 2);
        sigSrcImXArr[k] = -sigDestImXArr[k] / (IDFTLength / 2); 
    }
    sigSrcReXArr[0] /= 2;
    sigSrcImXArr[0] = -sigSrcImXArr[0] / 2;

    for (i = 0; i < IDFTLength; i++) {
        IDFTOutArr[i] = 0;
    }
    for (k = 0; k < IDFTLength / 2; k++) {
        for (i = 0; i < IDFTLength; i++) {
            IDFTOutArr[i] += (sigSrcReXArr[k] * cos(2 * PI * k * i / IDFTLength));
            IDFTOutArr[i] += (sigSrcImXArr[k] * sin(2 * PI * k * i / IDFTLength));
        }
    }
}