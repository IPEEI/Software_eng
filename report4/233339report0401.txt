/*
 * 科目：ソフトウェア演習Ia
 * 学籍番号・氏名：B233339・多賀一平
 * 課題番号：課題4-1
 * 提出日：2023/5/16
 * 使用Ｃコンパイラ：gcc version 10.3.0-2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMIT_WORD 45 //最長の英単語の文字数

typedef struct node {
    char *d;
    int c;
    struct node *left; // subtree
    struct node *right; // subtree
}NODE,*BTREE;

//ノードのメモリを確保
BTREE allocNode( char *x )
{
    BTREE p;
    p = (BTREE)malloc(sizeof(NODE));
    p->d = strdup(x);
    p->c = 1;
    p->left = p->right = NULL;
    return p ;
}

//ノードの挿入
BTREE insertNode( BTREE node, char *x )
{
    BTREE p = node;
    if ( p == NULL ) { // rootに挿入
        p = allocNode( x );
        return p ;
    }
    if ( strcmp(x ,p->d)==0 ) {
        // 等しいときの処理
        p->c++;
    } else if ( strcmp(x ,p->d)<0 ) { // 左部分木に割り当て
        p->left = insertNode(p->left, x); // 再帰呼出し
    } else { // 右部分木に割り当て
        p->right = insertNode(p->right, x); // 再帰呼出し
    }
    return p ;
}

void printBtree( BTREE p )
{
    if (p != NULL ) {
        static int num=1;
        printBtree( p->left ); // 左部分木の処理（再帰呼び出し）
        printf("%d: WORD: \"",num++);
        printf( "%s, COUNT: %d\n", p->d , p->c);
        printBtree( p->right ); // 右部分木の処理（再帰呼び出し）
    }
    return;
}

void freeBtree( BTREE p )
{
    if (p != NULL ) {
        freeBtree( p->left ); // 左部分木の処理（再帰呼び出し）
        freeBtree( p->right ); // 右部分木の処理（再帰呼び出し）
        free( p );
    }
    return;
}

int main(void)
{
    FILE *fp;
    fp = fopen("Alice_in_Wonderland.txt", "r"); /* ファイルのオープン */

    if (fp == NULL) {
        printf("¥Cannot open the file.\n");
    } else {
        BTREE R = NULL;
        char word[LIMIT_WORD];
        //fscanfでこの条件下での単語を取得できる
        while (fscanf(fp, "%s", word) != EOF) {
            R=insertNode(R,word);
        }
        printBtree(R);
        freeBtree(R); 
        fclose(fp); /* ファイルのクローズ */
    }
    return 0;
}


/*
実行結果：
gcc 233339report0401.c -Wall -o 233339report0401
233339report0401

1: WORD: ""'TIS, COUNT: 1
2: WORD: ""--SAID, COUNT: 1
3: WORD: ""Come, COUNT: 1
4: WORD: ""Coming, COUNT: 1
5: WORD: ""Edwin, COUNT: 1
6: WORD: ""French,, COUNT: 1
7: WORD: ""HOW, COUNT: 1
8: WORD: ""He's, COUNT: 1
9: WORD: ""How, COUNT: 1
10: WORD: ""I, COUNT: 8
11: WORD: ""I'll, COUNT: 2
12: WORD: ""Keep, COUNT: 1
13: WORD: ""Let, COUNT: 1
14: WORD: ""Such, COUNT: 1
15: WORD: ""THEY, COUNT: 1
16: WORD: ""There, COUNT: 2
17: WORD: ""There's, COUNT: 1
18: WORD: ""Too, COUNT: 1
19: WORD: ""Turtle, COUNT: 1
20: WORD: ""Twinkle,, COUNT: 1

5292: WORD: "you,, COUNT: 25
5293: WORD: "you,', COUNT: 6
5294: WORD: "you--all, COUNT: 1
5295: WORD: "you--are, COUNT: 1
5296: WORD: "you., COUNT: 1
5297: WORD: "you.', COUNT: 1
5298: WORD: "you:, COUNT: 1
5299: WORD: "you?, COUNT: 2
5300: WORD: "you?', COUNT: 7
5301: WORD: "young, COUNT: 5
5302: WORD: "your, COUNT: 53
5303: WORD: "yours, COUNT: 1
5304: WORD: "yours."', COUNT: 1
5305: WORD: "yourself, COUNT: 5
5306: WORD: "yourself!', COUNT: 1
5307: WORD: "yourself,, COUNT: 1
5308: WORD: "yourself,', COUNT: 1
5309: WORD: "yourself.', COUNT: 2
5310: WORD: "youth,, COUNT: 3
5311: WORD: "youth,', COUNT: 3
5312: WORD: "zigzag,, COUNT: 1

*/