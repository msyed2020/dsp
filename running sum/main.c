// COMPILE: gcc main.c waveforms.c -o rs -lm

// Running Sum algorithm

// waveforms.c is the input signal

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double output_sig[SIG_LENGTH];
void calcRunningSum(double *sigSrcArr, double *sigDestArr, int sigLength);


int main() {

    FILE *inputSigFPTR, *outputSigFPTR;
    inputSigFPTR = fopen("input_signal.dat", "w");
    outputSigFPTR = fopen("output_signal.dat", "w");

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(inputSigFPTR, "\n%f", InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(inputSigFPTR);

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(outputSigFPTR, "\n%f", output_sig[i]);
    }
    fclose(outputSigFPTR);

    return 0;
}

void calcRunningSum(double *sigSrcArr, double *sigDestArr, int sigLength) {
    
}