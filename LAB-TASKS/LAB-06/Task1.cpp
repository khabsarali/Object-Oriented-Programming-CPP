#include <iostream>
using namespace std;
class Product
{
	private:
		string name;
		int price;
	public:
		Product()
		{
			name="Not Assigned";
			price=0;
		}
		Product(string n, int p)
		{
			name=n;
			price=p;
		}
		void displayProduct()
		{
			cout<<"----Details----"<<endl;
			cout<<"Name: "<<name<<endl;
			cout<<"Price: "<<price<<endl;
		}
};
class Electronics : public Product
{
	private:
		int warranty_year;
	public:
		//Constructor chaining
		Electronics(string n, int p, int warranty) : Product(n,p)
		{
			warranty_year=warranty;
		}
		void display()
		{
			displayProduct();
			cout<<"Warranty: "<<warranty_year<<" years"<<endl;
		}
};
int main()
{
	Electronics e("TV",78000,4);
	e.display();
	
	return 0;
}