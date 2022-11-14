// Written by Ben.

#include "bst.h"
#include "utils.h"

Node* initTree(char key) {
    // create new node
    
    Node* root = (Node*) malloc(sizeof(Node));
    root->key = key;
    
    return root;
}

Node* insert(Node* root, char key) {
    // inserts as child of root otherwise returns
    if (root->leftChild != NULL && root->rightChild != NULL) {
        printf("Failed to insert node as child of root. \n");
        return NULL; // return before we spend time allocating new memory
    }
    
    // create new node
    Node* n = (Node*) malloc(sizeof(Node));
    n->key = key;

    if (root->leftChild == NULL) {
        root->leftChild = n;
    } else { // would have already returned if right child wasn't null
        root->rightChild = n;
    }

    return n;
}

void postOrder(Node* root, char* buffer) {
    // perform post order traversal of root
    if (root == NULL)
        return;

    postOrder(root->leftChild, buffer);
    postOrder(root->rightChild, buffer);
    sprintf(buffer, "%s%c", buffer, root->key); 
}

void preOrder(Node* root, char* buffer) {
    if (root == NULL)
        return;
    
    sprintf(buffer, "%s%d,", buffer, root->key);
    preOrder(root->leftChild, buffer);
    preOrder(root->rightChild, buffer);
}

int max(int a, int b) { return a > b ? a : b; } // helper function
int height(Node* root) { // return the height of this node

    if (root == NULL)
        return -1;

    int hleft = height(root->leftChild);
    int hright = height(root->rightChild);
   
    return max(hleft, hright) + 1;
}

int balance(Node* root) {
    if(root == NULL)
        return 1; // if the tree is empty, its considered balanced

    int hl = height(root->rightChild);
    int hr = height(root->leftChild);

    return hl - hr; // calculates the balance factor
}

int isBalanced(Node* root) {
    int bf = balance(root);
    return bf > -1 && bf < 1; // balance factor must fall between [-1, 1] for the root to be considered balanced
}

Node* lrot(Node* root) {
    if(root == NULL)
        return root;

    Node* x1 = root->rightChild;
    if(x1 == NULL)
        return root; // dont rotate
    Node* x2 = x1->leftChild;

    x1->leftChild = root;
    root->rightChild = x2;

    return x1;
}

Node* rrot(Node* root) {
    if(root == NULL)
        return root;

    Node* x1 = root->leftChild;
    if(x1 == NULL)
        return root; // dont rotate
    Node* x2 = x1->rightChild;

    x1->rightChild = root;
    root->leftChild = x2;

    return x1;
}

Node* rotation(Node* root) { // convert tree held by root to AVL
    if (root == NULL || isBalanced(root))
        return root;
    
    int bf = balance(root);
    int cbf; // child balance factor

    if(bf < 0) { // left heavy
        cbf = balance(root->leftChild);
        if(cbf > 0)
            root = lrot(root->leftChild); // handles right-left case
        root = rrot(root);
    } else if(bf > 0) { // right heavy
        cbf = balance(root->rightChild);
        if(cbf < 0)
            root = rrot(root->rightChild); // handles left-right case
        root = lrot(root);
    }

    return rotation(root); // keep rotating until balanced
}

int size(Node* root) {
    if (root == NULL)
        return 0;

    return size(root->leftChild) + size(root->rightChild) + 1;
}

int toarr(Node* root, char* arr, int idx) {
    
    if (root == NULL)
        return idx;

    arr[idx] = root->key;
    idx++;

    idx = toarr(root->leftChild, arr, idx); 
    idx = toarr(root->rightChild, arr, idx);

    return idx;
}

Node* totree(char* arr, int start, int end) {
    if (start > end)
        return NULL;

    // make root the middle
    int mid = (start + end) / 2;
    Node* root = initTree(arr[mid]);

    root->leftChild = totree(arr, start, mid-1);
    root->rightChild = totree(arr, mid+1, end);

    return root;
}

Node* merge(Node* a, Node* b) {
    // find size
    int asize = size(a);
    int bsize = size(b);

    // convert tree to arr 
    char* arr = (char*) malloc(sizeof(char) * (asize + bsize));
    int start = toarr(a, arr, 0);
    toarr(b, arr, start);

    // sort the arr
    selectionSort(arr, asize + bsize);

    return totree(arr, 0, (asize + bsize) - 1);
}

