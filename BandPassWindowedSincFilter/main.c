#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH  320
#define KERNEL_LENGTH   29

void bandPassWindowedSinc(
                        double *lowerCutoffStateBuff,
                        double *upperCutoffStateBuff,
                        double *filterKernelDestinationArr,
                        double lowerCutoff,
                        double upperCutoff,
                        int filterLength,
                        double *sigSrcArr,
                        double *sigDestArr,
                        int inputSigLength);

int main() {
    

    return 0;
}

void bandPassWindowedSinc(
                        double *lowerCutoffStateBuff,
                        double *upperCutoffStateBuff,
                        double *filterKernelDestinationArr,
                        double lowerCutoff,
                        double upperCutoff,
                        int filterLength,
                        double *sigSrcArr,
                        double *sigDestArr,
                        int inputSigLength)
{
    
}