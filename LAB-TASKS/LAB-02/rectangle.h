#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <iostream>
#include <string>
using namespace std;
class Rectangle
{
	public:
	//data members
	int length, width;
	//member functions
	void setDimension();
	int area();	
	int perimeter();
};
//member functions
void Rectangle::setDimension()
{
	cout<<"Enter length: ";
	cin>>length;
	cout<<"Enter width: ";
	cin>>width;
}
int Rectangle::area()
{
	cout<<"Area is: "<<length*width<<endl;
}
int Rectangle::perimeter()
{
	cout<<"Perimeter is: "<<2*(length+width);
}
#endif