#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
using namespace std;
class Product
{
	//data members
	private:
		string name;
		float price;
		int quantity;
	//member functions
	public:
	void setname(string n)
	{
		if(!n.empty())
		{
			name=n;
		}
		else
		{
			cout<<"Name can't be empty."<<endl;
		}
	}
	
	void setprice(double p)
	{
		if(p>0)
		{
			price=p;
		}
		else
		{
			cout<<"invalid price."<<endl;
		}
	}
	void setquantity(int q)
	{
		if(q>=0)
		{
			quantity=q;
		}
		else
		{
			cout<<"invalid quantity."<<endl;
		}
	}
	//getter functions
	string getname() {return name;}
	float getprice() {return price;}
	int getquantity(){return quantity;}
};


#endif