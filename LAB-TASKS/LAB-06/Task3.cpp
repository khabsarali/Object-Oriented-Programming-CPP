#include <iostream>
using namespace std;

// Base class
class File {
public:
    File() {
        cout << "File opened" << endl;
    }

    ~File() {
        cout << "File closed" << endl;
    }
};

// Derived class
class TextFile : public File {
public:
    TextFile() {
        cout << "Text file created" << endl;
    }

    ~TextFile() {
        cout << "Text file destroyed" << endl;
    }
};

int main()
{
    TextFile t;   // object create
    return 0;     // object destroy
}