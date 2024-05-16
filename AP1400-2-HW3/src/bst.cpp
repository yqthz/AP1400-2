#include "bst.h"
#include<queue>
#include<memory>


BST::Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {

}

BST::Node::Node() : value(0), left(nullptr), right(nullptr) { }

BST::Node::Node(const Node& node) : value(node.value), left(node.left), right(node.right) {
}

bool BST::Node::operator>(int value) {
    return this->value > value;
}


bool BST::Node::operator>=(int value) {
    return this->value >= value;
}


bool BST::Node::operator<(int value) {
    return this->value < value;
}

bool BST::Node::operator<=(int value) {
    return this->value <= value;
}

bool BST::Node::operator==(int value) {
    return this->value == value;
}

std::ostream& operator<<(std::ostream& os, BST::Node node) {
    os << &node << " " << node.left << " " << node.right << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, BST& bst) {
    BST::Node* root = bst.get_root();
    os << "***********************" << std::endl;
    std::queue<BST::Node*> q;
    q.push(root);
    while (!q.empty()) {
        BST::Node* t = q.front();
        q.pop();
        os << t << "       => value:" << t->value 
        << "           left:" << t->left 
        << "           right:" << t->right
        << std::endl; 
        if (t->left != nullptr) {
            q.push(t->left);
        }
        if (t->right != nullptr) {
            q.push(t->right);
        }
    }
    os << "binary search tree size: " << bst.length() << std::endl;
    os << "***********************" << std::endl;
    return os;
}

BST& BST::operator++() {
    bfs([](BST::Node*& node) {
        node->value += 1;
    });
    return *this;

}

BST BST::operator++(int) {
    BST bst{*this};
    bfs([](BST::Node*& node) {
        node->value += 1;
    });
    return bst;

}
BST::BST(std::initializer_list<int> init) {
    root = nullptr;
    for (int v : init) {
        add_node(v);
    }
}
BST::BST(const BST& bst) {
    std::vector<Node*> nodes;
    bst.bfs([&nodes](BST::Node*& node) {
        nodes.push_back(node);
    });
    root = nullptr;
    for (auto& node : nodes) {
        add_node(node->value);
    }

}

BST::BST(BST&& bst) {
    root = std::move(bst.root);
    bst.root = nullptr;
}
BST::~BST() {
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) {
        nodes.push_back(node);
    });
    for (auto& node : nodes) {
        delete node;
    }
}

BST& BST::operator=(const BST& bst) {
    if (this == &bst) {
        return *this;
    }
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) {
        nodes.push_back(node);
    });
    for (auto& node : nodes) {
        delete node;
    }
    root = nullptr;
    std::vector<Node*> nodes1;
    bst.bfs([&nodes1](BST::Node*& node) {
        nodes1.push_back(node);
    });
    for (auto& node : nodes1) {
        add_node(node->value);
    }
    return *this;

}

BST& BST::operator=(BST&& bst) {
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) {
        nodes.push_back(node);
    });
    for (auto& node : nodes) {
        delete node;
    }
    root = std::move(bst.root);
    bst.root = nullptr;
    return *this;

}


BST::Node*& BST::get_root() {
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) const {
    if (root == nullptr) {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* t = q.front();
        q.pop();
        func(t);
        if(t->left != nullptr) {
            q.push(t->left);
        }
        if (t->right != nullptr) {
            q.push(t->right);
        }
    }
}

size_t BST::length() const {
    size_t ans = 1;
    if (root == nullptr) {
        return 0;
    }

    Node* p = root;
    std::queue<Node*> q;
    q.push(p);
    while (!q.empty()) {
        Node* t = q.front();
        q.pop();
        if (t->left != nullptr) {
            q.push(t->left);
            ans++;
        }
        if (t->right != nullptr) {
            q.push(t->right);
     ;       ans++;
        }
    }
    return ans;
}

bool BST::add_node(int value) {
    if (find_node(value) != nullptr) {
        return false;
    }

    Node* p = root;
    if (root == nullptr) {
        root = new Node(value, nullptr, nullptr);
        return true;
    }
    while (!((p->left == nullptr && p->value > value) || (p->right == nullptr && p->value < value))) {
        if (p->value > value) {
            p = p->left;
        }
        else if (p->value < value) {
            p = p->right;
        }
    }
    if (p->left == nullptr && p->value > value) {
        p->left = new Node(value, nullptr, nullptr);
    }
    else if (p->right == nullptr && p->value < value) {
        p->right = new Node(value, nullptr, nullptr);
    }
    return true;
}

