//Amr Riyad - 20201127 || Hussien Mostafa - 20200161
#include <iostream>

using namespace std;

//TODO
class FloatArray {
private:
    int size_;
    float *arr;
public:
    FloatArray(int size) {
        size_ = size;
        arr = new float[size_];
        for (int i = 0; i < size_; ++i) {
            arr[i] = 0;
        }
    }

    void addFloat(float x) {
        for (int i = 0; i < size_; ++i) {
            if (arr[i] == 0) {
                arr[i] = x;
                break;
            }
        }
    }


    friend void operator<<(ofstream &in, FloatArray &rhs) {

    }

    friend void operator>>(ofstream &in, FloatArray &rhs) {

    }

    ~FloatArray() {
        delete[] arr;
    }

//    void print() {
//        for (int i = 0; i < size_; ++i) {
//            cout << arr[i] << " ";
//        }
//    }
};

//TODO
class SortedArray {

};

//TODO
class FrontArray {

};

//TODO
class PositiveArray {

};

//TODO
class NegativeArray {

};

int main() {
    FloatArray x(3);
    x.addFloat(1.2);
//    x.print();
}
