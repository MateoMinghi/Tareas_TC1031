#ifndef SPLAY_H_
#define SPLAY_H_

#include <string>
#include <sstream>

using namespace std;

template <class T> class SplayTree;

template <class T>
class Node {
private:
    T data;
    Node *left, *right, *parent;

    Node<T>* succesor();
    Node<T>* rot_right(Node<T>* current);
    Node<T>* rot_left(Node<T>* current);
public:
    Node(T newData) : data(newData), left(0), right(0), parent(0) {}

    Node<T>* add(T newData);
    Node<T>* find(T newData);
    Node<T>* remove(T newData);

    Node<T>* splay(Node<T>*, Node<T>*);
    void removeChilds();

    void print_tree(stringstream &output) const;
    void preorder(stringstream &output) const;
    void inorder(stringstream &output) const;

    friend class SplayTree<T>;
};

template <class T>
Node<T>* Node<T>::add(T newData) {
    if (newData < data) {
        if (left != 0) {
            return left->add(newData);
        } else {
            left = new Node<T>(newData);
            left->parent = this;
            return left;
        }
    } else {
        if (right != 0) {
            return right->add(newData);
        } else {
            right = new Node<T>(newData);
            right->parent = this;
            return right;
        }
    }
}

template <class T>
Node<T>* Node<T>::find(T newData) {
    if (newData == data) {
        return this;
    } else if (newData < data) {
        if (left == 0) {
            return this;
        } else {
            return left->find(newData);
        }
    } else {
        if (right == 0) {
            return this;
        } else {
            return right->find(newData);
        }
    }
}

template <class T>
Node<T>* Node<T>::succesor() {
    Node<T> *leftNode, *rightNode;
    leftNode = left;
    rightNode = right;

    if (right == 0 && left == 0) {
        return 0;
    }

    if (right == 0) {
        if (left != 0) {
            if (left->right) {
                right = left->right;
            }
            left = left->left;
        }
        return leftNode;
    }

    if (right->left == 0) {
        right = right->right;
        rightNode->right = 0;
        return rightNode;
    }

    Node<T> *predecessor, *successor;
    predecessor = right;
    successor = right->left;
    while (successor->left != 0) {
        predecessor = successor;
        successor = successor->left;
    }
    predecessor->left = successor->right;
    successor->right = 0;
    return successor;
}

template <class T>
Node<T>* Node<T>::remove(T targetValue) {
    Node<T> *successorNode, *targetNode;

    if (targetValue < data) {
        if (left != 0) {
            if (left->data == targetValue) {
                targetNode = left;
                successorNode = left->succesor();
                if (successorNode != 0) {
                    successorNode->left = targetNode->left;
                    successorNode->right = targetNode->right;
                    successorNode->parent = targetNode->parent;

                    if (successorNode->left)
                        successorNode->left->parent = successorNode;
                    if (successorNode->right)
                        successorNode->right->parent = successorNode;
                }
                left = successorNode;
                delete targetNode;
                return this;
            } else {
                return left->remove(targetValue);
            }
        } else {
            return this;
        }
    } else {
        if (right != 0) {
            if (right->data == targetValue) {
                targetNode = right;
                successorNode = right->succesor();
                if (successorNode != 0) {
                    successorNode->left = targetNode->left;
                    successorNode->right = targetNode->right;
                    successorNode->parent = targetNode->parent;

                    if (successorNode->left)
                        successorNode->left->parent = successorNode;
                    if (successorNode->right)
                        successorNode->right->parent = successorNode;
                }
                right = successorNode;

                delete targetNode;
                return this;
            } else {
                return right->remove(targetValue);
            }
        } else {
            return this;
        }
    }
}


