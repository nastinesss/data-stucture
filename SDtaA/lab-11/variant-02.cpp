#include <iostream>
#include <string>
#include <ctime>
using namespace std;
struct Tree1 {
    int height;
    string name;
    Tree1* left;
    Tree1* right;
    Tree1 (int h, string n) : height(h), name(n), left(nullptr), right(nullptr) {}
}*root=0;

struct Tree2 {
    int height;
    Tree2* left;
    Tree2* right;
    Tree2 (int h) : height(h), left(nullptr), right(nullptr) {}
};

Tree1* insertTree1(Tree1* root, int height, string name) {
    if (root == 0) {
        return new Tree1(height, name);
    }
    if (height < root->height) {
        root->left = insertTree1(root->left, height, name);
    } else {
        root->right = insertTree1(root->right, height, name);
    }
    return root;
}

Tree2* insertTree2(Tree2* root, int height) {
    if (root == 0) {
        return new Tree2(height);
    }
    if (height < root->height) {
        root->left = insertTree2(root->left, height);
    } else {
        root->right = insertTree2(root->right, height);
    }
    return root;
}

int countNameOccurrences(Tree1* root, const string& targetName) {
    if (root == 0) {
        return 0;
    }
    int count = (root->name == targetName) ? 1 : 0;
    return count + countNameOccurrences(root->left, targetName) + countNameOccurrences(root->right, targetName);
}
void buildSecondTree(Tree1* sourceRoot, Tree2*& destRoot) {
    if (sourceRoot == 0) return;

    destRoot = insertTree2(destRoot, sourceRoot->height);

    buildSecondTree(sourceRoot->left, destRoot);
    buildSecondTree(sourceRoot->right, destRoot);
}

Tree1* buildTree(int n, string names[], int namesCount) {
    Tree1* treeRoot = nullptr;

    for (int i = 0; i < n; i++) {
        int randomHeight = 150 + rand() % 51;
        string randomName = names[rand() % namesCount];

        treeRoot = insertTree1(treeRoot, randomHeight, randomName);
    }

    return treeRoot;
}

int countNodes(Tree1* root) {
    if (root == 0) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countNodes(Tree2* root) {
    if (root == 0) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}
int tree1Depth(Tree1* root) {
    if (root == 0) return 0;
    return 1 + max(tree1Depth(root->left), tree1Depth(root->right));
}

int tree2Depth(Tree2* root) {
    if (root == 0) return 0;
    return 1 + max(tree2Depth(root->left), tree2Depth(root->right));
}

void deleteTree1(Tree1* node) {
    if (node==0) return;
    deleteTree1(node->left);
    deleteTree1(node->right);
    delete node;
}

void deleteTree2(Tree2* node) {
    if (node==0) return;
    deleteTree2(node->left);
    deleteTree2(node->right);
    delete node;
}

void printTree1(Tree1* root) {
    if (root != 0) {
        printTree1(root->left);
        cout << "[" << root->height << " sm, " << root->name << "] ";
        printTree1(root->right);
    }
}

void printTree2(Tree2* root) {
    if (root != 0) {
        printTree2(root->left);
        cout << "[" << root->height << " sm] ";
        printTree2(root->right);
    }
}

int main() {
    srand(time(0));
    int n, randomHeight, namesCount;
    string randomNames;
    string names[] = {"Anna", "Ivan", "Maria", "Oleg", "Lesya"};
    namesCount=5;
    cout<<"Enter number of nodes: ";
    cin>>n;

    if (n<=0) {
        cout<<"Number of nodes must be >0"<<endl;
        return 0;
    }

    Tree1* tree1=buildTree(n,names,namesCount);
    printTree1(tree1);

    cout<<endl;
    cout<<"Main tree:"<<endl;
    printTree1(tree1);
    cout<<endl;

    string searchName;
    cout<<"Enter search name: ";
    cin>>searchName;

    int occurrences=countNameOccurrences(tree1, searchName);
    if (occurrences>0) {
        cout<<"Name "<<searchName<<" found. Number: "<<occurrences<<endl;
    } else {
        cout<<"Name "<<searchName<<" not found."<<endl;
    }

    Tree2* tree2=0;
    if (tree1!=0 && tree1->left!=0) {
        buildSecondTree(tree1->left, tree2);
        cout<<"Second tree:"<<endl;
        printTree2(tree2);
        cout<<endl;
    } else {
        cout<<"Left tree of main tree is empty. Second tree is empty."<<endl;
    }

    cout<<"Tree statistics: "<<endl;
    cout<<"Main tree:"<<endl;
    cout<<"Number of nodes: "<<countNodes(tree1)<<endl;
    cout<<"Depth: "<<tree1Depth(tree1)<<endl;

    cout<<"Second tree:"<<endl;
    cout<<"Number of nodes: "<<countNodes(tree2)<<endl;
    cout<<"Depth: "<<tree2Depth(tree2)<<endl;

    deleteTree1(tree1);
    deleteTree2(tree2);

    return 0;
}