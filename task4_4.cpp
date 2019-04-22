/*
4_4. Скользящий максимум.
Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер 
некоторого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n.
Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне.

Скорость работы O(n log n), память O(n).

Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n строк со значением каждого элемента. Затем вводится k  - размер окна.

Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения окна.
*/
#include <iostream>
#include <algorithm>
 
using namespace std;
 
struct node {
    int key;
    int height;
    int number_of_children;
    node* left;
    node* right;
 
    node(int getkey) {
        key = getkey;
        height = 1;
        number_of_children = 1;
        left = nullptr;
        right = nullptr;
    }
 
    ~node() {
        if (left != nullptr) {
            delete left;
        }
        if (right != nullptr) {
            delete right;
        }
    }
};
 
int node_height(node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    return tree->height;
}
 
int num_children(node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    return tree->number_of_children;
}
 
int b_node(node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    return (node_height(tree->right) - node_height(tree->left));
}
 
void update_children(node* tree) {
    if (tree == nullptr) {
        return;
    }
    else {
        tree->number_of_children = 1;
        if (tree->right != nullptr) {
            tree->number_of_children += tree->right->number_of_children;
        }
        if (tree->left != nullptr) {
            tree->number_of_children += tree->left->number_of_children;
        }
    }
}
 
void update_height(node* tree) {
    if (tree == nullptr) {
        tree->height = 1;
    }
    tree->height = 1 + max(node_height(tree->right), node_height(tree->left));
}
 
node* small_left(node* tree) {
    node* tmp = tree->right;
    tree->right = tmp->left;
    tmp->left = tree;
    update_height(tree);
    update_children(tree);
    update_height(tmp);
    update_children(tmp);
    return tmp;
}
 
node* small_right(node* tree) {
    node* tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;
    update_height(tree);
    update_children(tree);
    update_height(tmp);
    update_children(tmp);
    return tmp;
}
 
node* balance(node* tree) {
    update_height(tree);
    update_children(tree);
    if (tree == nullptr) {
        return tree;
    }
    if (b_node(tree) == 2) {
        if (b_node(tree->right) < 0) {
            tree->right = small_right(tree->right);
        }
        return small_left(tree);
    }
 
    if (b_node(tree) == -2) {
        if (b_node(tree->left) > 0) {
            tree->left = small_left(tree->left);
        }
        return small_right(tree);
    }
    return tree;
}
 
node* add(node* tree, int key) {
    if (tree == nullptr) {
        return new node(key);
    }
    if (key < tree->key) {
        tree->left = add(tree->left, key);
    }
    else {
        tree->right = add(tree->right, key);
    }
    return balance(tree);
}
 
node* f_min(node* tree) {
    if (tree->left == nullptr) {
        return tree;
    }
    else {
        return f_min(tree->left);
    }
}
 
node* del_min(node* tree) {
    if (tree->left == 0) {
        return tree->right;
    }
    tree->left = del_min(tree->left);
    return balance(tree);
}
 
void define_height(node* tree, int position, int& height) {
    if (position == num_children(tree->right)) {
        height = tree->key;
    }
    else if (position > num_children(tree->right)) {
        define_height(tree->left, position - num_children(tree->right) - 1, height);
    }
    else {
        define_height(tree->right, position, height);
    }
}
 
node* delete_node(node* tree, int key) {
    if (tree == nullptr) {
        return nullptr;
    }
    if (key < tree->key) {
        tree->left = delete_node(tree->left, key);
    }
    else if (key > tree->key) {
        tree->right = delete_node(tree->right, key);
    }
    else {
        node* r = tree->right;
        node* l = tree->left;
        tree->left = nullptr;
        tree->right = nullptr;
        delete tree;
        if (r == nullptr) {
            return l;
        }
        else {
            node* min = f_min(r);
            min->right = del_min(r);
            min->left = l;
            return balance(min);
        }
    }
    return balance(tree);
}
 
void soldier_pos(node* tree, int height, int& counter) {
    if (height == tree->key) {
        counter += num_children(tree->right);
    }
    if (height > tree->key) {
        soldier_pos(tree->right, height, counter);
    }
    if (height < tree->key) {
        if (tree->right != nullptr) {
            counter += num_children(tree->right) + 1;
            soldier_pos(tree->left, height, counter);
        }
        else {
            counter += 1;
            soldier_pos(tree->left, height, counter);
        }
    }
};
 
int main()
{
    int n = 0;
    cin >> n;
 
    node* root = 0;
    int position = 0;
    int cmd = 0;
    int height = 0;
    int second_value = 0;
 
    for (int i = 0; i < n; i++) {
 
        cin >> cmd >> second_value;
        if (cmd == 1) {
            root = add(root, second_value);
            position = 0;
            soldier_pos(root, second_value, position);
            cout << position << endl;
        }
        else {
            define_height(root, second_value, height);
            root = delete_node(root, height);
        }
    }
 
    delete root;
    return 0;
}
