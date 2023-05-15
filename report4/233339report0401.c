/*
 * 科目：ソフトウェア演習Ia
 * 学籍番号・氏名：B233339・多賀一平
 * 課題番号：課題4-1
 * 提出日：2023/5/16
 * 使用Ｃコンパイラ：gcc version 10.3.0-2
 */

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
実行結果：
gcc 233339report0401.c -Wall -o 233339report0401
233339report0401



*/