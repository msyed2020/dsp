#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320

extern double _320_pts_ecg_IMX[SIG_LENGTH];
extern double _320_pts_ecg_REX[SIG_LENGTH];

double OutputMAG[SIG_LENGTH];
double OutputPhase[SIG_LENGTH];

void rectToPolarConversion(double * sigSrcREX, double * sigSrcIMX,
                            double * sigOutMAG, double * sigOutPhase,
                            int sigLength);

int main() {

    FILE *inputREXfptr, *inputIMXfptr, *outputMAGfptr, *outputPhasefptr;
    rectToPolarConversion((double *) &_320_pts_ecg_REX[0], (double *) &_320_pts_ecg_IMX[0],
                            (double *) &OutputMAG[0], (double *) &OutputPhase[0],
                            (int) SIG_LENGTH);

    inputREXfptr = fopen("input_rex.dat", "w");
    inputIMXfptr = fopen("input_imx.dat", "w");
    outputMAGfptr = fopen("output_magnitude.dat", "w");
    outputPhasefptr = fopen("output_phase.dat", "w");

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(inputREXfptr, "\n%f", _320_pts_ecg_REX[i]);
        fprintf(inputIMXfptr, "\n%f", _320_pts_ecg_IMX[i]);
        fprintf(outputMAGfptr, "\n%f", OutputMAG[i]);
        fprintf(outputPhasefptr, "\n%f", OutputPhase[i]);
    }

    fclose(inputREXfptr);
    fclose(inputIMXfptr);
    fclose(outputMAGfptr);
    fclose(outputPhasefptr);

    return 0;
}

void rectToPolarConversion(double * sigSrcREX, double * sigSrcIMX,
                            double * sigOutMAG, double * sigOutPhase,
                            int sigLength)
{
    double PI = 3.14159265358979f;
    int k;
    for (k = 0; k < sigLength; k++) {

        sigOutMAG[k] = sqrt(powf(sigSrcREX[k], 2) + powf(sigSrcIMX[k], 2));
        
        if (sigSrcREX[k] == 0) {
            sigSrcREX[k] = pow(10, -20);
            sigOutPhase[k] = atan(sigSrcIMX[k] / sigSrcREX[k]);
        }

        if ((sigSrcREX[k] < 0) && (sigSrcIMX[k] < 0)) {
            sigOutPhase[k] -= PI;
        }

        if ((sigSrcREX[k] < 0) && (sigSrcIMX[k] >= 0)) {
            sigOutPhase[k] += PI;
        }


    }
}