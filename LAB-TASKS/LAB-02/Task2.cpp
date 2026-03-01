//#include<iostream>
//using namespace std;
//
//class student{
//	public:
//	string name;
//	int rollNumber;
//	float marks;
//	
//	void getData(){
//		cout<<"Enter Name: ";
//		cin>>name;
//		cout<<"Enter Roll Number: ";
//		cin>>rollNumber;
//		cout<<"Enter Marks: ";
//		cin>>marks;		
//	}
//	void displayData(){
//	    cout<<"Name: "<<name<<endl;
//		cout<<"Roll Number: "<<rollNumber<<endl;	
//		cout<<"Marks: "<<marks<<endl;		
//	}
//};
//int main(){
//	student s1;
//	s1.getData();
//	s1.displayData();
//	return 0;
//}

#include <iostream>
using namespace std;

class Rectangle {
public:
    int length;
    int width;


    void setDimensions();   // Function declaration
    int area();             // Function declaration
    int perimeter();        // Function declaration
};

// Defining member functions outside the class

void Rectangle::setDimensions() {
    cout << "Enter length: ";
    cin >> length;
    cout << "Enter width: ";
    cin >> width;
}

int Rectangle::area() {
    return length * width;
}

int Rectangle::perimeter() {
    return 2 * (length + width);
}

int main() {
    Rectangle rect;

    rect.setDimensions();

    cout << "Area of rectangle: " << rect.area() << endl;
    cout << "Perimeter of rectangle: " << rect.perimeter() << endl;

    return 0;
}

