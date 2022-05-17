#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

struct BinaryTree
{
    int val;
    struct BinaryTree *left;
    struct BinaryTree *right;
};

typedef struct BinaryTree btree_t;

void preorder(struct BinaryTree *t) {
    printf("%d", t->val);
    if (t->left != NULL) preorder(t->left);
    if (t->right != NULL) preorder(t->right);
}

void inorder(struct BinaryTree *t) {
    if (t->left != NULL) preorder(t->left);
    printf("%d", t->val);
    if (t->right != NULL) preorder(t->right);
}

void postorder(struct BinaryTree *t) {
    if (t->left != NULL) preorder(t->left);
    if (t->right != NULL) preorder(t->right);
    printf("%d", t->val);
}

int main(int argc,char *argv[]) {
    btree_t r = {0};
    btree_t r_l = {1};
    btree_t r_r = {2};
    btree_t r_ll = {7};
    btree_t r_lr = {5};
    btree_t r_rr = {8};
    r.left = &r_l;
    r.right = &r_r;

    r_l.left = &r_ll;
    r_l.right = &r_lr;

    r_r.right = &r_rr;
    preorder(&r); printf("\n");
    inorder(&r); printf("\n");
    postorder(&r); printf("\n");
}

