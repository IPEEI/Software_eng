#include <stdio.h>
#include <stdlib.h>

double *get_mean(int ndim, double **data, int ndata) {
    double *mean = (double *)calloc(ndim, sizeof(double));
    for (int i = 0; i < ndata; i++) {
        for (int j = 0; j < ndim; j++) {
            mean[j] += data[i][j];
        }
    }
    for (int j = 0; j < ndim; j++) {
        mean[j] /= ndata;
    }
    return mean;
}

double **get_cova(int ndim, double **data, int ndata) {
    double **cova = (double **)calloc(ndim, sizeof(double *));
    for (int i = 0; i < ndim; i++) {
        cova[i] = (double *)calloc(ndim, sizeof(double));
    }
    double *mean = get_mean(ndim, data, ndata);

    for (int i = 0; i < ndata; i++) {
        for (int j = 0; j < ndim; j++) {
            for (int k = 0; k < ndim; k++) {
                cova[j][k] += (data[i][j] - mean[j]) * (data[i][k] - mean[k]);
            }
        }
    }

    for (int j = 0; j < ndim; j++) {
        for (int k = 0; k < ndim; k++) {
            cova[j][k] /= ndata;
        }
    }

    free(mean);
    return cova;
}

int main() {
    FILE *fp;
    int ndata, ndim;

    fp = fopen("A01M0007-0007.dat", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    fscanf(fp, "%d %d", &ndata, &ndim);

    //2次元配列を動的に確保し、データファイルから各フレームのデータを読み込んで格納。
    double **data = (double **)calloc(ndata, sizeof(double *));
    for (int i = 0; i < ndata; i++) {
        data[i] = (double *)calloc(ndim, sizeof(double));
        for (int j = 0; j < ndim; j++) {
            fscanf(fp, "%lf", &data[i][j]);
        }
    }
    fclose(fp);

    double *mean = get_mean(ndim, data, ndata);
    double **cova = get_cova(ndim, data, ndata);

    printf("Mean Vector:\n");
    for (int i = 0; i < ndim; i++) {
        printf("%lf ", mean[i]);
    }
    printf("\n\nVariance-Covariance Matrix:\n");
    for (int i = 0; i < ndim; i++) {
        for (int j = 0; j < ndim; j++) {
            printf("%lf ", cova[i][j]);
        }
        printf("\n");
    }
    //動的に確保したメモリを解放し、プログラムを終了
    free(mean);
    for (int i = 0; i < ndim; i++) {
        free(cova[i]);
    }
    free(cova);

    for (int i = 0; i < ndata; i++) {
        free(data[i]);
    }
    free(data);

    return 0;
}


/*
Mean Vector:
-0.000014 -0.000001 -0.000018 -0.000009 -0.000012 0.000000 -0.000015 -0.000000 0.000006 -0.000004

Covariance Matrix:
29.471271 -4.837940 2.028353 -21.389792 -15.640306 8.616999 -5.790819 -3.818632 -9.079218 -1.735942
-4.837940 47.828585 2.845787 12.237472 16.812849 14.034974 23.226600 -16.852672 -14.392397 3.204816
2.028353 2.845787 46.211006 20.934828 -27.856179 -5.780364 -11.739078 12.226655 -1.810690 -14.431697
-21.389792 12.237472 20.934828 86.887678 27.689395 -25.679328 9.540696 8.974716 13.989213 12.270149
-15.640306 16.812849 -27.856179 27.689395 92.242244 3.363938 22.242742 -0.466154 13.756317 32.437461
8.616999 14.034974 -5.780364 -25.679328 3.363938 64.946545 19.833721 -21.919222 -10.316377 2.555105
-5.790819 23.226600 -11.739078 9.540696 22.242742 19.833721 75.566127 -11.246475 -2.021936 -0.218053
-3.818632 -16.852672 12.226655 8.974716 -0.466154 -21.919222 -11.246475 65.495327 18.795457 0.033173
-9.079218 -14.392397 -1.810690 13.989213 13.756317 -10.316377 -2.021936 18.795457 59.404086 0.652245
-1.735942 3.204816 -14.431697 12.270149 32.437461 2.555105 -0.218053 0.033173 0.652245 42.640628
*/