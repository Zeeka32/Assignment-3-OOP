//Amr Riyad - 20201127 || Hussien Mostafa - 20200161
#include <iostream>
#include <fstream>

using namespace std;

//TODO
class FloatArray {
protected:
    float *arr_;
    int size_;
public:
    FloatArray(int size) {
        size_ = size;
        arr_ = new float[size_];
        for (int i = 0; i < size_; ++i) {
            arr_[i] = 0;
        }
    }

    void addFloatToBack(float x) {
        for (int i = 0; i < size_; ++i) {
            if (arr_[i] == 0) {
                arr_[i] = x;
                break;
            }
        }
    }

    //YASTA A7MOS ANA M4 FAHM 7AGA FI EL FILES
    friend ostream &operator<<(ostream &output, const FloatArray &rhs) {
        ofstream outFile("out.txt");
        for (int i = 0; i < rhs.size_; i++) {
            outFile << rhs.arr_[i] << " ";
        }
        return output;
    }

    friend istream &operator>>(istream &input, FloatArray &rhs) {
        ifstream inFile("input.txt");
        for (int i = 0; i < rhs.size_; i++) {
            inFile >> rhs.arr_[i];
        }
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

//TODO
class SortedArray : public FloatArray {
public:
    SortedArray(int size) : FloatArray(size) {}

    void addSortedFloat(float f) {

    }

};

//TODO
class FrontArray : public FloatArray {
public:
    FrontArray(int size) : FloatArray(size) {}

    void addFloatToFront(float f) {

    }
};

//TODO
class PositiveArray : public SortedArray {
    PositiveArray(int size) : SortedArray(size) {}

    void addPostiveFloat(float f) {

    }
};

//TODO
class NegativeArray : public SortedArray {
    NegativeArray(int size) : SortedArray(size) {}

    void addNegativeFloat(float f) {

    }
};

int main() {
    FloatArray x(3);
    cin >> x;
    x.print();

}