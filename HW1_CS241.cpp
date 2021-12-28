// HW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//By Derek Stahl

#include <iostream>
using namespace std;
class Array {

public:
    // please implement the following six member functions 
    void Set(int key, int index);  // assign "key" to "x[index]"
    int* Get();                    // return pointer to a copy of array x 
                                   // must be a copy, not x itself 
    void Sort_Bubble();            // bubble sort array x
    void Sort_Insertion();         // insertion sort array x                     
    int Search_Linear(int key);    // linear search of "key" in the array
                                   // if success, return index of key 
                                   // if fail, return -1 
    int Search_Binary(int key);    // binary search of "key" in the array
                                   // if success, return index of key 
                                   // if fail, return -1 
    int partitionSearch(int beginning, int end, int key);   //basically a binary search, but made so that it can be recursive
private:
    int x[10];                     // array size is fixed to 10 
};

void Array::Set(int key, int index) {
    
    x[index] = key;     //key is assigned to index of x
}


int* Array::Get() {
    
    return x;
}

//switches the current index in x with the index right after x without a temporary variable
void swap(int currentIndex, int x[]) {

    //switch the two numbers without using a temporary variable
    x[currentIndex] = x[currentIndex] + x[currentIndex + 1];
    x[currentIndex + 1] = x[currentIndex] - x[currentIndex + 1];
    x[currentIndex] = x[currentIndex] - x[currentIndex + 1];
}

//BUBBLE SORT ARRAY
void Array::Sort_Bubble() {
    
   
      for (int i = 0; i < (sizeof(x) / sizeof(x[0])) - 1; i++) {

        //if the first index is smaller than the second index
        if (Get()[i] > Get()[i + 1]) {

            swap(i, Get()); //swaps the two values
        }

        else {
            //do nothing
        }
    }


    //Check to see if the array is fully sorted
    for (int i = 0; i < (sizeof(x) / sizeof(x[0])) - 1; i++) {
        
        if (Get()[i] <= Get()[i + 1]) {
            ;// do nothing
        }

        else {
            Sort_Bubble();
        }
    }

}


//INSERTION SORT ARRAY
void Array::Sort_Insertion() {

    int key;

    for (int i = 0; i < (sizeof(x) / sizeof(x[0])) - 1; i++) {

        key = (Get())[i + 1];   //set the key equal to the second element in the array x
        int compareIndex = i;   //index to be used to compare values with the key

        while (key < (Get())[compareIndex] && compareIndex >= 0) {  //while the current key is less than the index before and greater than or equal to zero
            (Get())[compareIndex + 1] = (Get())[compareIndex];  //switch key at compare index and the one after it if it is less than the key
            compareIndex--;
        }

        
            (Get())[compareIndex + 1] = key;            //insert key at its lowest position

    

    }
}

//LINEAR SEARCH
int Array::Search_Linear(int key) {

    //increment index after every comparison between key and position of array until key is found or not
    for (int i = 0; i < (sizeof(x) / sizeof(x[0])); i++) {

        int number = Get()[i];
        if (number == key) {
            return i;
        }
        else {
            //do nothing
        }

        
    }
    return (-1);    //key is not found
}


//PARTITION SEARCH
int Array::partitionSearch(int beginning, int end, int key){
    
    int middle = ((end - beginning)/ 2) + beginning;    //takes the middle point between the end and the beginning indices

    //checks to see for 2 size arrays, helpful if key is at the beginning or end of the array
    if (end - beginning == 1){
        if (Get()[end] == key) {
            return end;
        }

        else if (Get()[beginning] == key) {
            return beginning;
        }
        else {
            return (-1);
        }
    }


    //if the middle position is greater search the left half
    else if (Get()[middle] > key) {
        partitionSearch(beginning, middle, key);
    }

    //if the middle position is smaller search the right half
    else if (Get()[middle] < key) {
        partitionSearch(middle, end, key);
    }
    
    //if the middle position is equal return that one
    else if(key == Get()[middle]) {
        return middle;
    }
    //if it cannot be found return -1
    else {
        return (-1);
    }
}
//BINARY SEARCH
int Array::Search_Binary(int key) {

    return partitionSearch(0, 9, key); //uses partition search as actual binary search
}

int main()
{
    Array A;

    int InputKey, operationChoice, SearchKey, IndexKey;
    int i = 0;
    while (i < 10) {
        cin >> InputKey;             // Reads the input numbers from the console
        A.Set(InputKey, i);
        i++;
    }

    
    // if operationChoice = 1, directly output elements in A 
    // if operationChoice = 2, sort elements in A by bubble sort and output result 
    // if operationChoice = 3, sort elements in A by insertion sort and output result 
    // if operationChoice = 4, apply linear search to search for "SearchKey" in A
    // if operationChoice = 5, first apply bubble sort on A, then apply binary search to search for "SearchKey" in A

    cin >> operationChoice;  
    int* temp;

    if (operationChoice == 1)
    {
        temp = A.Get();
        for (int i = 0; i < 10; i++) {
            cout << temp[i] << ' ';   // outputs are separated by tabs 
        }
    }
    else if (operationChoice == 2)
    {
        A.Sort_Bubble();
        temp = A.Get();
        for (int i = 0; i < 10; i++) {
            cout << temp[i] << ' ';   // outputs are separated by tabs 
        }
    }
    
    else if (operationChoice == 3)
    {
        A.Sort_Insertion();
        temp = A.Get();
        for (int i = 0; i < 10; i++) {
            cout << temp[i] << ' ';   // outputs are separated by tabs 
        }
    }
    
    else if (operationChoice == 4)
    {
        cin >> SearchKey;
        IndexKey = A.Search_Linear(SearchKey);
        cout << IndexKey << endl;
    }
    
    else if (operationChoice == 5)
    {
        cin >> SearchKey;
        A.Sort_Bubble();
        IndexKey = A.Search_Binary(SearchKey);
        cout << IndexKey << endl;
    }
    else
    {
        cout << "Enter a valid choice";
    }
    
    
    

    return 0;
}

