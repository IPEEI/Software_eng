/*
 * 科目：ソフトウェア演習Ia
 * 学籍番号・氏名：B233339・多賀一平
 * 課題番号：課題5-1
 * 提出日：2023/5/23
 * 使用Ｃコンパイラ：gcc version 10.3.0-2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 三角形と色を定義
typedef struct Triangle {
    double x1, y1;
    double x2, y2;
    double x3, y3;
    double R, G, B;
} Triangle;

// ノードを定義
typedef struct Node {
    struct Triangle data;
    struct Node* next;
} Node;

Node* head = NULL;

// 新しいノードを作成
Node* createNode(Triangle t) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = t;
    newNode->next = NULL;
    return newNode;
}

// ノードを追加
void insertNode(Triangle t) {
    Node* newNode = createNode(t);
    newNode->next = head;
    head = newNode;
}

// ランダムな値を生成
double randInRange(double min, double max) {
    return min + (rand() / (RAND_MAX / (max-min)));
}

// Postscriptファイルに出力
void outputToFile(char* filename) {
    FILE* file = fopen(filename, "w");
    Node* temp = head;
    //リストの最後尾までループ
    while(temp != NULL) {
        Triangle t = temp->data;
        fprintf(file, "%f %f moveto\n", t.x1, t.y1);
        fprintf(file, "%f %f lineto\n", t.x2, t.y2);
        fprintf(file, "%f %f lineto\n", t.x3, t.y3);
        fprintf(file, "closepath\n");
        fprintf(file, "%f %f %f setrgbcolor\n", t.R, t.G, t.B);
        fprintf(file, "fill\n");
        temp = temp->next;
    }
    fclose(file);
}

int main() {
    srand(time(0));
    //ランダムなNを作成し三角形データ数を決める
    int N = rand() % (100-3+1) + 3;

    //三角形データを生成し、リストを用いてまとめる
    for(int i = 0; i < N; i++) {
        //各TriangleはrandInRange()関数を使って指定された範囲内の座標と色情報を持つ
        Triangle t = {
            randInRange(50.0, 550.0), randInRange(50.0, 550.0),
            randInRange(50.0, 550.0), randInRange(50.0, 550.0),
            randInRange(50.0, 550.0), randInRange(50.0, 550.0),
            randInRange(0.0, 1.0), randInRange(0.0, 1.0), randInRange(0.0, 1.0)
        };
        //insertNode()関数を使ってリンクされたリストに追加する
        insertNode(t);
    }

    //結果を出力する
    outputToFile("output.ps");
    printf("done");
    
    return 0;
}

/*
実行結果：
gcc 233339report0501.c -Wall -o 233339report0501
233339report0501

done
*/