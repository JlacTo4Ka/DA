#include <iostream>
#include <ostream>
#include <fstream>
#include <cstring>

using namespace std;

const int buffer_size = 257;

typedef struct Node
{
    char key[buffer_size];
    unsigned long long value;
    int height;
    Node* right;
    Node* left;

    Node(const char* key, unsigned long long value) {
        memcpy(this->key, key, buffer_size);
        this->value = value;
        height = 1;
        left = right = nullptr;
    }
} Node;

int height(Node* target)
{
    if (target) return target->height;
    else return 0;
}

int calculate_diff(Node *target)
{
    return height(target->right)-height(target->left);
}

void recalculate_height(Node *target)
{
    int left_height = height(target->left);
    int right_height = height(target->right);
    target->height = (left_height>right_height ? left_height : right_height) + 1;
}

size_t calc_count(Node* target)
{
    if (!target) {
        return 0;
    }
    if (!target->left && !target->right) {
        return 1;
    }
    return calc_count(target->left) + calc_count(target->right) + 1;
}

Node* right_rotate(Node* target)
{
    Node *target_child = target->left;
    target->left = target_child->right;
    target_child->right = target;
    recalculate_height(target);
    recalculate_height(target_child);
    return target_child;
}

Node* left_rotate(Node* target)
{
    Node *target_child = target->right;
    target->right = target_child->left;
    target_child->left = target;
    recalculate_height(target);
    recalculate_height(target_child);
    return target_child;
}

Node *rebalance(Node* target)
{
    recalculate_height(target);
    if (calculate_diff(target) == 2)
    {
        if (calculate_diff(target->right) < 0) {
            target->right = right_rotate(target->right);
        }
        return left_rotate(target);
    }
    if (calculate_diff(target) == -2)
    {
        if (calculate_diff(target->left) > 0) {
            target->left= left_rotate(target->left);
        }
        return right_rotate(target);
    }
    return target;
}

Node *insert_node(Node *target, char* key, unsigned long long value)
{
    if (!target) {
        return new Node(key, value);
    }
    if (strcmp(target->key, key) == 0) {
        return target;
    }
    if (strcmp(target->key, key) > 0) {
        target->left = insert_node(target->left, key, value);
    }
    else {
        target->right = insert_node(target->right, key, value);
    }
    return rebalance(target);
}

Node* find_min(Node *target)
{
    if (target->left) {
        return find_min(target->left);
    }
    else return target;
}

Node* delete_min(Node *target)
{
    if (!target->left) {
        return target->right;
    }
    target->left = delete_min(target->left);
    return rebalance(target);
}

Node* delete_node(Node* target, char* key)
{
    if (!target) {
        return nullptr;
    }
    if (strcmp(target->key, key) > 0) {
        target->left = delete_node(target->left, key);
    }
    else if (strcmp(target->key, key) < 0) {
        target->right = delete_node(target->right, key);
    }
    else
    {
        Node *left_child = target->left;
        Node *right_child = target->right;
        delete target;
        if (!right_child) {
            return left_child;
        }
        Node* min = find_min(right_child);
        min->right = delete_min(right_child);
        min->left=left_child;
        return rebalance(min);
    }
    return rebalance(target);
}

Node *get_node(Node* target, const string& key) {
    if (!target) {
        return nullptr;
    }
    if(target->key == key) {
        return target;
    }
    else if (target->key < key) {
        return get_node(target->right, key);
    }
    else {
        return get_node(target->left, key);
    }
}

enum cmd_commands{
    ADD,
    DELETE,
    GET,
};

cmd_commands resolve_cmd(string cmd) {
    if (cmd == "+") {
        return ADD;
    }
    if (cmd == "-") {
        return DELETE;
    }
    return GET;
}

void to_lower(char* target) {
    for(int i = 0; target[i] != 0; ++i) {
        target[i] = tolower(target[i]);
    }
}

int main() {
    char cmd[buffer_size];
    char arg[buffer_size];
    char second_arg[buffer_size];
    Node* root = nullptr;
    ofstream serialize_output;
    ifstream deserialize_input;
    while (cin >> cmd) {
        switch (resolve_cmd(cmd)) {
            case ADD:
                cin >> arg;
                cin >> second_arg;
                to_lower(arg);
                if (root == nullptr) {
                    root = new Node(arg, stoull(second_arg));
                    cout << "OK" << endl;
                } else {
                    if (get_node(root, arg)) {
                        cout << "Exist" << endl;
                        break;
                    }
                    root = insert_node(root, arg, stoull(second_arg));
                    cout << "OK" << endl;
                }
                break;
            case DELETE:
                cin >> arg;
                if (root == nullptr) {
                    cout << "NoSuchWord" << endl;
                } else {
                    to_lower(arg);
                    if (!get_node(root, arg)) {
                        cout << "NoSuchWord" << endl;
                        break;
                    }
                    root = delete_node(root, arg);
                    cout << "OK" << endl;
                }
                break;
            case GET:
                if (root == nullptr) {
                    cout << "NoSuchWord" << endl;
                } else {
                    to_lower(cmd);
                    Node* result = get_node(root, cmd);
                    if (result == nullptr) {
                        cout << "NoSuchWord" << endl;
                    } else {
                        cout << "OK: " << result->value << endl;
                    }
                }
                break;
        }
    }
    delete root;
    return 0;
}
