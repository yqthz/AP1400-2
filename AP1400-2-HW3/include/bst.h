#ifndef BST_H
#define BST_H
#include<functional>
#include<cstddef>
#include<ostream>

class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;

        operator int() const {
            return value;
        }

        bool operator>(int value);
        
        bool operator>=(int value);
        
        bool operator<(int value);

        bool operator<=(int value);

        bool operator==(int value);

        friend std::ostream& operator<<(std::ostream& os, Node node);
    };

    BST() : root(nullptr) {}
    BST(const BST& bst);
    BST(std::initializer_list<int> init); 
    BST(BST&& bst);
    ~BST();
    BST& operator=(const BST& bst);
    BST& operator=(BST&& bst);
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value) const;
    Node** find_parrent(int value) const;
    Node** find_successor(int value) const;
    bool delete_node(int value);
    BST& operator++();
    BST operator++(int);
    friend std::ostream& operator<<(std::ostream& os, BST& bst);
private:
    Node* root;
};

#endif //BST_H