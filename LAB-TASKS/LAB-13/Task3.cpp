#include <iostream>
using namespace std;
 
template <class T>
class Pair
{
	private:
		T first,second;
	public:
		//constructor
		Pair(T a, T b)
		{
			first=a;
			second=b;
		}
		T getfirst()
		{
			return first;
		}
		T getsecond()
		{
			return second;
		}
		void display()
		{
			cout<<"First: "<<first<<endl;
			cout<<"second: "<<second<<endl;
			cout<<"\n";
		}
};
int main()
{
	Pair<int> p1(10,20);
	Pair<double> p2(23.4,19.9);
	Pair<string> p3("Hello","world");
	cout<<"For integers\n";
	p1.display();
	cout<<"For double\n";
	p2.display();
	cout<<"For string\n";
	p3.display();
return 0;
}
		