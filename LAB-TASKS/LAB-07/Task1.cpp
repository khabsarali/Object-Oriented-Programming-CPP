#include <iostream>
using namespace std;

class Display{
	private:
		double final_value;
	public:
		Display(){
			final_value = 0.0;
		}
		
		double show_result(double value){
			final_value = value;
			cout<<"Result : "<<final_value<<endl;
		}
	
		double getfinal_value() const {return final_value;}
	
	
};

class Calculator{
	private:
		Display display;
	public:
		Calculator(){} //Constructor...
		
		void add(double a, double b){
			double result = a + b;
			display.show_result(result);
		}
		
		void multiply(double a, double b){
			double result = a * b;
			display.show_result(result);
		}
		
		void show_previous_result() const {
			cout<<"Previous Result : "<<display.getfinal_value()<<endl;
		}
		
};

int main(){
	Calculator c1;
	c1.add(6.4, 5.6);
	c1.multiply(1.5, 3.0);
	c1.show_previous_result();
	
	return 0;
}