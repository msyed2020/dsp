// compile: gcc main.c waveforms.c -o ecg -lm

// ECG DFT and IDFT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 640


extern double _640_points_ecg_[SIG_LENGTH];
double outputReX[SIG_LENGTH / 2];
double outputImX[SIG_LENGTH / 2];
double outputMAG[SIG_LENGTH / 2];
double outputIDFT[SIG_LENGTH];

void calcDFT(double * sigSrcArr, double * sigDestReXArr, double * sigDestImXArr, int sig_length);
void calcInverseDFT(double *IDFTOutArr, double *sigSrcReXArr, double *sigSrcImXArr, int IDFTLength);
void getDFTOutputMAG(double *sigDestMAGArr);

int main() {

    FILE *fptr, *fptr2, *fptr3, *fptr4, *fptr5;
    calcDFT((double *) &_640_points_ecg_[0], (double *) &outputReX[0],
    (double *) &outputImX[0], (int) SIG_LENGTH);

    getDFTOutputMAG((double *) &outputMAG[0]);

    calcInverseDFT((double *) &outputIDFT[0], (double *) &outputReX[0], (double *) &outputImX[0], (int) SIG_LENGTH);

    fptr = fopen("input_signal.dat", "w");
    fptr2 = fopen("output_rex.dat", "w");
    fptr3 = fopen("output_imx.dat", "w");
    fptr4 = fopen("output_idft.dat", "w");
    fptr5 = fopen("output_mag.dat", "w");

    for (int i = 0; i < SIG_LENGTH; i++) {
        fprintf(fptr, "\n%f", _640_points_ecg_[i]);
        fprintf(fptr4, "\n%f", outputIDFT[i]);
    }

    for (int i = 0; i < SIG_LENGTH / 2; i++) {
        fprintf(fptr2, "\n%f", outputReX[i]);
        fprintf(fptr3, "\n%f", outputImX[i]);
        fprintf(fptr5, "\n%f", outputMAG[i]);
    }

    fclose(fptr);
    fclose(fptr2);
    fclose(fptr3);
    fclose(fptr5);

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

void calcInverseDFT(double *IDFTOutArr, double *sigSrcReXArr, double *sigSrcImXArr, int IDFTLength) {
    double PI = 3.14159265359;

    int i;
    int k;

    for (k = 0; k < IDFTLength / 2; k++) {
        sigSrcReXArr[k] /= (IDFTLength / 2);
        sigSrcImXArr[k] = -sigSrcImXArr[k] / (IDFTLength / 2); 
    }
    sigSrcReXArr[0] /= 2;
    sigSrcImXArr[0] = -sigSrcImXArr[0] / 2;

    for (i = 0; i < IDFTLength; i++) {
        IDFTOutArr[i] = 0;
    }
    for (k = 0; k < IDFTLength / 2; k++) {
        for (i = 0; i < IDFTLength; i++) {
            IDFTOutArr[i] += (sigSrcReXArr[k] * cos(2 * PI * k * i / IDFTLength));
            IDFTOutArr[i] += (sigSrcImXArr[k] * sin(2 * PI * k * i / IDFTLength));
        }
    }
}

void getDFTOutputMAG(double *sigDestMAGArr) {
    int k;
    for (k = 0; k < SIG_LENGTH / 2; k++) {
        sigDestMAGArr[k] = sqrt(pow(outputReX[k], 2) + pow(outputImX[k], 2));
    }
}




