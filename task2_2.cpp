/*Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.
Выведите элементы в порядке pre-order (сверху вниз).
*/

#include <iostream>
#include <stack>
#include <vector>

template <typename T>
struct node {
    node<T>* left;
    node<T>* right;
    T key;

    node() : left(nullptr), right(nullptr), key() {}
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

int main() {
    int N;
    tree<int> my_tree;
    std::cin >> N;
    int num;
    for (int i=0; i<N; i++)
    {
        std::cin >> num;
        my_tree.insert(num);
    }

    std::vector<int> vec = my_tree.pre_order();

    for (auto& i : vec) {
        std::cout << i << " ";
    }

    return 0;
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
