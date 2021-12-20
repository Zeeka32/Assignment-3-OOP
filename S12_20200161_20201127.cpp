//Amr Riyad - 20201127 || Hussien Mostafa - 20200161
#include <iostream>
#include <fstream>

using namespace std;

//DONE
class FloatArray {
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

    void addFloatToBack(float x) {
        for (int i = 0; i < size_; ++i) {
            if (!isTaken_[i]) {
                arr_[i] = x;
                isTaken_[i] = true;
                break;
            }
        }
    }

    //YASTA A7MOS ANA M4 FAHM 7AGA FI EL FILES
    friend ostream &operator<<(ostream &output, const FloatArray &rhs) {
        ofstream outFile("output.txt");
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

//DONE
class SortedArray : public FloatArray {
public:
    SortedArray(int size) : FloatArray(size) {}

    void addSortedFloat(float f) {
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

//DONE
class FrontArray : public FloatArray {
public:
    FrontArray(int size) : FloatArray(size) {}

    void addFloatToFront(float f) {
        for (int j = size_ - 1; j > 0; --j) {
            swap(arr_[j], arr_[j - 1]);
        }
        arr_[0] = f;
    }
};

//TODO
class PositiveArray : public SortedArray {
private:

public:
    PositiveArray(int size) : SortedArray(size) {}

    void addPostiveFloat(float f) {
        if (f > 0) {
            addSortedFloat(f);
        }
    }
};

//TODO
class NegativeArray : public SortedArray {
private:

public:
    NegativeArray(int size) : SortedArray(size) {}

    void addNegativeFloat(float f) {
        if (f < 0) {
            addSortedFloat(f);
        }
    }
};

int main() {
//    FloatArray x(3);
    NegativeArray y(6);
    y.addNegativeFloat(7.5);
    y.addNegativeFloat(-3.5);
    y.addNegativeFloat(-1.5);
    y.addNegativeFloat(-4.5);
    y.addNegativeFloat(-1.5);
    y.addNegativeFloat(0);
//    cin >> x;
//    cout << x;
    y.print();

}