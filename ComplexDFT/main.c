#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 501

// compile: compile: gcc main.c waveforms.c -o recttopolar -lm

extern double _501pts_20Hz_sig_imx[SIG_LENGTH];
extern double _501pts_20Hz_sig_rex[SIG_LENGTH];

double OutputReX[SIG_LENGTH];
double OutputImX[SIG_LENGTH];

void complexDFT(double *sigSrcTimeDomainReX,
                double *sigSrcTimeDomainImX,
                double *sigDestFreqDomainReX,
                double *sigDestFreqDomainImX,
                int sigLength);


int main() {

    FILE *inputREXfptr, *inputIMXfptr, *outputREXfptr, *outputIMXfptr;

    complexDFT((double *) &_501pts_20Hz_sig_rex[0],
                (double *) &_501pts_20Hz_sig_imx[0],
                (double *) &OutputReX[0],
                (double *) &OutputImX[0],
                (int) SIG_LENGTH);

    inputREXfptr = fopen("input_rex.dat", "w");
    inputIMXfptr = fopen("input_imx.dat", "w");
    outputREXfptr = fopen("output_magnitude.dat", "w");
    outputIMXfptr = fopen("output_phase.dat", "w");

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(inputREXfptr, "\n%f", _501pts_20Hz_sig_rex[i]);
        fprintf(inputIMXfptr, "\n%f", _501pts_20Hz_sig_imx[i]);
        fprintf(outputREXfptr, "\n%f", OutputReX[i]);
        fprintf(outputIMXfptr, "\n%f", OutputImX[i]);
    }

    fclose(inputREXfptr);
    fclose(inputIMXfptr);
    fclose(outputREXfptr);
    fclose(outputIMXfptr);

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

            sigDestFreqDomainReX[k] += (SReX * sigSrcTimeDomainReX[i]) - (SImX * sigSrcTimeDomainImX[i]);
            sigDestFreqDomainImX[k] += (SImX * sigSrcTimeDomainImX[i]) - (sigSrcTimeDomainImX[i]);
        }
    }    

}