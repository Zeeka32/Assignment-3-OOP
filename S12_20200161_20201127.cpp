//Amr Riyad - 20201127 || Hussien Mostafa - 20200161 || S11-S12 || Assignment 3
#include <iostream>
#include <fstream>
using namespace std;

//The abstract class FloatArray.
class FloatArray {
private:
    int index_ = 0;
protected:
    float *arr_;
    int size_;
public:

    //A paramatrized constructor for the FloatArray class.
    FloatArray(int size) : size_(size) {
        arr_ = new float[size_];
    }

    virtual void add(float f) {
        arr_[index_++] = f;
    }

    //Operator Overloading.
    friend ofstream &operator<<(ofstream &output, FloatArray &rhs) {

        output << rhs.size_ << "|";
        for (int i = 0; i < rhs.size_; i++) {
            output << "\t" << rhs.arr_[i];
        }
        output << "\n";
        return output;
    }

    friend ifstream &operator>>(ifstream &input, FloatArray &rhs) {
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
    //this members is used for the sorting algorithm.
    int lastTaken_ = 0;
public:

    //the parameterized constructor for the SortedArray class.
    SortedArray(int size) : FloatArray(size) {}

    void add(float f) {

        //binary search to find the right index, "left" stores the first index.
        //and "right" stores the last index of the array.
        int Left = 0, Right = lastTaken_, mid;
        while (Left < Right) {
            mid = (Left + Right) / 2;
            if (arr_[mid] > f) {
                Right = mid;
            } else {
                Left = mid + 1;
            }
        }
        
        //shift elements to the right.
        for (int j = lastTaken_; j > Left; --j) {
            swap(arr_[j], arr_[j - 1]);
        }
        arr_[Left] = f;
        lastTaken_++;
    }

};

//The child class FrontArray.
class FrontArray : public FloatArray {
public:

    //Front array constructor.
    FrontArray(int size) : FloatArray(size) {}

    void add(float f) {

        //shift all elements to the right then add the new number at the front.
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

int main() {

    //string to store the classtype and object sum to loop through the objects.
    string classType, inputFileName, outputFileName;
    int size, objectSum = 0;
    
    //prompting the user for the i/o files' name.
    cout << "Enter the input file's name\n";
    cin >> inputFileName;
    cout << "Enter the output file's name\n";
    cin >> outputFileName;

    //creating an array of pointers of the parent class.
    FloatArray *objects[10];

    //opening the i/o files.
    ifstream inFile(inputFileName);
    ofstream outFile(outputFileName);

    //loop over the file contents.
    while (!inFile.eof()) {

        //input the classtype and its size from the file.
        inFile >> classType;
        inFile >> size;

        //based on the class type we allocate memory accordingly then fill up
        //the array based on the type.
        if (classType == "Sorted") {
            objects[objectSum] = new SortedArray(size);

            for (int i = 0; i < size; i++)
                inFile >> *objects[objectSum];
            objectSum++;

        } else if (classType == "Array") {
            objects[objectSum] = new FloatArray(size);

            for (int i = 0; i < size; i++)
                inFile >> *objects[objectSum];
            objectSum++;

        } else if (classType == "Front") {
            objects[objectSum] = new FrontArray(size);

            for (int i = 0; i < size; i++)
                inFile >> *objects[objectSum];
            objectSum++;

        } else if (classType == "Positive") {
            objects[objectSum] = new PositiveArray(size);

            for (int i = 0; i < size; i++)
                inFile >> *objects[objectSum];
            objectSum++;

        } else if (classType == "Negative") {
            objects[objectSum] = new NegativeArray(size);

            for (int i = 0; i < size; i++)
                inFile >> *objects[objectSum];
            objectSum++;
        }
    }

    //loop to print the items.
    for (int i = 0; i < objectSum; i++)
        outFile << *objects[i];

    //free allocated memory.
    for (int i = 0; i < 10; i++)
        delete objects[i];

    //close the opened files.
    inFile.close();
    outFile.close();

    return 0;
}
