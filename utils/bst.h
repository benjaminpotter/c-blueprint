// Written by Ben.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node { // node stores a single byte
    char key;
    
    struct Node* leftChild;
    struct Node* rightChild;

} Node;

Node* initTree(char key); // must pass a value for the root
Node* insert(Node* root, char key);
void postOrder(Node* root, char* buffer);
void preOrder(Node* root, char* buffer);

int height(Node* root);
int balance(Node* root);
int isBalanced(Node* root);
Node* lrot(Node* root);
Node* rrot(Node* root);
Node* rotation(Node* root);
Node* merge(Node* a, Node* b);
