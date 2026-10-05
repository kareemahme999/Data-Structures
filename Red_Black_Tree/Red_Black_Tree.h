//
//  RedBlackTree.h
//  Red-Black-tree
//
//  Created by Kareem Ahmed on 2026-10-5.
//

#ifndef Red_Black_Tree_h
#define Red_Black_Tree_h
#include <iostream>




enum Color { RED, BLACK };

class Node {
    friend class RedBlackTree;
    private:
        int data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(int val){
            this->data = val;
            this->color = RED;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }

};


class RedBlackTree {
    private:
        Node* root;

    //  left rotation
    void leftRotate(Node* x) {

        if (x == nullptr || x->right == nullptr)
            return;

        Node* y = x->right;

        x->right = y->left;

        if (y->left != nullptr)

            y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == nullptr)

            root = y;

        else if (x == x->parent->left)
            x->parent->left = y;

        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    //  right rotation
    void rightRotate(Node* y) {

        if (y == nullptr || y->left == nullptr)
            return;

        Node* x = y->left;


        y->left = x->right;

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)

            y->parent->left = x;

        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }




    // fix violations after inserting a node
    void fixInsert(Node* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    // if uncle is black z inner child (tringle)
                    if (z == z->parent->right) { 

                        z = z->parent;

                        leftRotate(z);
                    }
                    //if uncle is black z outer child (line)
                    z->parent->color = BLACK;

                    z->parent->parent->color = RED;

                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                
                // if  uncle is red
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } 
                // if uncle is black (tringle)
                else {
                    //right rotation
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        // first case
        root->color = BLACK;
    }





// Transplant function used in deletion
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    
//    delete a node
    void deleteNode(Node* z) {
        if (z == nullptr)
            return;

        Node* y = z;
        Node* x = nullptr;
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != nullptr)
                    x->parent = y; // Check if x is not nullptr before assigning parent
            } else {
                if (x != nullptr)
                    x->parent = y->parent; // Check if x and y->parent are not nullptr before assigning parent
                transplant(y, y->right);
                if (y->right != nullptr)
                    y->right->parent = y; // Check if y->right is not nullptr before assigning parent
                y->right = z->right;
                if (y->right != nullptr)
                    y->right->parent = y; // Check if y->right is not nullptr before assigning parent
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr)
                y->left->parent = y; // Check if y->left is not nullptr before assigning parent
            y->color = z->color;
        }

        if (y_original_color == BLACK && x != nullptr) // Check if x is not nullptr
            fixDelete(x);

        delete z; // Free memory allocated for the deleted node
    }


    // Function to fix violations after deleting a node
    void fixDelete(Node* x) {
        while (x != root && x != nullptr && x->color == BLACK) {

            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {

                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {

                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) {

                        if (w->left != nullptr)

                            w->left->color = BLACK;

                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;

                    x->parent->color = BLACK;

                    if (w->right != nullptr)

                        w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;

                if (w->color == RED) {

                    w->color = BLACK;
                    x->parent->color = RED;

                    rightRotate(x->parent);


                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) {

                        if (w->right != nullptr)

                            w->right->color = BLACK;

                        w->color = RED;

                        leftRotate(w);

                        w = x->parent->left;

                    }
                    w->color = x->parent->color;

                    x->parent->color = BLACK;

                    if (w->left != nullptr)

                        w->left->color = BLACK;
                        
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr)
            x->color = BLACK;
    }

    // find the minimum node in a subtree (successor)
    Node* minimum(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // print the tree structure (in-order traversal)
    void printHelper(Node* root, int space) {
        constexpr int COUNT = 5;
        if (root == nullptr)
            return;
        space += COUNT;
        printHelper(root->right, space);
        std::cout << std::endl;
        for (int i = COUNT; i < space; i++)
            std::cout << " ";
        std::cout << root->data << "(" << ((root->color == RED) ? "RED" : "BLACK") << ")" << std::endl;
        printHelper(root->left, space);
    }
    //search
    Node* findNode(int val) const {
        Node* cur = root;
        while (cur != nullptr) {
            if (val < cur->data)
                cur = cur->left;
            else if (val > cur->data)
                cur = cur->right;
            else
                return cur;     
        }
        return nullptr;         
    }

    public:
    RedBlackTree() : root(nullptr) {}

    // insert a node
    void insert(int val) {
        Node* newNode = new Node(val);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;
        if (y == nullptr)
            root = newNode;
        else if (newNode->data < y->data)
            y->left = newNode;
        else
            y->right = newNode;

        fixInsert(newNode);
    }

    // delete a node by value
    void remove(int val) {
        Node* z = root;
        while (z != nullptr) {
            if (val < z->data)
                z = z->left;
            else if (val > z->data)
                z = z->right;
            else {
                deleteNode(z);
                return;
            }
        }
        std::cout << "Node with value " << val << " not found in the tree." << std::endl;
    }

    bool search(int val) const {
    return findNode(val) != nullptr;
}

// serch and print the node's color and parent information
void searchAndPrint(int val) const {
    Node* n = findNode(val);
    if (n == nullptr) {
        std::cout << val << " not found.\n";
        return;
    }
    std::cout << val << " found. Color: " << (n->color == RED ? "RED" : "BLACK");
    if (n->parent == nullptr)
        std::cout << ", it is the root.\n";
    else
        std::cout << ", parent = " << n->parent->data<< (n == n->parent->left ? " (left child)\n" : " (right child)\n");
}

    // print the tree structure
    void printTree() {
        printHelper(root, 0);
    }
};

#endif