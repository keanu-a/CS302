// binTree header file

#include <iostream>
#include <vector>

class binTree {

    public:
        struct binTreeNode {
            bool apple;
            binTreeNode * left;
            binTreeNode * right;
        };
        binTree ();
        binTree(std::vector<bool>);
        ~binTree ();
        int minTime ();

    private:
        void destroyTree(binTreeNode *);
        void buildTree(binTreeNode * r, std::vector<bool>, int);
        int minTime(binTreeNode * r, int);
        binTreeNode * root;
};

// --------------------
// -- PUBLIC MEMBERS --
// ------------ -------
binTree::binTree() {
    root = nullptr;
}

binTree::binTree(std::vector<bool> apples) {
    // Allocating a node to the root
    root = new binTreeNode;

    // Setting fields of root
    root->apple = apples[0];
    root->left = nullptr;
    root->right = nullptr;

    buildTree(root, apples, 0);
}

binTree::~binTree() {
    destroyTree(root);
}

int binTree::minTime() {
    return minTime(root, 0);
}

// ---------------------
// -- PRIVATE MEMBERS --
// ---------------------
void binTree::destroyTree(binTreeNode * r) {

    if (r == nullptr) { return; }

    destroyTree(r->left);
    destroyTree(r->right);

    delete r;
    r = nullptr;

    return;
}

void binTree::buildTree(binTreeNode * r, std::vector<bool> apples, int i) {

    int leftIndex, rightIndex;

    leftIndex = (i * 2) + 1;
    if (leftIndex >= apples.size()) { return; } // Base case

    // Allocating left node
    r->left = new binTreeNode;

    // Setting left child
    r->left->apple = apples[leftIndex];
    r->left->left = nullptr;
    r->left->right = nullptr;

    rightIndex = (i * 2) + 2;
    if (rightIndex >= apples.size()) { return; } // Base case

    // Allocating right node
    r->right = new binTreeNode;

    // Setting right child
    r->right->apple = apples[rightIndex];
    r->right->left = nullptr;
    r->right->right = nullptr;

    // Recursive calls to both sides of the tree
    buildTree(r->left, apples, leftIndex);
    buildTree(r->right, apples, rightIndex);

    return;
}

int binTree::minTime(binTreeNode * r, int time) {

    // USING POSTORDER TRAVERSAL
    int left, right;

    // Base Case
    if (r == nullptr) { return 0; }

    // Since postorder, find left side
    left = minTime(r->left, time + 1);

    // Depending on left side, find right side
    if (left == 0) { // left = 0
        right = minTime(r->right, time + 1);

        if (right == 0) { // left = 0 and right = 0
            if (r->apple == true) { return time + 1; }
            else { return 0; }
        }
        else { // left = 0 and right > 0  
            if (r->apple == true || r != root) { return right + 1; }
            else { return right; }
        }
    }
    else { // left > 0
        right = minTime(r->right, left + 1);

        if (right == 0) { // left > 0 and right = 0   
            if (r->apple == true || r != root) { return left + 1; }
            else { return left; }
        }
        else { // left > 0 and right > 0  
            if (r->apple == true || r != root) { return right + 1; }
            else { return right; }
        }
    }
}
