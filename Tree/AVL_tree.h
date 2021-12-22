#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include "my_stack.h"

// description code.
struct Node
{
    int key;
    Node* left, * right;
    unsigned char height;

    Node(int k) { key = k; left = right = NULL; height = 1; } // simple constructor for a new node.
};

struct Queue
{
    int size = 0;
    Node** nodeArr = NULL;

    Queue(Node* node) { nodeArr = new Node * (node); size = 1; }
};

void pushBack(Queue&, Node*&);
Node* popFront(Queue&);
unsigned char height(Node*&);
char balance(Node*&);
void fixHeight(Node*&);
Node* rotateRight(Node*&);
Node* rotateLeft(Node*&);
Node* balancing(Node*&); // balancing node.
Node* insert(Node*&, const int&); // inserting a key into a tree.
Node* findNode(Node*&, const int&);
Node* findMinNode(Node*&);
Node* forgetMin(Node*&);
Node* remove(Node*&, const int&);
void infixTraverse(Node*&);
void postfixTraverse(Node*&);
void prefixTraverse(Node*&);
void BFS(Node*&);
// end of description code.


// definition code.
void pushBack(Queue& queue, Node*& node)
{
    if (queue.nodeArr == NULL) { queue.nodeArr = new Node * (node); queue.size++; }
    else
    {
        Node** tmp = queue.nodeArr;
        queue.nodeArr = new Node * [queue.size + 1];

        memmove_s(queue.nodeArr + 1, sizeof(Node*) * queue.size, tmp, sizeof(Node*) * queue.size);

        queue.nodeArr[0] = node;
        queue.size++;

        delete[] tmp;
    }
}

Node* popFront(Queue& queue)
{
    if (queue.nodeArr == NULL) return NULL;
    else if (queue.size == 1)
    {
        Node* node = queue.nodeArr[0];

        queue.nodeArr = NULL;
        queue.size = 0;

        delete[] queue.nodeArr;

        return node;
    }
    else
    {
        Node** tmp = queue.nodeArr;
        Node* node = queue.nodeArr[queue.size - 1];

        queue.nodeArr = new Node * [queue.size - 1];

        memmove_s(queue.nodeArr, sizeof(Node*) * (queue.size - 1), tmp, sizeof(Node*) * (queue.size - 1));

        queue.size--;

        delete[] tmp;

        return node;
    }
}

unsigned char height(Node*& current)
{
    return current ? current->height : 0; // yeah, it works with nullptr(in this case returns 0).
}

char balance(Node*& current)
{
    return current ? height(current->left) - height(current->right) : 0;
}

void fixHeight(Node*& current)
{
    unsigned char leftHeight = height(current->left);
    unsigned char rightHeight = height(current->right);
    current->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

Node* rotateRight(Node*& current)
{
    Node* root = current->left;
    current->left = root->right;
    root->right = current;

    fixHeight(current);
    fixHeight(root);

    return root;
}

Node* rotateLeft(Node*& current)
{
    Node* root = current->right;
    current->right = root->left;
    root->left = current;

    fixHeight(current);
    fixHeight(root);

    return root;
}

Node* balancing(Node*& current) // balancing node.
{
    fixHeight(current);

    if (balance(current) == -2) // if outweights the right subtree.
    {
        if (balance(current->right) > 0)
            current->right = rotateRight(current->right); // right-left rotation.
        return rotateLeft(current);
    }

    if (balance(current) == 2)  // if outweights the left subtree.
    {
        if (balance(current->left) < 0)
            current->left = rotateLeft(current->left);    // left-right rotation.
        return rotateRight(current);
    }

    return current; // balancing is not needed.
}

Node* insert(Node*& treeRoot, const int& key) // inserting a key into a tree.
{
    if (!treeRoot) return new Node(key);

    if (key < treeRoot->key)
        treeRoot->left = insert(treeRoot->left, key);
    else
        treeRoot->right = insert(treeRoot->right, key);

    return balancing(treeRoot);
}

Node* findNode(Node*& node, const int& key)
{
    while (true)
    {
        if (!node) return NULL;
        if (node->key == key) return node;
        if (node->key > key) node = node->left;
        if (node->key < key) node = node->right;
    }
}

Node* findMinNode(Node*& root)
{
    return root->left ? findMinNode(root->left) : root;
}

Node* forgetMin(Node*& root)
{
    if (!root->left) return root->right;
    else root->left = forgetMin(root->left);

    return balancing(root);
}

Node* remove(Node*& root, const int& key)
{
    if (!root) return NULL;

    else if (key < root->key) root->left = remove(root->left, key);

    else if (key > root->key) root->right = remove(root->right, key);

    else // if key == root->key
    {
        Node* left = root->left;
        Node* right = root->right;
        delete root;

        if (!right) return left;
        else
        {
            Node* min = findMinNode(right);
            min->right = forgetMin(right);
            min->left = left;

            return balancing(min);
        }
    }

    return balancing(root);
}

void prefixTraverse(Node*& root)
{
    if (!root)
    {
        std::cout << "What are you doing???" << std::endl;
        return;
    }

    std::cout << std::endl;
    MyStack<Node*> stack;

    stack.push(root);
    while (stack.isNotEmpty())
    {
        Node* node = stack.pop();
        std::cout << node->key << " ";
        if (node->right) stack.push(node->right);
        if (node->left)  stack.push(node->left);
    }
    std::cout << std::endl;
}

void infixTraverse(Node*& root)
{
    if (!root)
    {
        std::cout << "What are you doing???" << std::endl;
        return;
    }

    std::cout << std::endl;
    MyStack<Node*> stack;
    Node* node = root;

    while (stack.isNotEmpty() || node)
    {
        if (node)
        {
            stack.push(node);
            node = node->left;
        }
        else
        {
            node = stack.pop();
            std::cout << node->key << " ";
            node = node->right;
        }
    }
    std::cout << std::endl;
}

void postfixTraverse(Node*& root)
{
    if (!root)
    {
        std::cout << "What are you doing???" << std::endl;
        return;
    }

    std::cout << std::endl;
    MyStack<Node*> stack;
    Node* node = root;
    Node* lastVisited = NULL;

    while (stack.isNotEmpty() || node)
    {
        if (node)
        {
            stack.push(node);
            node = node->left;
        }
        else if (stack.peek() != NULL)
        {
            Node* peek = stack.peek();
            if ((peek->right) && (lastVisited != peek->right))
                node = peek->right;
            else
            {
                std::cout << peek->key << " ";
                lastVisited = stack.pop();
            }
        }
    }
    std::cout << std::endl;
}

void BFS(Node*& root)
{
    if (!root)
    {
        std::cout << "What are you doing???" << std::endl;
        return;
    }

    std::cout << std::endl;
    Queue queue(root);

    while (queue.size != 0)
    {
        Node* node = popFront(queue);
        std::cout << node->key << " ";

        if (node->left)
        {
            pushBack(queue, node->left);
        }

        if (node->right)
        {
            pushBack(queue, node->right);
        }
    }
    std::cout << std::endl;
}
// end of definition code.


#endif //AVL_TREE