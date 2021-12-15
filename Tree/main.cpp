#include <iostream>
#include "AVL_tree.h"

using namespace std;

int main(int argc, char* argv[])
{
    Node* ptrTree = NULL;

    cout << "Please, enter number of nodes: ";
    int count; cin >> count;
    cout << endl;

    for (int i = 0; i < count; i++)
    {
        cout << "Please, enter " << i + 1 << " key for node: ";
        int key; cin >> key;
        cout << endl;

        ptrTree = insert(ptrTree, key);
    }

    cout << "Your infixTraverse(LKP, sorted list): ";
    infixTraverse(ptrTree);
    cout << endl;

    cout << "Your prefixTraverse(KLP): ";
    prefixTraverse(ptrTree);
    cout << endl;

    cout << "Your postfixTraverse(LPK): ";
    postfixTraverse(ptrTree);
    cout << endl;

    cout << "Your breadth-first search(BFS): ";
    BFS(ptrTree);
    cout << endl;

    system("Pause");

    printf("smth\n");

    return 0;
}