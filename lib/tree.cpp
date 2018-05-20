#include "tree.h"

bool cmp(code_tree::node* a, code_tree::node* b) {
    return a->amount > b->amount;
}

code_tree::code_tree(std::vector<std::pair<byte, ullong>> alphabet) {
    std::vector<node*> dict;
    for (auto p : alphabet) {
        dict.push_back(new node(p.first, p.second));
    }
    build_tree(dict);
}

code_tree::code_tree(std::map<byte, ullong> alphabet) {
    std::vector<node*> dict;
    for (auto p : alphabet) {
        dict.push_back(new node(p.first, p.second));
    }
    build_tree(dict);
}

code_tree::code_tree(std::map<byte, symbol_code> codes) {
    root = new node();
    for (auto p : codes) {
        specific_build(p);
    }
}

const symbol_code& code_tree::get_code(byte s) { return code[s]; }

code_tree::~code_tree() { del(root); }

void code_tree::del(node*& cur) {
    if (cur != nullptr) {
        del(cur->left);
        del(cur->right);
        delete cur;
        cur = nullptr;
    }
}

void code_tree::specific_build(std::pair<byte, symbol_code> p) {
    node* current = root;
    // iteration by small code
    for (size_t i = 0; i < p.second.size(); i++) {
        if ((p.second.get_code() >> (63 - i)) & 1) {
            if (current->right == nullptr) {
                current->right = new node();
            }
            current = current->right;
        } else {
            if (current->left == nullptr) {
                current->left = new node();
            }
            current = current->left;
        }
    }
    current->end = true;
    current->symbol = p.first;
}

void code_tree::dfs_assign(node* vertex, symbol_code code) {
    if (vertex == nullptr) return;
    if (vertex->end) {
        this->code[vertex->symbol] = code;
    } else {
        // 0 - to the left, 1 - to the right
        code.push_back(false);
        dfs_assign(vertex->left, code);
        code.pop_back();
        code.push_back(true);
        dfs_assign(vertex->right, code);
    }
}

void code_tree::build_tree(std::vector<node*> dict) {
    while (dict.size() > 1) {
        std::sort(dict.begin(), dict.end(), cmp);
        auto last = dict.back();
        dict.pop_back();
        auto prelast = dict.back();
        dict.pop_back();

        node* parent = new node();
        parent->left = prelast;
        parent->right = last;
        parent->amount = last->amount + prelast->amount;

        dict.push_back(parent);
    }
    if (dict.size() == 1) {
        if (dict[0]->end) {
            root = new node();
            root->left = dict[0];
        } else {
            root = dict[0];
        }
        dfs_assign(root, symbol_code());
    } else {
        root = nullptr;
    }
}
