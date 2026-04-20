#include <iostream>
#include <exception>
#include <cmath>
#include <limits>
#include <new>    
#include <stdexcept> 

using namespace std;

class InputFailException : public exception {
public:
    const char* what() const throw() { return "Incorrect numbers"; }
};

class Div0Exception : public exception {
public:
    const char* what() const throw() { return "Divided by zero"; }
};

class RangeException : public exception {
public:
    const char* what() const throw() { return "Value out of range"; }
};

void checkDivisor(int y) {
    if (y == 0) throw Div0Exception();
}

int main() {
    int x, y;
    double d;
    bool retry = true;

    while (retry) {
        try {
            cout << "Enter 2 numbers: ";
            
            if (!(cin >> x >> y)) {
                throw InputFailException();
            }

            if (abs(x) > 1000 || abs(y) > 1000) {
                throw RangeException(); 
            }

            checkDivisor(y);

            d = (double)x / y;
            cout << "The result is " << d << endl;
            
            // ส่วนจำลองหน่วยความจำเต็ม
            for (int i = 0; i < 1; i++) {
                cout << "Allocating memory .... " << i << endl;
                double* myarray = new double[999999999999999]; 
            }

            retry = false; 

        } 

        catch (const exception &e) {
            cerr << e.what() << endl;
            
            if (string(e.what()) == "Incorrect numbers") {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            if (string(e.what()) == "std::bad_alloc" || string(e.what()) == "bad allocation") {
                retry = false;
            }
        }
    }

    return 0;
}