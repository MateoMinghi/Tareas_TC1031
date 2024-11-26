/*
 * Mateo Minghi Vega
 * TC1031
 * Prof. Benjamin
*/

#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include <string>
using namespace std;


template <class T> class BST;

//utilicé dos funciones como vimos en clase
template <class T>
class Node {
private:
    T value;
    Node *left, *right;
    Node<T>* succesor();
public:
    Node(T);
    Node(T, Node<T>*, Node<T>*);
    Node<T>* add(T);
    Node<T>* find(T);

    
    void inorder(string&) const; //para comprobar que estamos visitando correctamente
    void preorder(string&) const; //para comprobar que estamos visitando correctamente
    void postorder(string&) const; //para comprobar que estamos visitando correctamente
    void levelorder(string&) const; //para comprobar que estamos visitando correctamente
    int height() const;
    int whatlevelamI(T) const;
    bool findAncestors(T, string&) const;
    void printlevel(string&, int) const; //para pasar los test cases que piden un formato particular
    friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri)
    : value(val), left(le), right(ri) {}

template <class T>
Node<T>* Node<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            return left->add(val);
        } else {
            left = new Node<T>(val);
            return left;
        }
    } else {
        if (right != 0) {
            return right->add(val);
        } else {
            right = new Node<T>(val);
            return right;
        }
    }
}

template <class T>
Node<T>* Node<T>::find(T val) {
    if (val == value) {
        return this;
    }
    if (val < value) {
        if (left != 0) {
            return left->find(val);
        } else {
            return 0;
        }
    } else {
        if (right != 0) {
            return right->find(val);
        } else {
            return 0;
        }
    }
}

template <class T>
Node<T>* Node<T>::succesor() {
    Node<T> *le, *ri;
    le = left;
    ri = right;
    if (right == 0) {
        if (left != 0) {
            left = 0;
        }
        if (ri != 0) {
            ri->add(le);
            return ri;
        } else {
            return le;
        }
    }
    Node<T> *parent, *child;
    parent = this;
    child = right;
    while (child->left != 0) {
        parent = child;
        child = child->left;
    }
    if (parent != this) {
        parent->left = child->right;
        child->right = right;
    }
    if (le != 0) {
        child->add(le);
    }
    if (ri != 0) {
        ri->add(child);
    }
    return child;
}

template <class T>
bool Node<T>::findAncestors(T val, string& result) const {
    if (value == val) return true;
    
    if (val < value) {
        if (left != 0) {
            if (left->findAncestors(val, result)) {
                if (result.empty()) {
                    result = to_string(value);
                } else {
                    result = to_string(value) + " " + result;
                }
                return true;
            }
        }
    } else {
        if (right != 0) {
            if (right->findAncestors(val, result)) {
                if (result.empty()) {
                    result = to_string(value);
                } else {
                    result = to_string(value) + " " + result;
                }
                return true;
            }
        }
    }
    return false;
}

template <class T>
int Node<T>::height() const {
    int le = 0;
    int ri = 0;
    if (left != 0) {
        le = left->height() + 1;
    }
    if (right != 0) {
        ri = right->height() + 1;
    }
    if (le == 0 && ri == 0) {
        return 1;
    }
    return (le > ri ? le : ri);
}

template <class T>
void Node<T>::inorder(string &s) const {
    if (left != 0) {
        left->inorder(s);
    }
    if (s.size() != 0) {
        s += " ";
    }
    s += to_string(value);
    if (right != 0) {
        right->inorder(s);
    }
}

template <class T>
void Node<T>::preorder(string &s) const {
    if (s.size() != 0) {
        s += " ";
    }
    s += to_string(value);
    if (left != 0) {
        left->preorder(s);
    }
    if (right != 0) {
        right->preorder(s);
    }
}

template <class T>
void Node<T>::postorder(string &s) const {
    if (left != 0) {
        left->postorder(s);
    }
    if (right != 0) {
        right->postorder(s);
    }
    if (s.size() != 0) {
        s += " ";
    }
    s += to_string(value);
}

template <class T>
void Node<T>::levelorder(string& s) const {
    int h = height();
    for (int i = 1; i <= h; i++) {
        printlevel(s, i);
    }
}

template <class T>
void Node<T>::printlevel(string &s, int level) const {
    if (level == 1) {
        if (s.size() != 0) {
            s += " ";
        }
        s += to_string(value);
    } else {
        if (left != 0) {
            left->printlevel(s, level - 1);
        }
        if (right != 0) {
            right->printlevel(s, level - 1);
        }
    }
}



template <class T>
int Node<T>::whatlevelamI(T val) const {
    if (val == value) {
        return 1;
    }
    if (val < value) {
        if (left != 0) {
            return left->whatlevelamI(val) + 1;
        } else {
            return 0;
        }
    } else {
        if (right != 0) {
            return right->whatlevelamI(val) + 1;
        } else {
            return 0;
        }
    }
}

template <class T>
class BST{
private:
    Node<T> *root;
public:
    BST();
    
    void add(T);
    string visit();
    int height();
    string ancestors(T);
    int whatlevelamI(T);
};

template <class T>
BST<T>::BST() : root(0) {}



template <class T>
void BST<T>::add(T val) {
    if (root == 0) {
        root = new Node<T>(val);
    } else {
        root->add(val);
    }
}

template <class T>
string BST<T>::visit() {
    string preStr = "", inStr = "", postStr = "", levelStr = "";
    if (root != 0) {
        root->preorder(preStr);
        root->inorder(inStr);
        root->postorder(postStr);
        root->levelorder(levelStr);
    }
    string result = "[" + preStr + "]\n";
    result += "[" + inStr + "]\n";
    result += "[" + postStr + "]\n";
    result += "[" + levelStr + "]";
    return result;
}


template <class T>
int BST<T>::height() {
    if (root != 0) {
        return root->height();
    } else {
        return 0;
    }
}

template <class T>
string BST<T>::ancestors(T val) {
    string result = "";
    if (root != 0) {
        root->findAncestors(val, result);
    }
    return "[" + result + "]";
}

template <class T>
int BST<T>::whatlevelamI(T val) {
    if (root != 0) {
        return root->whatlevelamI(val);
    } else {
        return -1;
    }
}

#endif