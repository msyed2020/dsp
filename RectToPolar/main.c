#include <stdio.h>
#include <stdlib.h>
#define SIG_LENGTH 320

extern double _320_pts_ecg_IMX[SIG_LENGTH];
extern double _320_pts_ecg_REX[SIG_LENGTH];

void rectToPolarConversion(double * sigSrcREX, double * sigSrcIMX,
                            double * sigOutMAG, double * sigOutPhase,
                            int sigLength);

int main() {



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
            
        }
    }
}