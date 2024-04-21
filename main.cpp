#include <iostream>

using namespace std;

struct Tree {
    int inf;
    Tree *left;
    Tree *right;
};

Tree *addElement(Tree *tree, int inf) {

    Tree *nl, *pr, *ps;
    bool b;

    nl = new Tree;
    nl->inf = inf;
    nl->left = NULL;
    nl->right = NULL;

//    cout << tree << " ";
//    if (tree->inf == 0 && tree->right == NULL && tree->left == NULL) {
//        tree->inf = inf;
//        return tree;
//    }
    if (tree == NULL) {
        return nl;
    }

    ps = tree;

    while (ps != NULL) {
        pr = ps;
        b =  (inf < ps->inf);

        if (b) {
            ps = ps->left;
        } else {
            ps = ps->right;
        }
    }

    if (b) {
        pr->left = nl;
    } else {
        pr->right = nl;
    }

    return tree;

}

Tree *makeTree(int left, int right, int *mas) {
    Tree *ps;
    int m;

    if (left > right) {
        return NULL;
    }

    m = (left + right) / 2;

    ps = new Tree;
    ps->inf = mas[m];

    ps->left = makeTree(left, m-1, mas);
    ps->right = makeTree(m+1, right, mas);

    return ps;

}

void changeElements(Tree *tree, const Tree *treeMax, const Tree *treeMin, int max, int min) {
    if (tree == NULL) {
        return;
    }

    if (tree == treeMax) {
        tree->inf = min;
    }

    if (tree == treeMin) {
        tree->inf = max;
    }

    changeElements(tree->left, treeMax, treeMin, max, min);
    changeElements(tree->right, treeMax, treeMin, max, min);
}

void getElements(Tree *tree, Tree *&treeMax, Tree *&treeMin, bool first = true) {
    if (tree == NULL) return;
    if (first) return getElements(tree->left, treeMax, treeMin, false);

    if ((treeMax->inf == 0 && tree->right == NULL && tree->left == NULL) || treeMax->inf < tree->inf) {
        treeMax = tree;
    }
    if ((treeMin->inf == 0 && treeMin->right == NULL && treeMin->left == NULL) || treeMin->inf > tree->inf) {
        treeMin = tree;
    }

    getElements(tree->left, treeMax, treeMin, false);
    getElements(tree->right, treeMax, treeMin, false);
}

void symmetric(Tree *tree) {

    if (tree == NULL) {
        return;
    }

    symmetric(tree->left);
    cout << tree->inf << " ";
    symmetric(tree->right);
}

void straight(Tree *tree) {

    if (tree == NULL) {
        return;
    }

    cout << tree->inf << " ";
    straight(tree->left);
    straight(tree->right);
}

void reversive(Tree *tree) {

    if (tree == NULL) {
        return;
    }

    reversive(tree->left);
    reversive(tree->right);
    cout << tree->inf << " ";

}

Tree *deleteAllTree(Tree *p) {
    if (p == NULL) {
        return NULL;
    }

    deleteAllTree(p->left);
    deleteAllTree(p->right);

    delete p;
    p = NULL;
    return NULL;
}

void printAllChilds(Tree *tree) {

    if (tree == NULL) {
        return;
    }

    if (tree->right == NULL and tree->left == NULL) {
        cout << "\033[1;31m" << tree->inf << " ";
    }

    printAllChilds(tree->right);
    printAllChilds(tree->left);
}

void printBinaryTree(Tree* root, int level = 0, char branch = '-') {
    if (root) {
        printBinaryTree(root->right, level + 1, '/');
        for (int i = 0; i < level; i++) {
            std::cout << "    ";
        }
        std::cout << branch << "--" << root->inf << std::endl;
        printBinaryTree(root->left, level + 1, '\\');
    }
}

int main() {
    int mas[8] = {1, 2, 3, 4, 6, 7, 9, 13};
    Tree *tree = makeTree(0, 7, mas);
    Tree *treeMax = new Tree;
    Tree *treeMin = new Tree;

    cout << "\033[1;31m" << "symmetric: ";
    symmetric(tree);
    cout << endl;
    cout << "straight: ";
    straight(tree);
    cout << endl;
    cout << "reversive: ";
    reversive(tree);
    cout << endl << "\033[1;32m";
    printBinaryTree(tree);
    cout << endl;
    cout << "---------------" << endl << "\033[1;33m";
    getElements(tree, treeMax, treeMin);
    changeElements(tree, treeMax, treeMin, treeMax->inf, treeMin->inf);
    printBinaryTree(tree);
    printAllChilds(tree);
    deleteAllTree(tree);

    return 0;
}
