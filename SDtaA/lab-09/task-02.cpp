#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Tech {
    int code;
    string name;
    double price;
};

struct TechNode {
    Tech data;
    TechNode *left, *right;
};

TechNode* insert(TechNode* root, Tech item) {
    if (root==nullptr) {
        TechNode* node = new TechNode;
        node->data = item;
        node->left = node->right = nullptr;
        return node;
    }
    if (item.code < root->data.code)
        root->left = insert(root->left, item);
    else if (item.code > root->data.code)
        root->right = insert(root->right, item);
    return root;
}

void deleteTree(TechNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void calculateAverage(TechNode* root, double& totalPrice, int& count) {
    if (!root) return;
    totalPrice+=root->data.price;
    count++;
    calculateAverage(root->left, totalPrice, count);
    calculateAverage(root->right, totalPrice, count);
}

void countLevels(TechNode* root, int currentLevel, int levelsCount[]) {
    if (root==nullptr) return;
    levelsCount[currentLevel]++;
    countLevels(root->left, currentLevel+1, levelsCount);
    countLevels(root->right, currentLevel+1, levelsCount);
}

int calculateMaxDepth(TechNode* root) {
    if (!root) return 0;
    int l=calculateMaxDepth(root->left);
    int r=calculateMaxDepth(root->right);
    int max;
    if (l>r) {
        max=l;
    } else {
        max=r;
    }
    return max+1;
}

TechNode* findAndRemoveChildren(TechNode* root, int searchCode) {
    if (root==nullptr) return nullptr;
    if (root->data.code == searchCode) {
        deleteTree(root->left);
        deleteTree(root->right);
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    if (searchCode < root->data.code)
        return findAndRemoveChildren(root->left, searchCode);
    else
        return findAndRemoveChildren(root->right, searchCode);
}

void showTech(TechNode* root) {
    if (root==nullptr) return;

    showTech(root->left);
    cout<<"Code: "<<root->data.code<<" | "<<root->data.name<<" | Price: "<<root->data.price<<endl;

    showTech(root->right);
}

int main() {
    TechNode* root = nullptr;

    ifstream file("C:/CLionProjects/untitled/SDtaA/lab-09/data.txt");
    if (!file.is_open()) {
        cout<<"Error opening file"<<endl;
        return 1;
    }

    Tech temp;
    while (file >> temp.code >> temp.name >> temp.price) {
        root = insert(root, temp);
    }
    file.close();

    cout<<"Current Tech Tree: "<<endl;
    showTech(root);

    double totalPrice = 0;
    int totalItems = 0;
    calculateAverage(root, totalPrice, totalItems);
    if (totalItems > 0) {
        cout<<"Average Price: "<<totalPrice/totalItems<<endl;
    }

    int levelsCount[100]={0};
    countLevels(root, 0, levelsCount);

    int depth=calculateMaxDepth(root);
    cout<<"Number of nodes on levels: "<<endl;
    for (int i=0;i<depth;i++) {
        cout<<"Level "<<i<<": "<<levelsCount[i]<<" nodes"<<endl;
    }

    int target;
    cout<<"Enter the target code: ";
    cin>>target;
    if (findAndRemoveChildren(root, target)) {
        cout<<"Children removed"<<endl;
        cout<<"Tree after changes: "<<endl;
        showTech(root);
    }
    else {
        cout<<"Code not found"<<endl;
    }
    deleteTree(root);
    return 0;
}