#include <stdio.h>
#define LIMIT_COLUMN 100

void reverse(char *s);

int main(void)
{
    FILE *fp;
    

    fp = fopen("Alice_in_Wonderland.txt", "r"); /* ファイルのオープン */

    if (fp == NULL) {
        printf("¥Cannot open the file.\n");
    } else {
        while(1){
            char buf[LIMIT_COLUMN]={0}; //一時的に文字列を保存しておく配列
            if(fgets(buf,LIMIT_COLUMN,fp)==NULL)break;
            reverse(buf);
            printf("%s\n",buf);
        }
        fclose(fp); /* ファイルのクローズ */
    }
    return 0;
}

void reverse(char *input){
    char rev[LIMIT_COLUMN]={0};//反転結果を保存しておく配列
    int count=0;
    //その行の文字数をカウントする
    for(int j=0;j<LIMIT_COLUMN&&input[j]!='\n';++j){
        count++;
    }
    for(int j=0;j<count;++j){
        rev[j]=input[count-1-j];
    }

    for(int j=0;j<LIMIT_COLUMN;++j){
        input[j]=rev[j];
    }
}