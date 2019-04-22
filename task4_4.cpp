/*
4_1. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая,
то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце –
самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного
роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего
солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n).
*/

#include <iostream>
#include <algorithm>
 
#include <iostream>
#include <algorithm>

using namespace std;

class node {
    int key;
    int height;
    int number_of_children;
    node* left;
    node* right;

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

public:
    node(int key_) {
        key = key_;
        height = 1;
        number_of_children = 1;
        left = nullptr;
        right = nullptr;
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

int main()
{
    int n = 0;
    cin >> n;

    node* root = nullptr;
    int position = 0;
    int cmd = 0;
    int height = 0;
    int second_value = 0;

    for (int i = 0; i < n; i++) {
        cin >> cmd >> second_value;
        if (cmd == 1) {
            root = root->add(root, second_value);
            position = 0;
            root->soldier_pos(root, second_value, position);
            cout << position << endl;
        }
        else {
            root->define_height(root, second_value, height);
            root = root->delete_node(root, height);
        }
    }

    delete root;
    return 0;
}
