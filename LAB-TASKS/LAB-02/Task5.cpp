#include <iostream>
#include "calculator.h"
using namespace std;

int main()
{
	Calculator c;
	float num1,num2;
	char op;
	cout<<"Enter 1st num: "<<endl;
	cin>>num1;
	cout<<"Enter 2nd num: "<<endl;
	cin>>num2;
	cout<<"Enter operation: +,-,x,/"<<endl;
	cin>>op;
	if(op=='+')
	c.add(num1,num2);
	else if (op=='-')
	c.subtract(num1,num2);
	else if(op=='x')
	c.multiply(num1,num2);
	else if(op=='/')
	c.divide(num1,num2);
	else
	cout<<"Invalid"<<endl;
	
	return 0;
}