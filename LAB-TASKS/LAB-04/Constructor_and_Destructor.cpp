#include <iostream>
using namespace std;
class Locker
{
	public:
		Locker()
		{
			cout<<"Locker allocated to customer."<<endl;
		}
		~Locker()
		{
			cout<<"Locker returned by customer."<<endl;
		}
};
int main()
{
	Locker locker1;
	
	
	return 0;
}