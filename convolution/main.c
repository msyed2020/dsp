// COMPILE: gcc main.c waveforms.c -o convolution -lm

// Linear convolution algorithm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];


int main() {

    // avg = calcSignalMean(&InputSignal_f32_1kHz_15kHz[0], SIG_LENGTH);
    // vari = calcSignalVariance(&InputSignal_f32_1kHz_15kHz[0], avg, SIG_LENGTH);
    // standardDev = calcSignalSTD(vari);
    // printf("Mean = %f\n", avg);
    // printf("Average = %f\n", vari);
    // printf("Standard Deviation = %f\n", standardDev);
    return 0;
}

double calcSignalMean(double *signalSrcArr, int sigLength) {
    double mean = 0.0;
    for (int i = 0; i < sigLength; i++) {
        mean += signalSrcArr[i];
    }
    mean = mean / (double) sigLength;
    return mean;
}

double calcSignalVariance(double *signalSrcArr, double sigMean, int sigLength) {
    double variance = 0.0;
    for (int i = 0; i < sigLength; i++) {
        variance += pow((signalSrcArr[i] - sigMean), 2);
    }
    variance = variance / (sigLength - 1);
    return variance;
}  

double calcSignalSTD(double sigVar) {
    double std = sqrt(sigVar);
    return std;
}
