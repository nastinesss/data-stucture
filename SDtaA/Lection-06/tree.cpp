#include <iostream>
using namespace std;

struct Tree {
    int m;
    Tree* left;
    Tree* right;
} *root=0;

Tree* insert(Tree *root, int value) {
    if (root==0) {
        Tree *node=new Tree;
        node->m=value;
        node->left=0;
        node->right=0;
        return node;
    }
    if (value<root->m) {
        root->left=insert(root->left,value);
    }
    else if (value>root->m) {
        root->right=insert(root->right,value);
    }
    return root;
}

void show(Tree *root) {
    if (root!=0) {
        show(root->left);
        cout<<root->m<<" ";
        show(root->right);
    }
}

Tree* search(Tree *root, int value) {
    if (root==0) {
        return 0;
    }
    if (root->m==value) {
        return root;
    }
    if (value<root->m) {
        return search(root->left,value);
    }
    else return search(root->right,value);
}

int main() {
    root=insert(root,20);
    root=insert(root,10);
    root=insert(root,23);
    root=insert(root,15);
    show(root);

    cout<<endl;
    root=search(root, 15);
    cout<<root->m;

    return 0;
}