// compile: gcc main.c waveforms.c -o dft -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double outputReX[SIG_LENGTH / 2];
double outputImX[SIG_LENGTH / 2];
double outputMAG[SIG_LENGTH / 2];
void calcDFT(double * sigSrcArr, double * sigDestReXArr, double * sigDestImXArr, int sig_length);

int main() {

    FILE *fptr, *fptr2, *fptr3;
    calcDFT((double *) &InputSignal_f32_1kHz_15kHz[0], (double *) &outputReX[0],
    (double *) &outputImX[0], (int) SIG_LENGTH);

    getDFTOutputMAG((double *) sigDestMAGArr);

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

void getDFTOutputMAG(double *sigDestMAGArr) {
    int k;
    for (k = 0; k < SIG_LENGTH / 2; k++) {
        sigDestMAGArr[k] = sqrt(pow(outputReX[k], 2) + pow(outputImX[k], 2));
    }
}