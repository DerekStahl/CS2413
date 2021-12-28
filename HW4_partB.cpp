#include <iostream>
#include <vector>
using namespace std;
// In this project, implement a minimum heap using vector
//
// Implement two functions 
// -- insert(int key): insert a new key into the heap 
// -- remove(): remove the root key from the heap 
// 
// In the main function, we will first input 10 keys into the heap 
// Then, we will enumarate them from the vector 
// The enumeration function has been implemented for you 
// 
class heap {
public:
    void enumerate(); // enumerate all elements in the heap 
    void insert(int key); // insert a new key into the heap vector 
    void remove(); // remove root key from the heap 
    void swap(int idx1, int idx2);  //swaps two elements in the vector
    void comp_parents(int key, int idx);    //compares the parent of a node with itself and then switches if greater. recursive
    void comp_child(int key, int idx);  //compares the children of a node with itself and then switches if smaller. recursive
private:
    vector<int> x;

    int get_parent(int idx);    //returns the parent of a node
    int get_left(int idx);  //returns the left child of a node
    int get_right(int idx); //return the right child of a node
};
void heap::enumerate() {
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << ' ';
    }
}
int heap::get_left(int idx) {   //return the left child
    return (2 * idx + 1);
}
int heap::get_right(int idx) {  //return the right child
    return (2 * idx + 2);
}

int heap::get_parent(int idx) { //get the parent node of the key
    return (idx - 1) / 2;
}

void heap::swap(int idx1, int idx2) {   //swaps two values in the vector
    int temp = x[idx1];
    x[idx1] = x[idx2];
    x[idx2] = temp;
}


void heap::comp_parents(int key, int idx) { //checks to see if the parent node is smaller, recursive

    if (key < x[get_parent(idx)]) {
        swap(idx, get_parent(idx));   //swap the key and its parent
        comp_parents(key, get_parent(idx));
    }
    else {
        ;//do nothing
    }
}

void heap::comp_child(int key, int idx) {   //compares the children of the current node and swaps them if smaller, recursive
    int left = get_left(idx);
    int right = get_right(idx);

    if (left < x.size() && right < x.size() ){  //if node has two children, compare them and switch with the lower value one. Then call function again
        if (x[left] < x[right]) {
            swap(left, idx);
            comp_child(key, left);
        }
        else if (x[right] < x[left]) {
            swap(right, idx);
            comp_child(key, right);
        }
        else {
            ;//do nothing
        }
    }

    else if (left < x.size() && right >= x.size()) {    //if left side has a smaller value but right side does not
        swap(left, idx);
        comp_child(key, left);
    }

    else if (right < x.size() && left >= x.size()) {   //if right side has a smaller value but right side does not
        swap(right, idx);
        comp_child(key, right);
    }

    else {
        ;//do nothing
    }

}

void heap::insert(int key) {    //insert key into the min heap

    if (x.empty()) {
        x.push_back(key);   //put element into vector
    }

    else {
        x.push_back(key);   //put element into vector
        comp_parents(key, x.size() - 1);


    }

}

void heap::remove() {

    if (x.empty()) {
        ;//do nothing
    }
    else {
        swap(0, x.size() - 1);  //swap first and last element
        x.pop_back();   //remove the last element
        comp_child(x[0], 0);    //compare elements below it
    }
}


int main()
{
    int tmp[10];
    for (int i = 0; i < 10; i++) {

        cin >> tmp[i];
    }
    heap x;
    for (int i = 0; i < 10; i++) {
        x.insert(tmp[i]);
    }

    int operationChoice;
    cin >> operationChoice;
    if (operationChoice == 1) { // enumerate key 
        x.enumerate();
    }
    else if (operationChoice == 2) { // remove the smallest element from the heap and update the heap
            x.remove();
        x.enumerate();
    }
    else {
        cout << "Enter a valid choice";
    }
    return 0;
}