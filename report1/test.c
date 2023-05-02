/* getline_1.c                                     */  
/* 1行格納し、その後表示                           */  
/* 最大読み込み文字数は改行とヌル文字を除く999文字 */  
#include <stdio.h>    //getchar用  
#define MAXLINE 1000    //最大読み込み文字数  
  
void getline(char line[], int maxline);  
  
int main(void){  
    char str[MAXLINE];  //文字列を格納する配列  
      
    getline(str, MAXLINE);  //strに文字列を格納  
    printf("格納した文字列:%s\n", str);    //表示  
      
    return 0;  
}  
  
/* 
 * 関数名:getline 
 * 引数:文字列領域、文字列領域の長さ 
 * 機能:getchar関数を用いて、標準入力から文字列を受け取る 
 *      エンターキーを押す事により決定、入力文字が規定文字数以上だった場合は 
 *      それまでを格納する 
 * 返り値:なし 
 */  
void getline(char s[], int lim){  
    int c, i;   //getcharの受け取り用変数c、ループ用変数i  
      
    for (i = 0; i < lim - 1 && (c = getchar()) != '\n'; ++i)  
        s[i] = c;  
      
    s[i] = '\0';  
}  