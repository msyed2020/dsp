// COMPILE: gcc main.c waveforms.c -o convolution -lm

// Linear convolution algorithm

// waveforms.c is the input signal

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320
#define IMP_RSP 29

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
extern double Impulse_response[IMP_RSP];

// ..

int main() {

    FILE *inputSigFPTR, *impRspFPTR;
    inputSigFPTR = fopen("input_signal.dat", "w");
    impRspFPTR = fopen("impulse_response.dat", "w");

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(inputSigFPTR, "\n%f", InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(inputSigFPTR);

    for (int i = 0; i < IMP_RSP; i++) {
        fprintf(impRspFPTR, "\n%f", Impulse_response[i]);
    }
    fclose(impRspFPTR);

    return 0;
}

