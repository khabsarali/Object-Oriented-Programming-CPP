#include <iostream>
using namespace std;

class Box
{
private:
    int length;

public:
    // Constructor
    Box(int l)
    {
        length = l;
    }

    // Friend function declaration
    friend void displayLength(Box b);
};

// Friend function definition
void displayLength(Box b)
{
    cout << "Length = " << b.length << endl;
}

int main()
{
    Box b1(15);   

    // Call friend function like a normal function
    displayLength(b1);

    return 0;
}