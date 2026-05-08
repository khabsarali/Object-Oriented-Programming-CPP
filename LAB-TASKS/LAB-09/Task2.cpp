#include<iostream>
using namespace std;
class Distance {
private:
    int feet;
    int inches;

public:
    Distance(int f, int i) {
        feet = f;
        inches = i;
    }

    bool operator==(Distance d) {
        if (feet == d.feet && inches == d.inches)
            return true;
        else
            return false;
    }

    void checkEqual(Distance d) {
        if (*this == d)
            cout << "Both distances are equal" << endl;
        else
            cout << "Distances are NOT equal" << endl;
    }
};

int main() {
    Distance d1(5, 8);
    Distance d2(5, 8);

    d1.checkEqual(d2);

    return 0;
}