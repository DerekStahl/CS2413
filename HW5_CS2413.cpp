#include <iostream>
#include <stack>
#include <queue>
using namespace std;
// the node class is used to creat list representation 
class Node {
public:
    int SID = -1;
    Node* next = NULL;
};
// here is the graph class 
// assume we work on an undirected graph of 6 nodes (fix size) 
// it has a matrix representation and a list representation 
// ask students to input matrix representation
// and design a function to convert that to a list representation 
class Graph {
public:
    Graph();
    void SetMatrix(int a, int b);   // set Matrix[a][b] = Matrix[b][a] = 1
                                    // a and b must be in [0,5] 
                                    // already implemented
    void DeleteMatrix();            // reset matrix to zero
                                    // already implemented
    void Convert();                 // convert matrix representation to list
                                    // in the list, make sure nodes are sorted in an ascending order
                                    // @TODO: you need to implement this method
    void EnumerateList();           // enumerate all nodes in the list
                                    // already implemented
    int* DFS(int idx);              // depth first search based on list representation
                                    // idx represents the first node to visit
                                    // whenever there is a tie, choose the smallest node to  visit first
                                    // return a pointer to an array of 6 nodes based on the order they are visited
                                    // for example, if DFS visits 3, 5, 2, 0, 1, 4; then the array should have
                                    // x[0]=3, x[1]=5, x[2]=2, x[3]=0, x[4]=1, x[5]=4
                                    // @TODO: you need to implement this method

    void converter_help(int column, int row);   //helps the main converter function by iterating through the columns of the matrix
    void find_next(Node* x, int j, int row);    //finds the next open node in a position on the list
    int DFS_help(Node* x);  //helps the main DFS function by checking to see if values have been visited on different nodes
    vector<bool> visited = { false, false, false, false, false, false, false, false, false, false };    //used to tell if certain values have been visited
    int dfsvect[6]; //stores the traversal of DFS

private:
    int Matrix[6][6];
    Node* List[6];
};
// enumerate nodes in a list
void Graph::EnumerateList() {
    Node* temp;
    for (int i = 0; i < 6; i++) {
        cout << i << " -> ";
        if (List[i] != NULL) {
            temp = List[i];
            cout << temp->SID;
            while (temp->next != NULL) {
                temp = temp->next;
                cout << " -> " << temp->SID << ' ';
            }
            cout << endl;
        }
    }
}
// SetMatrix Function
void Graph::SetMatrix(int a, int b) {
    Matrix[a][b] = 1;
    Matrix[b][a] = 1;
}
// DeleteMatrix Function
void Graph::DeleteMatrix() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            Matrix[i][j] = 0;
        }
    }
}
// constructor
Graph::Graph() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            Matrix[i][j] = 0;
        }
        List[i] = NULL;
    }
}


void Graph::find_next(Node* x, int j, int row) {    //find the next available node


    if (x == NULL) {
        List[row] = new Node();
        List[row]->SID = j;
    }

    else if (x->next != NULL) {
        find_next(x->next, j, row);
    }
    else {
        x->next = new Node();
        x->next->SID = j;
    }

}

void Graph::converter_help(int column, int row) {   //helps convert the matrix into a list, does so for each individual column

    for (int j = column; j < 6; j++) {
        if (Matrix[row][j] == 1) {

            find_next(List[row], j, row);


        }
        else {
            ;//do nothing
        }
    }
}

void Graph::Convert() { //the main convert function, this iterates through all the rows

    for (int i = 0; i < 6; i++) {

        converter_help(0, i);
    }
}

int Graph::DFS_help(Node* x) {  //this helps the main DFS function, checks to see if nodes have been visited and if so recursively calls itself to the next node

    int idx2 = x->SID;

    if (visited[idx2] == false) {
        return idx2;
    }
    else if (visited[idx2] == true && x->next != NULL) {
        DFS_help(x->next);
    }

    else {  //if the end of a branch is reached
        return idx2-1;
    }
}

int counter = 0;
int* Graph::DFS(int idx) {  //while the DFS array is not filled, keep iterating through the graph. when a new value is found store it in the dfsvect array
    
    while (counter < 6) {
        if (visited[idx] == false) {
            visited[idx] = true;
            dfsvect[counter] = idx;
            counter++;
        }

        else {
            int next_check = DFS_help(List[idx]);
                DFS(next_check);
        }
    }




    return dfsvect; //array of dfs
}

int main()
{
    Graph graph;
    int a, b; // the values of a and b are between 0 and 5
    int* visit;
    // always input 8 edges
    for (int i = 0; i < 8; i++) {
        cin >> a >> b;
        graph.SetMatrix(a, b);
    }
    int idx;
    cin >> idx;
    // always immediately convert matrix into list
    cout << "Adjacency List" << endl;
    graph.Convert();
    graph.DeleteMatrix();
    graph.EnumerateList();
    cout << "DFS" << endl;
    visit = graph.DFS(idx);
    for (int i = 0; i < 6; i++) {
        cout << visit[i] << ' ';
    }
    return 0;



}