template <class T>
void Node<T>::removeChilds() {
    if (left != 0) {
        left->removeChilds();
        delete left;
        left = 0;
    }
    if (right != 0) {
        right->removeChilds();
        delete right;
        right = 0;
    }
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* current) {
    while (current->parent != 0) {
        if (current->parent->data == root->data) {
            if (current->parent->left && current->parent->left->data == current->data) {
                rot_right(current->parent);
            } else {
                rot_left(current->parent);
            }
        } else {
            Node<T>* p = current->parent;
            Node<T>* g = p->parent;

            if (p->left && g->left &&
                current->data == p->left->data && p->data == g->left->data) {
                rot_right(g);
                rot_right(p);
            } else if (p->right && g->right &&
                current->data == p->right->data && p->data == g->right->data) {
                rot_left(g);
                rot_left(p);
            } else if (p->left && g->right &&
                current->data == p->left->data && p->data == g->right->data) {
                rot_right(p);
                rot_left(g);
            } else {
                rot_left(p);
                rot_right(g);
            }
        }
    }
    return current;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* current) {
    Node<T> *newParent = current->left;
    current->left = newParent->right;
    if (newParent->right)
        newParent->right->parent = current;

    newParent->right = current;

    newParent->parent = current->parent;
    current->parent = newParent;

    if (newParent->parent) {
        if (newParent->parent->left && newParent->parent->left->data == current->data)
            newParent->parent->left = newParent;
        else
            newParent->parent->right = newParent;
    }
    return newParent;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* current) {
    Node<T> *newParent = current->right;
    current->right = newParent->left;
    if (newParent->left)
        newParent->left->parent = current;

    newParent->left = current;

    newParent->parent = current->parent;
    current->parent = newParent;

    if (newParent->parent) {
        if (newParent->parent->left && newParent->parent->left->data == current->data)
            newParent->parent->left = newParent;
        else
            newParent->parent->right = newParent;
    }
    return newParent;
}



template <class T>
void Node<T>::print_tree(stringstream &output) const {
    if (parent != 0) {
        output << "\n node " << data;
        output << " parent " << parent->data;
    } else
        output << "\n root " << data;
    if (left != 0)
        output << " left " << left->data;
    if (right != 0)
        output << " right " << right->data;
    output << "\n";
    if (left != 0) {
        left->print_tree(output);
    }
    if (right != 0) {
        right->print_tree(output);
    }
}

template <class T>
void Node<T>::preorder(stringstream &output) const {
    output << data;
    if (left != 0) {
        output << " ";
        left->preorder(output);
    }
    if (right != 0) {
        output << " ";
        right->preorder(output);
    }
}

template <class T>
void Node<T>::inorder(stringstream &output) const {
    if (left != 0) {
        left->inorder(output);
    }
    if (output.tellp() != 1) {
        output << " ";
    }
    output << data;
    if (right != 0) {
        right->inorder(output);
    }
}

template <class T>
class SplayTree {
private:
    Node<T> *root;

public:
    SplayTree();
    ~SplayTree();

    bool empty() const;
    void removeAll();

    void add(T newData);
    bool find(T newData);
    void remove(T newData);

    string print_tree() const;
    string inorder() const;
    string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
    removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
    return (root == 0);
}

template <class T>
void SplayTree<T>::add(T newData) {
    if (root != 0) {
        Node<T>* added = root->add(newData);
        root = root->splay(root, added);
    } else {
        root = new Node<T>(newData);
    }
}

template <class T>
void SplayTree<T>::remove(T newData) {
    if (root != 0) {
        if (newData == root->data) {
            Node<T> *replacement = root->succesor();
            if (replacement != 0) {
                replacement->left = root->left;
                replacement->right = root->right;
                replacement->parent = 0;

                if (replacement->left)
                    replacement->left->parent = replacement;
                if (replacement->right)
                    replacement->right->parent = replacement;
            }
            delete root;
            root = replacement;
        } else {
            Node<T>* parent = root->remove(newData);
            root = root->splay(root, parent);
        }
    }
}

template <class T>
bool SplayTree<T>::find(T newData) {
    if (root != 0) {
        Node<T>* found = root->find(newData);
        root = root->splay(root, found);
        if (root->data == newData)
            return true;
    }
    return false;
}

template <class T>
void SplayTree<T>::removeAll() {
    if (root != 0) {
        root->removeChilds();
    }
    delete root;
    root = 0;
}

template <class T>
string SplayTree<T>::inorder() const {
    stringstream output;

    output << "[";
    if (!empty()) {
        root->inorder(output);
    }
    output << "]";
    return output.str();
}

template <class T>
string SplayTree<T>::preorder() const {
    stringstream output;

    output << "[";
    if (!empty()) {
        root->preorder(output);
    }
    output << "]";
    return output.str();
}

template <class T>
string SplayTree<T>::print_tree() const {
    stringstream output;

    if (!empty()) {
        root->print_tree(output);
    }

    return output.str();
}

#endif