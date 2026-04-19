#include <iostream>
using namespace std;

class Rectangle
{
	private:
		float length, width, area;

	public:
		Rectangle()
		{
			length = 1.0;
			width = 1.0;
		}

		Rectangle(float l, float w)
		{
			length = l;
			width = w;
		}

		Rectangle(float l)
		{
			length = l;
			width = l;
		}

		void calculateArea()
		{
			area = length * width;
		}

		void display()
		{
			cout << "Area: " << area << endl;
		}
};

int main()
{
	Rectangle obj1(2, 3);
	obj1.calculateArea();
	obj1.display();

	Rectangle obj2(4);
	obj2.calculateArea();
	obj2.display();

	Rectangle obj3;  
	obj3.calculateArea();
	obj3.display();

	return 0;
}