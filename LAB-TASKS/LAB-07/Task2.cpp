#include <iostream>
using namespace std;

class Calculator{
	public:
		double addition(double a, double b){
			return a+b;
		}
		
		double multiplication(double a, double b){
			return a*b;
		}
};

class Student{
	private:
		Calculator *calc;
	public:
		Student(Calculator *c){
			calc = c;
		}
		
		void addition_result(double a, double b){
			if(calc){
				cout<<"Result (Addition) : "<<calc->addition(a,b)<<endl;
			}
		}
		
		void multiplication_result(double a, double b){
			if(calc){
				cout<<"Result (Product) : "<<calc->multiplication(a,b)<<endl;
			}
		}
		
};

int main(){
	
	Calculator c;
	
	Student s1(&c);
	Student s2(&c);
	
	cout<<"~~Student 01~~"<<endl;
	s1.addition_result(5.5,6.5);
	s1.multiplication_result(5.0,6.0);
	
	cout<<endl;
	
	cout<<"~~Student 02~~"<<endl;
	s2.addition_result(4.5,3.5);
	s2.multiplication_result(3.0,2.0);
	
	return 0;
}