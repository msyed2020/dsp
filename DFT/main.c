#include <stdio.h>
#include <stdlib.h>
#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
void calcDFT(double * sigSrcArr, double * sigDestReXArr, double * sigDestImXArr, int sig_length);

int main() {



    return 0;
}

void calcDFT(double * sigSrcArr, double * sigDestReXArr, double * sigDestImXArr, int sig_length) {
    int i, j, k;
    double PI = 3.14159265359;

    for (j = 0; j < sig_length / 2; j++) {
        
    }
}