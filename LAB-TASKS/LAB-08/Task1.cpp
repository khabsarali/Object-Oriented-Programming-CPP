#include<iostream>
using namespace std;
class shape{
	public:
		virtual double area(){
			return 0;
		}
};
class rectangle:public shape{
	private:
		int lenght;
		int width;
	public:
	rectangle(int l, int w){
		lenght=l;
		width=w;
	}
	double area()override{
		return lenght*width;
	}
};
class circle:public shape{
	private:
		int radius;
	public:
	circle( int r){
		radius=r;
	}
	double area()override{
		return 3.14 *radius *radius;
	}
};
 int main(){
 	shape *s= new rectangle(5,3);
 	shape *s1= new circle(2);
 	cout<<"The area of rectangle is"<<s->area()<<endl;
 	cout<<"The area of circle is"<<s1->area()<<endl;
 	return 0;
 }