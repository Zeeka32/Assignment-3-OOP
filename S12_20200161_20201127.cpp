//Amr Riyad - 20201127 || Hussien Mostafa - 20200161
#include <iostream>
#include <fstream>
using namespace std;

string inputF, outputF;

class FloatArray {
private:
    int index_ = 0;

protected:
    float *arr_;
    bool *isTaken_;
    int size_, lastTaken_;

public:
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

    virtual void add(float x) {
        arr_[index_++] = x;
    }

    friend ostream &operator<<(ostream &output, const FloatArray &rhs) {
        ofstream outFile(outputF, ios::app);
        outFile << rhs.size_ << "|";
        for (int i = 0; i < rhs.size_; i++) {
            outFile << "\t" << rhs.arr_[i];
        }
        outFile << "\n";
        return output;
    }

    friend istream &operator>>(istream &input, FloatArray &rhs) {
        float x;
        input >> x;
        rhs.add(x);
        return input;
    }

    ~FloatArray() {
        delete[] arr_;
    }

    void print() {
        for (int i = 0; i < size_; ++i) {
            cout << arr_[i] << " ";
        }
    }
};

class SortedArray : public FloatArray {
public:
    SortedArray(int size) : FloatArray(size) {}

    void add(float f) {
        for (int i = 0; i < size_; ++i) {
            if (!isTaken_[i]) {
                arr_[i] = f;
                isTaken_[i] = true;
                lastTaken_++;
                break;
            } else {
                if (arr_[i] <= f) {
                    continue;
                } else {
                    for (int j = size_ - 1; j > i; --j) {
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

//Mostly done
class PositiveArray : public SortedArray {
public:
    PositiveArray(int size) : SortedArray(size) {}

    void add(float f) {
        if (f > 0) {
            SortedArray::add(f);
        }else size_--;
    }
};

//Mostly done
class NegativeArray : public SortedArray {
public:
    NegativeArray(int size) : SortedArray(size) {}

    void add(float f) {
        if (f < 0) {
            SortedArray::add(f);
        }else size_--;
    }
};

//DONE
int main() {

    string classType; int size;
    cout << "Enter the input file's name\n";
    cin >> inputF;

    cout << "Enter the output file's name\n";
    cin >> outputF;
    
    ifstream inFile; inFile.open(inputF.c_str());
    while(!inFile.eof()) {
        
        inFile >> classType;
        inFile >> size;
        if(classType == "Sorted")
        {
            FloatArray* object = new SortedArray(size);
            for(int i = 0; i < size; i++)
            {
                inFile >> *object;
            }
            cout << *object;
            delete object;
        }


        else if(classType == "Array")
        {
            FloatArray* object = new FloatArray(size);
            for(int i = 0; i < size; i++){
                inFile >> *object;
            }
            cout << *object;
            delete object;
        }


        else if(classType == "Front")
        {
            FloatArray* object = new FrontArray(size);
            for(int i = 0; i < size; i++){
                inFile >> *object;
            }
            cout << *object;
            delete object;
        }


        else if(classType == "Positive")
        {
            FloatArray* object = new PositiveArray(size);
            for(int i = 0; i < size; i++){
                inFile >> *object;
            }
            cout << *object;
            delete object;
        }


        else if(classType == "Negative")
        {
            FloatArray* object = new NegativeArray(size);
            for(int i = 0; i < size; i++){
                inFile >> *object;
            }
            cout << *object;
            delete object;
        }
    }
    inFile.close();
}