//Amr Riyad - 20201127 || Hussien Mostafa - 20200161
#include <iostream>
#include <fstream>

using namespace std;

//DONE
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

    //Needs fix الدكتورة عايزانا نخلي اليوزر يختار اسم الفايل الي هيطبع فيه و الي هياخد منه الانبوت في الماين مش هنا
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

//DONE - not yet checked.
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

//kinda done
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
        }
    }
};

//Mostly done
class NegativeArray : public SortedArray {
public:
    NegativeArray(int size) : SortedArray(size) {}

    void add(float f) {
        if (f < 0) {
            SortedArray::add(f);
        }
    }
};

//in progress ...
int main() {
    string inputF, outputF;

    ifstream inFile;
    cout << "Enter the input file's name\n";
    cin >> inputF;
    inFile.open(inputF.c_str());

    cout << "Enter the output file's name\n";
    cin >> outputF;
    ofstream(outputF + "", ios::app);

}