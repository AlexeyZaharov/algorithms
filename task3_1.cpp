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
#include <stack>
#include <vector>

template <typename T>
struct node {
    node<T>* left;
    node<T>* right;
    int priority;
    T key;

    node() : left(nullptr), right(nullptr), priority(0), key() {}
};

template <typename T>
class tree {
private:
    node<T>* root;

    void delete_tree(node<T>* tree) {
        if (tree != nullptr) {
            delete_tree(tree->left);
            delete_tree(tree->right);
        }

        delete tree;
    }

    void delete_child_with_one_child(node<T>* parent, node<T>* child);
    void delete_child_with_two_child(node<T> *node_);

public:
    tree() : root(nullptr) {}

    void insert(const T& key);
    void remove(const T& key);
    bool find(const T& key);

    std::vector<T> pre_order();
    int find_max_depth();

    ~tree() {
        delete_tree(root);
    }
};

template <typename T>
std::vector<T> tree<T>::pre_order() {
    std::vector<T> vec;
    node<T>* cur = nullptr;
    std::stack<node<T>*> stack;
    stack.push(root);

    while (cur != nullptr || !stack.empty()){
        if (!stack.empty()){
            cur =stack.top();
            stack.pop();
        }
        while (cur != nullptr){

            vec.push_back(cur->key) ;
            if (cur->right != nullptr) stack.push(cur->right);
            cur=cur->left;
        }
    }

    return vec;
}

template <typename T>
void tree<T>::insert(const T &key) {
    node<T>* node_ = new node<T>;
    node_->key = key;

    if (root == nullptr) {
        root = node_;
        return;
    }

    node<T>* cur = root;

    while (cur->left != nullptr || cur->right != nullptr) {
        if (cur->key > key) {
            if (cur->left == nullptr) {
                break;
            }
            cur = cur->left;
        }
        else {
            if (cur->right == nullptr) {
                break;
            }
            cur = cur->right;
        }
    }

    if (cur->key <= key) {
        cur->right = node_;
    }
    else {
        cur->left = node_;
    }
}

template <typename T>
void tree<T>::delete_child_with_one_child(node<T>* parent, node<T>* child) {
    parent->key = child->key;
    parent->left = child->left;
    parent->right = child->right;

    delete child;
}

template <typename T>
void tree<T>::delete_child_with_two_child(node<T> *node_) {
    node<T>* parent = node_;
    node<T>* child = parent->right;

    while (child->left != nullptr) {
        parent = child;
        child = child->left;
    }

    if (parent == node_) {
        node_->right = child->right;
    }
    else {
        parent->left = child->right;
    }

    node_->key = child->key;

    delete child;
}

template <typename T>
void tree<T>::remove(const T &key){
    node<T>* node_= find(key);

    if (node_ != nullptr) {
        if (node_->left != nullptr && node_->right != nullptr) {
            delete_child_with_two_child(node_);
        }
        else {
            if (node_->left != nullptr) {
                delete_child_with_one_child(node_, node_->left);
            }
            else if (node_->right != nullptr){
                delete_child_with_one_child(node_, node_->right);
            }
            else {
                delete node_;
                node_ = nullptr;
            }
        }
    }
}

template <typename T>
bool tree<T>::find(const T &key){
    node<T>* cur = root;

    while (cur != nullptr) {
        if (cur->key == key) {
            return true;
        }
        else if (cur->key > key) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }

    return false;
}

template <typename T>
int tree<T>::find_max_depth() {
    std::vector<node<T>*> level;
    std::vector<node<T>*> vec;
    level.push_back(root);
    int maxDepth = 0;
    while(level.size() != 0) {
        for (int i = 0; i < level.size(); ++i) {
            if (level[i]->left != nullptr) {
                vec.push_back(level[i]->left);
            }
            if (level[i]->right != nullptr) {
                vec.push_back(level[i]->right);
            }
        }
        level.clear();
        level = vec;
        vec.clear();
        if (level.size() != 0) {
            ++maxDepth;
        }
    }
    return maxDepth;
}

template <typename T>
class dec_tree {
private:
    node<T>* root;
    void delete_tree();
    void insert(node<T>*& node_, const T& key, int priority);

public:
    dec_tree() : root(nullptr) {}

    void insert(const T& key, int priority);
    void split(node<T> *node_, const T& key, node<T> *&left, node<T> *&right);

    int find_max_depth();

    ~dec_tree() {
        delete_tree();
    }
};

template <typename T>
void dec_tree<T>::delete_tree() {
    std::vector<node<T>*> level;
    std::vector<node<T>*> vec;
    level.push_back(root);
    while(level.size() != 0) {
        for (int i = 0; i < level.size(); ++i) {
            if (level[i]->left != nullptr) {
                vec.push_back(level[i]->left);
            }
            if (level[i]->right != nullptr) {
                vec.push_back(level[i]->right);
            }
            delete(level[i]);
        }
        level.clear();
        level = vec;
        vec.clear();
    }
}

template <typename T>
void dec_tree<T>::split(node<T> *node_, const T& key, node<T> *&left, node<T> *&right) {
    if (!node_) {
        left = right = nullptr;
    } else {
        if ((*node_).key <= key) {
            split(node_->right, key, node_->right, right);
            left = node_;
        } else {
            split(node_->left, key, left, node_->left);
            right = node_;
        }
    }
}



template <typename T>
void dec_tree<T>::insert(node<T>*& node_, const T& key, int priority) {
    if (node_ == nullptr) {
        node_ = new node<T>;
        node_->key = key;
        node_->priority = priority;
        return;
    } else if (node_->priority < priority) {
        node<T> *left;
        node<T> *right;
        split(node_, key, left, right);
        if (node_ == root) {
            root = new node<T>;
            node_->key = key;
            node_->priority = priority;
            node_->left = left;
            node_->right = right;
        } else {
            node_ = new node<T>;
            node_->key = key;
            node_->priority = priority;
            node_->left = left;
            node_->right = right;
        }
        return;
    } else {
        if (node_->key > key) {
            insert(node_->left, key, priority);

        } else {
            insert(node_->right, key, priority);
        }
    }
}

template <typename T>
void dec_tree<T>::insert(const T& key, int priority) {
    insert(root, key, priority);
}

template <typename T>
int dec_tree<T>::find_max_depth() {
    std::vector<node<T>*> level;
    std::vector<node<T>*> vec;
    level.push_back(root);
    int maxDepth = 0;
    while(level.size() != 0) {
        for (int i = 0; i < level.size(); ++i) {
            if (level[i]->left != nullptr) {
                vec.push_back(level[i]->left);
            }
            if (level[i]->right != nullptr) {
                vec.push_back(level[i]->right);
            }
        }
        level.clear();
        level = vec;
        vec.clear();
        if (level.size() != 0) {
            ++maxDepth;
        }
    }
    return maxDepth;
}

int main() {
    int amount, key, priority;
    std::cin >> amount;
    std::cin >> key >> priority;

    tree<int> tree;
    tree.insert(key);

    dec_tree<int> dec_tree;
    dec_tree.insert(key, priority);

    for (int i = 1; i < amount; ++i) {
        std::cin >> key >> priority;
        tree.insert(key);
        dec_tree.insert(key, priority);
    }
    std::cout << tree.find_max_depth() - dec_tree.find_max_depth();

    return 0;
}

