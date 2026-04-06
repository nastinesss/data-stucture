#include <iostream>
#include <ctime>
using namespace std;

struct Tree {
    int m;
    Tree* left;
    Tree* right;
} *root=0;

Tree* insert(Tree* root,int value) {
    if (root==0) {
        Tree *node=new Tree;
        node->m=value;
        node->left=0;
        node->right=0;
        return node;
    }
    if (value<root->m)
        root->left=insert(root->left,value);
    else if (value>root->m)
        root->right=insert(root->right,value);
    return root;
}

void deleteTree(Tree* node) {
    if (node==0) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void show(Tree* root) {
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

void splitTree(Tree* root, Tree*& evenTree, Tree*& oddTree) {
    if (!root) return;
    if (root->m%2==0)
        evenTree=insert(evenTree,root->m);
    else oddTree=insert(oddTree,root->m);
    splitTree(root->left,evenTree,oddTree);
    splitTree(root->right,evenTree,oddTree);
}

int getDepth(Tree* root) {
    if (!root) return 0;
    int leftDepth = getDepth(root->left);
    int rightDepth = getDepth(root->right);

    if (leftDepth>rightDepth) return (leftDepth+1);
    else return (rightDepth+1);
}

int main() {
    srand(time(0));

    int n, k;
    cout<<"Enter number of nodes: ";
    cin>>n;

    int choice;
    cout<<"Choose: 1 - manually, 2 - random:"<<endl;
    cin>>choice;
    if (choice==1) {
        cout<<"Enter nodes: ";
        for (int i=0;i<n;i++) {
            cin>>k;
            if (search(root, k)==nullptr) {
                root=insert(root,k);
            }
        }
        cout<<"Showing all nodes: "<<endl;
        show(root);
    }
    else if (choice==2) {
        int a, b;
        cout<<"Enter [a, b]: "<<endl;
        cin>>a>>b;

        if (n>(b-a+1)) {
            cout<<"n is too large for this range."<<endl;
            return 1;
        }

      for (int i=0;i<n;i++) {
          k=rand()%(b-a+1)+a;
          if (search(root, k)==nullptr) {
              root=insert(root,k);
          } else {
              i--;
          }
      }
        show(root);
    }

    cout<<endl;

    Tree *evenTree = 0, *oddTree = 0;
    splitTree(root, evenTree, oddTree);
    cout<<"Even Tree: ";
    show(evenTree);
    cout<<endl;
    cout<<"Odd Tree: ";
    show(oddTree);
    cout<<endl;

    cout<<"Depth of main tree: "<<getDepth(root)<<endl;
    cout<<"Depth of even tree: "<<getDepth(evenTree)<<endl;
    cout<<"Depth of odd tree: "<<getDepth(oddTree)<<endl;

    deleteTree(root);
    deleteTree(evenTree);
    deleteTree(oddTree);
    return 0;
}