/*
 * 科目：ソフトウェア演習Ia
 * 学籍番号・氏名：B233339・多賀一平
 * 課題番号：課題1-1
 * 提出日：2023/4/19
 * 使用Ｃコンパイラ：gcc version 10.3.0-2
 */

#include<stdio.h>
#include <ctype.h>
#define MAXLINE 1000000    //最大読み込み文字数  
void count(long int memory[], long int maxline);

int main()
{
    long int memo[128]={0}; //アルファベット・記号をカウントするための関数
    count(memo,MAXLINE);//文字数カウント
    for(int i=0;i<128;i++)
    {
        if(isprint(i))
        {
            printf("\'%c\' : ",i);
            printf("%ld\n",memo[i]);
        }
    }
    return 0;
}

void count(long int m[], long int lim){  
    int c;   //getcharの受け取り用変数c 
    long int i; //ループ用変数i 
      
    for (i = 0; i < lim - 1 && (c = getchar()) != '\0'; ++i)  
        m[c]++;       
}
 
/*
実行結果：
gcc 233339report0101.c -Wall -o 233339report0101
233339report0101 <Alice_in_Wonderland.txt
' ' : 28918
'!' : 450
'"' : 113
'#' : 0
'$' : 0
'%' : 0
'&' : 0
''' : 1763
'(' : 56
')' : 55
'*' : 60
'+' : 0
',' : 2418
'-' : 669
'.' : 978
'/' : 0
'0' : 1
'1' : 0
'2' : 0
'3' : 1
'4' : 0
'5' : 0
'6' : 0
'7' : 0
'8' : 0
'9' : 0
':' : 233
';' : 194
'<' : 0
'=' : 0
'>' : 0
'?' : 202
'@' : 0
'A' : 638
'B' : 91
'C' : 145
'D' : 192
'E' : 188
'F' : 74
'G' : 83
'H' : 284
'I' : 733
'J' : 8
'K' : 82
'L' : 98
'M' : 200
'N' : 120
'O' : 176
'P' : 64
'Q' : 84
'R' : 140
'S' : 218
'T' : 472
'U' : 66
'V' : 42
'W' : 237
'X' : 4
'Y' : 114
'Z' : 1
'[' : 2
'\' : 0
']' : 2
'^' : 0
'_' : 4
'`' : 1109
'a' : 8153
'b' : 1384
'c' : 2254
'd' : 4739
'e' : 13386
'f' : 1927
'g' : 2448
'h' : 7090
'i' : 6781
'j' : 138
'k' : 1076
'l' : 4618
'm' : 1907
'n' : 6896
'o' : 7970
'p' : 1460
'q' : 125
'r' : 5297
's' : 6282
't' : 10217
'u' : 3402
'v' : 804
'w' : 2438
'x' : 144
'y' : 2150
'z' : 77
'{' : 0
'|' : 0
'}' : 0
'~' : 0
*/  