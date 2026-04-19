#include <iostream>
#include <string>
using namespace std;
class bankAccount
{
	private:
		string accountNumber, accountHolder;
		double balance;
	public:
		bankAccount(string account_no, string account_holder, double Balance)
		{
			accountNumber=account_no;
			accountHolder=account_holder;
			balance=Balance;
		}
	void display()
	{
		cout<<"Account Number: "<<accountNumber<<endl;
		cout<<"Account Holder: "<<accountHolder<<endl;
		cout<<"Balance: "<<balance<<endl;
	}
	
};
int main()
{
	bankAccount b("PK0309800780100","Muhammad Awais",10000);
	b.display();
	return 0;
}