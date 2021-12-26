//Amr Riyad - 20201127 || Hussien Mostafa - 20200161 || S11-S12 || Assignment 3
#include <iostream>
#include <fstream>

using namespace std;

//Input and output file names that the user will manually enter.
string inputF, outputF;

//The abstract class FloatArray.
class FloatArray {
private:
    int index_ = 0;
protected:
    float *arr_;
    int size_;
public:

    //A paramatrized constructor for the FloatArray class.
    FloatArray(int size) {
        size_ = size;
        arr_ = new float[size_];
    }

    //a polymorphism function in this class it simply fills up an array the usual way.
    virtual void add(float x) {
        arr_[index_++] = x;
    }

    //Operator Overloading.
    friend ostream &operator<<(ostream &output, const FloatArray &rhs) {
        ofstream outFile(outputF, ios::app);
       
        outFile << rhs.size_ << "|";
        for (int i = 0; i < rhs.size_; i++) {
            outFile << "\t" << rhs.arr_[i];
        }
        outFile << "\n";

        outFile.close();
        return output;
    }
    friend istream &operator>>(istream &input, FloatArray &rhs) {
        float number;
        input >> number;
        rhs.add(number);
        return input;
    }

    //the destructor for the Float array.
    ~FloatArray() {
        delete[] arr_;
    }

};


//the child class SortedArray.
class SortedArray : public FloatArray {
private:
    //these members are used for the sorting algorithm.
    bool *isTaken_;
    int lastTaken_;
public:

    //the parameterized constructor for the SortedAarray class.
    //we initialize an array of booleans to help with the sorting algo.
    //and the last taken variable to store the index of the last taken element.
    SortedArray(int size) : FloatArray(size) {
        isTaken_ = new bool[size_];
        for (int i = 0; i < size_; ++i) {
            arr_[i] = 0;
            isTaken_[i] = false;
        }
        lastTaken_ = 0;
    }

    //the add function for the SortedArray class.
    void add(float f) {

        //if the slot is empty put an element in said slot and said slot's index.
        //becomes true meaning there is an element there.
        for (int i = 0; i < size_; ++i) {
            if (!isTaken_[i]) {
                arr_[i] = f;
                isTaken_[i] = true;
                lastTaken_++;
                break;
            } else {

                //if an element already exists we compare if it's larger or smaller than the
                //existing element. if it's larger then we just continue.
                if (arr_[i] <= f) {
                    continue;
                } else {

                    //if the number is smaller we shift the array to the left starting from
                    //the end till the index we need to empty.
                    for (int j = size_ - 1; j > i; --j) {
                        swap(arr_[j], arr_[j - 1]);
                    }

                    //add the number to the array and turn that index true.
                    arr_[i] = f;
                    isTaken_[lastTaken_++] = true;
                    break;
                }
            }
        }
    }
    
    //destructor for the SortedArray class to free allocated memory.
    ~SortedArray() {
        delete[] isTaken_;
    }
};

//The child class FrontArray.
class FrontArray : public FloatArray {
private:
    int index_;
public:
   
    //Front array constructor.
    FrontArray(int size) : FloatArray(size) { index_ = size_ - 1; }

    //the front array add function.
    void add(float f) {
        for (int j = size_ - 1; j > 0; --j) {
            swap(arr_[j], arr_[j - 1]);
        }
        arr_[0] = f;
    }
};


//the child class PositiveArray.
class PositiveArray : public SortedArray {
public:
    //PositiveArray constructor.
    PositiveArray(int size) : SortedArray(size) {}

    void add(float f) {
        if (f > 0) {
            SortedArray::add(f);
        } else size_--;
    }
};

//the child class NegativeArray.
class NegativeArray : public SortedArray {
public:
    //NegativeArray constructor.
    NegativeArray(int size) : SortedArray(size) {}

    void add(float f) {
        if (f < 0) {
            SortedArray::add(f);
        } else size_--;
    }
};


int main(void) {

    //string to store the classtype and object sum to loop through the objects.
    string classType;
    int size, objectSum = 0;

    //prompting the user for the i/o files' name.
    cout << "Enter the input file's name\n";
    cin >> inputF;
    cout << "Enter the output file's name\n";
    cin >> outputF;

    //creating an array of pointers of the parent class.
    FloatArray *objects[10];

    ifstream inFile;
    inFile.open(inputF.c_str());
    
    //a while loop to loop over the file contents.
    while (!inFile.eof()) {

        //first we input the classtype and its size from the file.
        inFile >> classType;
        inFile >> size;

        //based on the class type we allocate memory accordingly then fill up
        //the array based on the type.
        if (classType == "Sorted") {
            objects[objectSum] = new SortedArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *objects[objectSum];
            }
            objectSum++;
            
        } else if (classType == "Array") {
            objects[objectSum] = new FloatArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *objects[objectSum];
            }
            objectSum++;

        } else if (classType == "Front") {
            objects[objectSum] = new FrontArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *objects[objectSum];
            }
            objectSum++;

        } else if (classType == "Positive") {
            objects[objectSum] = new PositiveArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *objects[objectSum];
            }
            objectSum++;

        } else if (classType == "Negative") {
            objects[objectSum] = new NegativeArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *objects[objectSum];
            }
            objectSum++;
        }
    }

    //loop to print the items.
    for(int i = 0; i < objectSum; i++){
        cout << *objects[i];
    }

    //free allocated memory.
    for (int i = 0; i < 10; i++)
        delete objects[i];
    inFile.close();
}
