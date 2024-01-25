#include <bits/stdc++.h>
using namespace std;

enum COLOR
{
    RED,
    BLACK
};

struct Node
{
public:
    int val;
    COLOR color;
    string contains;
    Node *left, *right, *parent;

    Node(int val, string s) : val(val), contains(s)
    {
        parent = left = right = nullptr;

        // Node is created during insertion
        // Node is red at insertion
        color = RED;
    }
    Node() : contains(""), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBT
{

public:
    Node *root;
    Node *TNULL;
    RBT()
    {
        cout << "RBT" << endl;
        TNULL = new Node;
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        cout << "RBT end" << endl;
    }
    int height(Node *x)
    {
        if (x == TNULL)
            return 0;
        else
        {
            int lheight = height(x->left);
            int rheight = height(x->right);

            if (lheight > rheight)
                return (lheight + 1);
            else
                return (rheight + 1);
        }
    }
    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
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
    void rightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insert(Node *z)
    {
        // cout << z->val << endl;
        Node *y = nullptr;
        Node *x = root;
        while (x != TNULL)
        {
            // cout << x->val << endl;
            y = x;
            if (z->val < x->val)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->val < y->val)
            y->left = z;
        else
            y->right = z;
        // z->left = nullptr;
        // z->right = nullptr;
        // z->color = RED;
        // cout << "here" << endl;
        if (z->parent == nullptr)
        {
            z->color = BLACK;
            return;
        }

        if (z->parent->parent == nullptr)
        {
            return;
        }

        insertFix(z);
    }

    void insertFix(Node *z)
    {
        // cout << "insertFix" << endl;
        while (z->parent != nullptr && z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node *y = z->parent->parent->right;
                if (y != nullptr && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    if (z->parent != nullptr)
                    {
                        z->parent->color = BLACK;
                        if (z->parent->parent != nullptr)
                        {
                            z->parent->parent->color = RED;
                            rightRotate(z->parent->parent);
                        }
                    }
                }
            }
            else
            {
                Node *y = z->parent->parent->left;
                if (y != nullptr && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    if (z->parent != nullptr)
                    {
                        z->parent->color = BLACK;
                        if (z->parent->parent != nullptr)
                        {
                            z->parent->parent->color = RED;
                            leftRotate(z->parent->parent);
                        }
                    }
                }
            }
            if (z == root)
            {
                break;
            }
        }
        root->color = BLACK;
    }

    void transplant(Node *u, Node *v)
    {
        cout << "transplant" << endl;
        if (u->parent == nullptr)
        {
            root = v;
            // if (v != nullptr)        // Ensure v is not null before accessing its parent
            // v->parent = nullptr; // Set v's parent to null
        }
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        // if (v != nullptr)          // Ensure v is not null before accessing its parent
        v->parent = u->parent; // Update v's parent
        cout << "transplant end" << endl;
    }

    Node *minimum(Node *x)
    {
        while (/*x != nullptr &&*/ x->left != TNULL)
            x = x->left;
        return x;
    }

    Node *find(int key)
    {
        Node *x = root;
        while (x != TNULL)
        {
            if (key < x->val)
                x = x->left;
            else if (key > x->val)
                x = x->right;
            else
                return x;
        }
        return nullptr;
    }

    void deleteFix(Node *x)
    {
        cout << "deleteFix" << endl;
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                Node *w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                Node *w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
        cout << "deleteFix end" << endl;
    }

    void Delete(Node *z)
    {
        if (root == TNULL || z == TNULL)
        {
            // Tree is empty or node to delete is null
            return;
        }
        cout << "deleting " << z->val << endl;

        Node *y = z;
        COLOR y_original_color = y->color;
        Node *x;

        if (z->left == TNULL)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        // Fix the RB tree properties
        if (y_original_color == BLACK)
            deleteFix(x);
    }

    string inOrderHelper(Node* node)
    {
        ostringstream string;
        if (node != TNULL)
        {
            inOrderHelper(node->left);
            string << node->val << "⇒"<<node->contains<<endl;
            inOrderHelper(node->right);
        }
    }

    int clear(Node *root)
    {
        if (root == TNULL)
            return 0;
        clear(root->left);
        clear(root->right);
        delete root;
        return 1;
    }

    std::string print(Node *root)
    {
        std::ostringstream string;
        if (root == TNULL)
        {
            return "";
        }
        else if (root->left == TNULL && root->right == TNULL)
        {
            string << root->val;
            string << "_";
            string << root->contains;
        }
        else if (root->left == TNULL && root->right != TNULL)
        {
            string << root->val;
            string << "_";
            string << root->contains;
            string << "(,";
            string << print(root->right);
            string << ")";
        }
        else if (root->left != TNULL && root->right == TNULL)
        {
            string << root->val;
            string << "_";
            string << root->contains;
            string << "(";
            string << print(root->left);
            string << ",";
            string << ")";
        }
        else if (root->left != TNULL && root->right != TNULL)
        {
            string << root->val;
            string << "_";
            string << root->contains;
            string << "(";
            string << print(root->left);
            string << ",";
            string << print(root->right);
            string << ")";
        }
        return string.str();
    }
};