//Amr Riyad - 20201127 || Hussien Mostafa - 20200161
#include <iostream>
#include <fstream>
using namespace std;

//Input and output file names that the user will manually enter.
string inputF, outputF;

//The abstract class FloatArray.
class FloatArray {
private:
    //A private int member to count the index of the array to know where to put the next element.
    int index_ = 0;

protected:
    float *arr_;
    bool *isTaken_;
    int size_, lastTaken_;

public:

    //A paramatrized constructor for the FloatArray class.
    FloatArray(int size) {
        size_ = size;
        isTaken_ = new bool[size_];
        arr_ = new float[size_];
        for (int i = 0; i < size_; ++i) {
            arr_[i] = 0;
            isTaken_[i] = false;
        }
        lastTaken_ = 0;
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
    friend istream &operator>>(istream &input, FloatArray &rhs) {
        float x;
        input >> x;
        rhs.add(x);
        return input;
    }

    //the destructor for the Float array.
    ~FloatArray() {
        delete[] arr_;
        delete[] isTaken_;
    }

};

class SortedArray : public FloatArray {
public:
    SortedArray(int size) : FloatArray(size) {}

    void add(float f) {

        for (int i = 0; i < size_; ++i) 
        {
            if (!isTaken_[i]) 
            {
                arr_[i] = f;
                isTaken_[i] = true;
                lastTaken_++;
                break;
            } 
            else
            {
                if (arr_[i] <= f) {
                    continue;
                } else {
                    for (int j = size_ - 1; j > i; --j) 
                    {
                        swap(arr_[j], arr_[j - 1]);
                    }
                    
                    arr_[i] = f;
                    isTaken_[lastTaken_] = true;
                    lastTaken_++;
                    break;
                }
            }
        }
    }
};

class FrontArray : public FloatArray {
private:
    int index_;
    
public:
    FrontArray(int size) : FloatArray(size) {index_ = size_ - 1;}

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
        }else size_--;
    }
};


class NegativeArray : public SortedArray {
public:
    NegativeArray(int size) : SortedArray(size) {}

    void add(float f) {
        if (f < 0) {
            SortedArray::add(f);
        }else size_--;
    }
};


int main() {

    string classType; int size;
    cout << "Enter the input file's name\n";
    cin >> inputF;

    cout << "Enter the output file's name\n";
    cin >> outputF;
    
    FloatArray* objects[10];
    ifstream inFile; inFile.open(inputF.c_str());
    int k = 0;
    while(!inFile.eof()) {
        inFile >> classType;
        inFile >> size;
        if(classType == "Sorted")
        {
            objects[k] = new SortedArray(size);
            for(int i = 0; i < size; i++)
            {
                inFile >> *(objects[k]);
            }
            cout << *(objects[k]); k++;
        }


        else if(classType == "Array")
        {
            objects[k]  = new FloatArray(size);
            for(int i = 0; i < size; i++){
                inFile >> *(objects[k]);
            }
            cout << *(objects[k]); k++;
        }


        else if(classType == "Front")
        {
            objects[k] = new FrontArray(size);
            for(int i = 0; i < size; i++){
                inFile >> *(objects[k]);
            }
            cout << *(objects[k]); k++;
        }


        else if(classType == "Positive")
        {
            objects[k]  = new PositiveArray(size);
            for(int i = 0; i < size; i++){
                inFile >> *(objects[k]);
            }
            cout << *(objects[k]); k++;
        }


        else if(classType == "Negative")
        {
            objects[k] = new NegativeArray(size);
            for(int i = 0; i < size; i++){
                inFile >> *objects[k];
            }
            cout << *objects[k];
        }
    }

    delete [] objects;
    inFile.close();
}