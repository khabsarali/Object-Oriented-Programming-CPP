#include <iostream>

using namespace std;

// Base class tracking file lifecycle
class File {
public:
    File() {
        cout << "[File] Base constructor: File descriptor opened." << endl;
    }

    ~File() {
        cout << "[File] Base destructor: File descriptor closed." << endl;
    }
};

// Derived class tracking specialized text file lifecycle
class TextFile : public File {
public:
    TextFile() {
        cout << "[TextFile] Derived constructor: Text buffer initialized." << endl;
    }

    ~TextFile() {
        cout << "[TextFile] Derived destructor: Text buffer flushed and freed." << endl;
    }
};

int main() {
    cout << "--- Creating TextFile Object in Local Scope ---" << endl;
    {
        TextFile txt;
        cout << "--- TextFile Object in Active Use ---" << endl;
    }
    cout << "--- TextFile Object Left Scope ---" << endl;

    return 0;
}