BST::Node** BST::find_node(int value) const {
    //Node* p = const_cast<Node*>(root);
    
    if (root == nullptr) {
        return nullptr;
    }

    if (root->value == value) {
      return const_cast<Node**>(&root);
    }

    Node* pre = root;
    Node* cur = root;

    while (cur != nullptr && cur->value != value) {
        if (cur->value > value) {
            pre = cur;
            cur = cur->left;
            if (cur != nullptr && cur->value == value) {
                return &(pre->left);
            }
        }
        else if (cur->value < value) {
            pre = cur;
            cur = cur->right;
            if (cur != nullptr && cur->value == value) {
                return &(pre->right);
            }
        }
    }
    if (cur == nullptr) {
        return nullptr;
    }
    return nullptr;
}

BST::Node** BST::find_parrent(int value) const {
    //Node** pre = const_cast<Node**>(&root);
    //Node** cur = const_cast<Node**>(&root);
    Node* ppre = root;
    Node* pre = root;
    Node* cur = root;
    if (root->value == value) {
        return nullptr;
    }
    if (root->left != nullptr && root->left->value == value) {
        return const_cast<Node**>(&root);
    }
    if (root->right != nullptr && root->right->value == value) {
        return const_cast<Node**>(&root);
    }

    while (cur != nullptr && cur->value != value) {
        if (cur->value > value) {
            ppre = pre;
            pre = cur;
            cur = cur->left;
            if (cur != nullptr && cur->value == value) {
                if (ppre->left == pre) {
                    return &(ppre->left);
                }
                else {
                    return &(ppre->right);
                }
            }
        }
        else if (cur->value < value) {
            ppre = pre;
            pre = cur;
            cur = cur->right;
            if (cur != nullptr && cur->value == value) {
                if (ppre->left == pre) {
                    return &(ppre->left);
                }
                else {
                    return &(ppre->right);
                }
            }
        }
    }
    return nullptr;
}

BST::Node** BST::find_successor(int value) const {
    Node** p = find_node(value);
    if ((*p)->left == nullptr && (*p)->right == nullptr) {
        return nullptr;
    }
    Node* pre = *p;
    Node* cur = *p;
    if (cur->left != nullptr) {
        pre = cur;
        cur = cur->left;
        while (cur->right != nullptr) {
            pre = cur;
            cur = cur->right;
        }
    } 
    else if (cur->right != nullptr) {
        pre = cur;
        cur = cur->right;
        while (cur->left != nullptr) {
            pre = cur;
            cur = cur->left;
        }
    }
    if (pre->left == cur) {
        return &(pre->left);
    }
    else if (pre->right == cur) {
        return &(pre->right);
    }
    return nullptr;
}

bool BST::delete_node(int value) {
    if (root->value == value) {
        Node** root_successor = find_successor(value);
        Node* t = *root_successor;
        Node** t1 = find_parrent(t->value);
        Node* t2 = *t1;
        root->value = t->value;
        if (t2->left == t) {
            t2->left = nullptr;
        }
        else if (t2->right == t) {
            t2->right = nullptr;
        }
        delete t;
        return true;
    }

    Node** p = find_node(value);
    if (p == nullptr) {
        return false;
    }

    Node** q = find_parrent(value);
    Node** successor = find_successor(value);

    Node* node = *p;
    Node* node_parrent = *q;
    if (successor == nullptr) {
        if (node_parrent->left == node) {
            node_parrent->left = nullptr;
        }
        else {
            node_parrent->right = nullptr;
        }
        delete node;
    }
    // only left-child or only right-child
    else if ((node->left != nullptr && node->right == nullptr) || (node->left == nullptr && node->right != nullptr)) {
        if (node_parrent->left == node) {
            if (node->left == nullptr && node->right == nullptr) {
              node_parrent->left = nullptr;
            }
            else if (node->left != nullptr) {
              node_parrent->left = node->left;
            }
            else {
              node_parrent->left = node->right;
            }
            delete node;
        }
        else {
          if (node->left == nullptr && node->right == nullptr) {
            node_parrent->right = nullptr;
          }
          else if (node->left != nullptr) {
            node_parrent->right = node->left;
          }
          else {
            node_parrent->right = node->right;
          }
          delete node;
        }

    }
    else {
        // both left-child and right-child
        Node* node_successor = *successor;
        Node** successor_parrent = find_parrent(node_successor->value);
        Node* t = *successor_parrent;
        node->value = node_successor->value;
        if (t->left == node_successor) {
            t->left = nullptr;
        }
        else if (t->right == node_successor) {
            t->right = nullptr;
        }
        delete node_successor;
    }
    
    return true;
}