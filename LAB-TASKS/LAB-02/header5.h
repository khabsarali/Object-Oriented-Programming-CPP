#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <iostream>
#include <string>
using namespace std;
class Calculator
{
	public:
	//data members
	float num1, num2;
	//member functions (outside the class)
	void add(float a, float b);
	void subtract(float a, float b);
	void multiply(float a, float b);
	void divide(float a, float b);
};
void Calculator::add(float a, float b)
{
	cout<<"Sum is: "<<a+b;
}
void Calculator::subtract(float a, float b)
{
	cout<<"Difference is: "<<a-b;
}
void Calculator::multiply(float a, float b)
{
	cout<<"Product is: "<<a*b;
}
void Calculator::divide(float a, float b)
{
	cout<<"Division is: "<<a/b;
}
#endif