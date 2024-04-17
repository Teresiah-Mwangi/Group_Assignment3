/* Implementing a C program using pointers which receives two arrays :  inOrder  and postOrder traversals
   and generates a binary search tree and uses breadth first search (BST) algorithm to display the BST elements.
   ---------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNewNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* bst_construct(int inOrder[], int postOrder[], int inStart, int inEnd, int postIndex) {

    if (inStart > inEnd)
        return NULL;

    struct Node* rootnode = createNewNode(postOrder[postIndex]);


    if (inStart == inEnd)
        return rootnode;

    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; ++inIndex) {
        if (inOrder[inIndex] == rootnode->data)
            break;
    }
    rootnode->right = bst_construct(inOrder, postOrder, inIndex + 1, inEnd, postIndex - 1);
    rootnode->left = bst_construct(inOrder, postOrder, inStart, inIndex - 1, postIndex - (inEnd - inIndex) - 1);

    return rootnode;
}
void bfsTraversal(struct Node* rootnode) {
    if (rootnode == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = rootnode;

    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}
int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int size = sizeof(inOrder) / sizeof(inOrder[0]);

    struct Node* rootnode = bst_construct(inOrder, postOrder, 0, size - 1, size - 1);

    printf("Breadth First Search Traversal Output:\n");
    bfsTraversal(rootnode);
    printf("\n\n");
    return 0;
}
