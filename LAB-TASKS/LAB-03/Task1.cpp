#include <iostream>
#include <iomanip>
#include "header.h"
int main()
{
	Product p;
	p.setname("");
	p.setprice(-50);
	p.setquantity(-2);
	cout<<" "<<endl;
	p.setname("Laptop");
	p.setprice(1200.50);
	p.setquantity(5);
	
	cout<<"Product: "<< p.getname() << endl;
	cout<<"Price: $"<< fixed << setprecision(2) << p.getprice() << endl;
	cout<<"Quantity: "<< p.getquantity() << endl;
return 0;
}