#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    char *word;
    int count;
    struct node *left;
    struct node *right;
} Node;

Node* new_node(char *word) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->word = strdup(word);
    new->count = 1;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node* insert(Node *node, char *word) {
    if (node == NULL) {
        return new_node(word);
    }
    int comparison = strcmp(word, node->word);
    if (comparison < 0) {
        node->left = insert(node->left, word);
    } else if (comparison > 0) {
        node->right = insert(node->right, word);
    } else {
        node->count++;
    }
    return node;
}

void inorder(Node *root) {
    static int num = 1;
    if (root != NULL) {
        inorder(root->left);
        printf("%d: %s - %d\n", num++, root->word, root->count);
        inorder(root->right);
    }
}

void free_tree(Node *node) {
    if (node != NULL) {
        free_tree(node->left);
        free_tree(node->right);
        free(node->word);
        free(node);
    }
}

int main() {
    FILE *file = fopen("Alice_in_Wonderland.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    Node *root = NULL;
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        root = insert(root, word);
    }
    fclose(file);
    inorder(root);
    free_tree(root);
    return 0;
}