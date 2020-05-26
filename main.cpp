#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void menjushka()
{
	cout << "1: Push." << endl;
	cout << "2: Pop." << endl;
	cout << "3: Print." << endl;
	cout << "4: Individual." << endl;
}

typedef struct tree
{
    int weight;
    int id;
    struct tree *left;
    struct tree *right;
} tree;

void push(tree* &radix, int id, int weight)
{
    if (radix == NULL)
    {
        tree* new_node = new tree;
        new_node->id = id;
        new_node->weight = weight;
        radix = new_node;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    if (radix)
    {
        if (id < radix->id)
            push(radix->left, id, weight);
        if (id > radix->id)
            push(radix->right, id, weight);
    }
}

tree* delet(tree* &radix, int id)
{
    if (radix == NULL)
    {
        cout << "There is no such element." << endl;
        cout << endl;
    }
    if (id < radix->id)
    {
        radix->left = delet(radix->left, id);
        return radix;
    }
    if (id >radix->id)
    {
        radix->right = delet(radix->right, id);
        return radix;
    }



    if (radix->left == NULL && radix->right == NULL)
    {
        tree* new_node = new tree;
        new_node = radix;
        radix = NULL;
        delete(new_node);
        return radix;
    }
    if (radix->left == NULL && radix->right != NULL)
    {
        tree* new_node = new tree;
        new_node = radix;
        radix = radix->right;
        delete(new_node);
        return radix;
    }
    if (radix->right == NULL && radix->left != NULL)
    {
        tree* new_node = new tree;
        new_node = radix;
        radix = radix->left;
        delete(new_node);
        return radix;
    }
    if (radix->right != NULL && radix->left != NULL)
    {
        tree* new_node = new tree;
        new_node = radix->left;
        while(new_node->right)
            new_node = new_node->right;
        radix->id = new_node->id;
        radix->weight = new_node->weight;
        delete(new_node);
        return radix;
    }
}

void show(tree* &radix, int n)
{
    if (radix)
    {
        show(radix->left, n + 1);
        cout << setw(3 * n) << radix->id << "(" << radix->weight << ")" << endl;
        show(radix->right, n + 1);
    }
}

int individ(tree* &radix)
{
    if (radix != NULL)
    {
        if (radix->weight == 0)
            return 1 + individ(radix->left) + individ(radix->right);
        else
            return 0 + individ(radix->left) + individ(radix->right);
    }
    else return 0;
}

int main()
{
    int i = 0;
    menjushka();
    cout << endl;
    tree *radix = NULL;
    for(i = 0; i < 7; i++)
        push(radix, rand() % 50 + 10, rand() % 3 - 1);
    int weight, id, s; s=0;
    while (1)
    {
		int of;
		cin >> of;
		switch (of)
		{
		    case(0):
		        return 0;
            case(1):
			    cout << "Id and weight: ";
			    cin >> id;
			    cin >> weight;
			    cout << endl;
			    push(radix, id, weight);
			    break;
            case(2):
			    cout << "Id: ";
			    cin >> id;
			    cout << endl;
			    delet(radix, id);
			    break;
            case(3):
			    show(radix, 1);
			    cout << endl;
			    break;
            case(4):
		        cout << individ(radix);
		        cout << endl;
		        break;
		}
	}
}
