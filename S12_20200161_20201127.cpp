//Amr Riyad - 20201127 || Hussien Mostafa - 20200161
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

    //overloading the insertion operator to print output to a file.
    friend ostream &operator<<(ostream &output, const FloatArray &rhs) {
        ofstream outFile(outputF, ios::app);
        outFile << rhs.size_ << "|";
        for (int i = 0; i < rhs.size_; i++) {
            outFile << "\t" << rhs.arr_[i];
        }
        outFile << "\n";
        return output;
    }

    //overloading the extraction operator to read the inputs from a file.
    //it first stores the float from the file then calls the right add function.
    //using polymorphism.
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


//the 2nd class the sortedarray class which inherits from the FloatArray class.
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
            }
                //if an element already exists we compare if it's larger or smaller than the
                //existing element. if it's larger then we just continue.
            else {
                if (arr_[i] <= f) {
                    continue;
                }
                    //however if the element is smaller than existing element:
                    //we shift the array to the left starting from the posistion
                    //of the desired index.
                else {
                    for (int j = size_ - 1; j > i; --j) {
                        swap(arr_[j], arr_[j - 1]);
                    }

                    //finally we put the float in the new empty slot.
                    // and we turn the last taken index true.
                    arr_[i] = f;
                    isTaken_[lastTaken_] = true;
                    lastTaken_++;
                    break;
                }
            }
        }
    }

    ~SortedArray() {
        delete[] isTaken_;
    }
};

class FrontArray : public FloatArray {
private:
    int index_;

public:
    FrontArray(int size) : FloatArray(size) { index_ = size_ - 1; }

    void add(float f) {
        arr_[index_--] = f;
    }
};


class PositiveArray : public SortedArray {
public:
    PositiveArray(int size) : SortedArray(size) {}

    void add(float f) {
        if (f > 0) {
            SortedArray::add(f);
        } else size_--;
    }
};


class NegativeArray : public SortedArray {
public:
    NegativeArray(int size) : SortedArray(size) {}

    void add(float f) {
        if (f < 0) {
            SortedArray::add(f);
        } else size_--;
    }
};


int main() {

    string classType;
    int size;
    cout << "Enter the input file's name\n";
    cin >> inputF;

    cout << "Enter the output file's name\n";
    cin >> outputF;

    FloatArray *objects[10];
    ifstream inFile;
    inFile.open(inputF.c_str());
    int k = 0;
    while (!inFile.eof()) {
        inFile >> classType;
        inFile >> size;
        if (classType == "Sorted") {
            objects[k] = new SortedArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *(objects[k]);
            }
            cout << *objects[k];
            k++;
        } else if (classType == "Array") {
            objects[k] = new FloatArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *(objects[k]);
            }
            cout << *objects[k];
            k++;
        } else if (classType == "Front") {
            objects[k] = new FrontArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *(objects[k]);
            }
            cout << *objects[k];
            k++;
        } else if (classType == "Positive") {
            objects[k] = new PositiveArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *(objects[k]);
            }
            cout << *objects[k];
            k++;
        } else if (classType == "Negative") {
            objects[k] = new NegativeArray(size);
            for (int i = 0; i < size; i++) {
                inFile >> *objects[k];
            }
            cout << *objects[k];
        }
    }

    // Delete each pointer in the dynamic array then delete the main pointer of the dynamic array
    for (int i = 0; i < 10; i++)
        delete objects[i];
    delete *objects;

    inFile.close();
}