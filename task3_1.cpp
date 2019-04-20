/*
Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное
поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два
дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.
*/

#include <iostream>
#include <vector>

using namespace std;

struct CNode {
    int data;
    int priority;
    CNode* left,* right;
    CNode(int Key, int Priority, CNode* Left, CNode* Right) {
        data = Key;
        priority = Priority;
        left = Left;
        right = Right;
    }
};

class BinTree {
public:
    BinTree(CNode* node) : root(node) {}
    void Insert(int key);
    int FindMaxDepth();
    void DeleteTree();
private:
    CNode* root;
};

void BinTree::DeleteTree() {
    vector<CNode*> level;
    vector<CNode*> vecForHelp;
    level.push_back(root);
    while(level.size() != 0) {
        for (int i = 0; i < level.size(); ++i) {
            if (level[i]->left != nullptr) {
                vecForHelp.push_back(level[i]->left);
            }
            if (level[i]->right != nullptr) {
                vecForHelp.push_back(level[i]->right);
            }
            delete(level[i]);
        }
        level.clear();
        level = vecForHelp;
        vecForHelp.clear();
    }
}

void BinTree::Insert(int key) {
    if (root == nullptr) {
        root = new CNode(key, 0, nullptr, nullptr);
        return;
    }
    CNode* current = root;
    while(true) {
        if (key >= current->data) {
            if (current->right == nullptr) {
                current->right = new CNode(key, 0, nullptr, nullptr);
                return;
            } else {
                current = current->right;
            }
        } else {
            if (current->left == nullptr) {
                current->left = new CNode(key, 0, nullptr, nullptr);
                return;
            } else {
                current = current->left;
            }
        }
    }
}

int BinTree::FindMaxDepth() {
    vector<CNode*> level;
    vector<CNode*> vecForHelp;
    level.push_back(root);
    int maxDepth = 0;
    while(level.size() != 0) {
        for (int i = 0; i < level.size(); ++i) {
            if (level[i]->left != nullptr) {
                vecForHelp.push_back(level[i]->left);
            }
            if (level[i]->right != nullptr) {
                vecForHelp.push_back(level[i]->right);
            }
        }
        level.clear();
        level = vecForHelp;
        vecForHelp.clear();
        if (level.size() != 0) {
            ++maxDepth;
        }
    }
    return maxDepth;
}

class DecTree {
public:
    DecTree(CNode* node) : root(node) {}
    
    void DecInsert(CNode*& node, int key, int priority);
    void Split(CNode* node, int key, CNode*& left, CNode*& right);
    void DeleteTree();
    
    CNode* GetRoot() {
        return root;
    }
    
    int FindMaxDepth();
private:
    CNode* root;
};

void DecTree::DeleteTree() {
    vector<CNode*> level;
    vector<CNode*> vecForHelp;
    level.push_back(root);
    while(level.size() != 0) {
        for (int i = 0; i < level.size(); ++i) {
            if (level[i]->left != nullptr) {
                vecForHelp.push_back(level[i]->left);
            }
            if (level[i]->right != nullptr) {
                vecForHelp.push_back(level[i]->right);
            }
            delete(level[i]);
        }
        level.clear();
        level = vecForHelp;
        vecForHelp.clear();
    }
}

void DecTree::Split(CNode* node, int key, CNode*& left, CNode*& right) {
    if (!node) {
        left = right = nullptr;
    } else {
        if ((*node).data <= key) {
            Split(node->right, key, node->right, right);
            left = node;
        } else {
            Split(node->left, key, left, node->left);
            right = node;
        }
    }
}

void DecTree::DecInsert(CNode*& node, int key, int priority) {
    if (node == nullptr) {
        node = new CNode(key, priority, nullptr, nullptr);
        return;
    }
    else if(node->priority < priority) {
        CNode* Left;
        CNode* Right;
        Split (node, key, Left, Right);
        if (node == root) {
            root = new CNode (key, priority, Left, Right);
        } else {
            node = new CNode(key, priority, Left, Right);
        }
        return;
    } else{
        if (node->data > key) {
            DecInsert(node->left, key, priority);

        } else {
            DecInsert(node->right, key, priority);
        }
    }
}

int DecTree::FindMaxDepth() {
    vector<CNode*> level;
    vector<CNode*> vecForHelp;
    level.push_back(root);
    int maxDepth = 0;
    while(level.size() != 0) {
        for (int i = 0; i < level.size(); ++i) {
            if (level[i]->left != nullptr) {
                vecForHelp.push_back(level[i]->left);
            }
            if (level[i]->right != nullptr) {
                vecForHelp.push_back(level[i]->right);
            }
        }
        level.clear();
        level = vecForHelp;
        vecForHelp.clear();
        if (level.size() != 0) {
            ++maxDepth;
        }
    }
    return maxDepth;
}

int main() {
    int amount, key, priority;
    cin >> amount;
    cin >> key >> priority;
    CNode* binnode = new CNode(key, 0, nullptr, nullptr);
    CNode* decnode = new CNode(key, priority, nullptr, nullptr);
    BinTree tree(binnode);
    DecTree decTree(decnode);
    for (int i = 1; i < amount; ++i) {
        cin >> key >> priority;
        tree.Insert(key);
        decnode = decTree.GetRoot();
        decTree.DecInsert(decnode, key, priority);
    }
    cout << tree.FindMaxDepth() - decTree.FindMaxDepth();
    tree.DeleteTree();
    decTree.DeleteTree();
    return 0;
}
