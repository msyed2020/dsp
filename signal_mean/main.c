// gcc main.c waveforms.c -o signal_mean

#include <stdio.h>
#include <stdlib.h>
#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double calcSignalMean(double *signalSrcArr, int sigLength);
double avg;

int main() {

    avg = calcSignalMean(&InputSignal_f32_1kHz_15kHz[0], SIG_LENGTH);
    printf("Mean = %f\n", avg);
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