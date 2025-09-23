#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 501

// compile: compile: gcc main.c waveforms.c -o recttopolar -lm

extern double _501pts_20Hz_sig_imx[SIG_LENGTH];
extern double _501pts_20Hz_sig_rex[SIG_LENGTH];

double OutputMAG[SIG_LENGTH];
double OutputPhase[SIG_LENGTH];


int main() {

    FILE *inputREXfptr, *inputIMXfptr, *outputMAGfptr, *outputPhasefptr;

    inputREXfptr = fopen("input_rex.dat", "w");
    inputIMXfptr = fopen("input_imx.dat", "w");
    outputMAGfptr = fopen("output_magnitude.dat", "w");
    outputPhasefptr = fopen("output_phase.dat", "w");

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(inputREXfptr, "\n%f", _501pts_20Hz_sig_rex[i]);
        fprintf(inputIMXfptr, "\n%f", _501pts_20Hz_sig_imx[i]);
        fprintf(outputMAGfptr, "\n%f", OutputMAG[i]);
        fprintf(outputPhasefptr, "\n%f", OutputPhase[i]);
    }

    fclose(inputREXfptr);
    fclose(inputIMXfptr);
    fclose(outputMAGfptr);
    fclose(outputPhasefptr);

    return 0;
}

void complexDFT(double *sigSrcTimeDomainReX,
                double *sigSrcTimeDomainImX,
                double *sigDestFreqDomainReX,
                double *sigDestFreqDomainImX,
                int sigLength) 
{

    double PI = 3.14159265358979f;

    double SReX;
    double SImX;
    for (int k = 0; k < sigLength; k++) {

        for (int i = 0; i < sigLength; i++) {
            SReX = cos(2*PI*k*i / sigLength);
            SImX = -1 * sin(2*PI*k*i / sigLength);
        }
    }    

}