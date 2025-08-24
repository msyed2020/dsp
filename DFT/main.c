#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double outputReX[SIG_LENGTH / 2];
double outputImX[SIG_LENGTH / 2];
void calcDFT(double * sigSrcArr, double * sigDestReXArr, double * sigDestImXArr, int sig_length);

int main() {

    calcDFT((double *) &InputSignal_f32_1kHz_15kHz[0], (double *) &outputReX[0],
    (double *) &outputImX[0], (int) SIG_LENGTH);


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