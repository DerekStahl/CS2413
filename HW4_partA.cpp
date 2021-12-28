#include <iostream>
using namespace std;
// In this project, implement an AVL tree with one function
// -- AVL_Insert: insert a new node into AVL tree 
//
// In the main function, we will insert 10 nodes into AVL 
// Then, we will enumarate these nodes based on in-order traverse 
// The enumeration function has been implemented for you
// 
// Some functions are provided. You don't have to use them. 
class Node {
public:
    int SID = 0;
    Node* left = NULL;
    Node* right = NULL;
    Node* parent = NULL;
    int height = -1;
};
class AVL {
public:
    Node* GetRoot(); // return root node pointer; not really used in testing 
    void AVL_Enumerate(); // enumerate nodes based on in-order traverse 
    void AVL_Insert(Node* x); // insert a new node x into AVL tree 
    int get_bf(Node* x);  //this returns the balance factor of the AVL tree
    int get_height(Node* x);    //returns the height value stored for this node
private:
    Node* root = NULL;
};

void enumerate(Node* ptr) { // in-order traverse 
    if (ptr->left != NULL) {
        enumerate(ptr->left);
    }
    cout << ptr->SID << ' ';
    if (ptr->right != NULL) {
        enumerate(ptr->right);
    }
}
void AVL::AVL_Enumerate() {
    enumerate(root);
}
int depth(Node* ptr) { // measure depth of a node 
    int counter = 0;
    while (ptr->parent != NULL) {
        ptr = ptr->parent;
        counter++;
    }
    return counter;
}

int isRoot(Node* ptr) { // check if node is root or not
    if (ptr->parent == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}
int isLeaf(Node* ptr) { // check if node is leaf or not
    if (ptr->left == NULL && ptr->right == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}
Node* insert(Node* root, Node* x) { // insert a node to a tree with root
    if (root == NULL) {
        root = x;
    }
    else {
        if (x->SID <= root->SID) {
            root->left = insert(root->left, x);
        }
        else {
            root->right = insert(root->right, x);
        }
    }
    return root;
}
int findmax(Node* root) { // find max node from a tree with root 
    if (root->right == NULL) {
        return root->SID;
    }
    else {
        return findmax(root->right);
    }
}


Node* rotation_counterclock(Node* root) { // rotate tree at root counter clockwise 
    Node* temp = root->right;
    if (root->right->left != NULL) {
        root->right = root->right->left;
    }
    temp->left = root;
    root = temp;
    return root;
}

Node* rotation_clock(Node* root) { // rotate tree at root clockwise 
    Node* temp = root->left;
    if (root->left->right != NULL) {
        root->left = root->left->right;
    }
    temp->right = root;
    root = temp;
    return root;
}

int AVL::get_height(Node* x) {  //return the height of a node

    if (x == NULL) {
        return 0;
    }

    else {
        return x->height;
    }
}

int AVL::get_bf(Node* root) {   //returns the balance factor of the tree, the values are stored in the first node on either side of the root

    if (root == NULL || ((root->left == NULL) && (root->right == NULL))) {  //if there are no values or there is only a root value
        return 0;
    }

    else {
        return get_height(root->left) - get_height(root->right);
    }
}


void AVL::AVL_Insert(Node* x) {
    
    int balance_fact;   //used to keep track of the balance factor
    if (root == NULL) { //if there is no root, assign the node to the root
        root = x;
    }

    else {
        insert(root, x);    //insert the node into the AVL tree


        if (x->SID <= root->SID) {
            root->left->height = depth(x);   //set the height for left side of branch
        }
        else {
            root->right->height = depth(x); //set the height for right side of branch
        }

        balance_fact = get_bf(root);    //get the balance factor of this node

        if (balance_fact > 1 || balance_fact < -1) {

            //----------------------------------------------------------------------------------------------------------

            if (balance_fact > 1 && x->SID < x->parent->SID && x->parent->parent->right == NULL) {  // Left Left Case
                rotation_clock(x->parent->parent);
            }
            else if (balance_fact > 1 && x->SID < x->parent->SID && x->parent->parent->right != NULL) {
                rotation_clock(root);
            }
            else {
                ;//do nothing
            }

            //----------------------------------------------------------------------------------------------------------

            if (balance_fact < -1 && x->SID > x->parent->SID && x->parent->parent->left == NULL) {// Right Right Case
                rotation_counterclock(x->parent->parent);
            }
            else if (balance_fact > -1 && x->SID > x->parent->SID && x->parent->parent->left != NULL) {
                rotation_counterclock(root);
            }
            else {
                ;//do nothing
            }

            //----------------------------------------------------------------------------------------------------------

            if (balance_fact > 1 && x->SID > x->parent->SID)   // Left Right Case
            {
                x->parent = rotation_counterclock(x->parent);
                rotation_clock(x->parent);
            }

            //----------------------------------------------------------------------------------------------------------

            if (balance_fact < -1 && x->SID < root->right->SID) // Right Left Case
            {
                x->parent = rotation_clock(x->parent);
                rotation_counterclock(x->parent);
            }
        }

    }
}

int main()
{
    Node tmp[10];
    for (int i = 0; i < 10; i++) {

        cin >> tmp[i].SID;
    }
    AVL x;
    for (int i = 0; i < 10; i++) {

        x.AVL_Insert(&tmp[i]);
    }
    int operationChoice;
    cin >> operationChoice;
    if (operationChoice == 1) { // enumerate key 
        x.AVL_Enumerate();
    }
    else {
        cout << "Enter a valid choice";
    }
    return 0;
}