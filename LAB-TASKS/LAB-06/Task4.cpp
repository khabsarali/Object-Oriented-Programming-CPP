#include <iostream>
using namespace std;
class Device
{
	private:
		string *device_name;
		string *device_id;
	public:
		Device(string name, string id)
		{
			device_name = new string(name);
			device_id = new string(id);
			cout<<"Parent class constructor, Memory allocated on heap.."<<endl;
		}
		virtual ~Device()
		{
			delete device_name;
			delete device_id;
			cout<<"Parent class destructor called."<<endl;
		}
		string getname(){ return *device_name; }
		string getid(){ return *device_id; }
};
class Sensor : public Device
{
	private:
		string *sensor_type;
		float *sensor_value;
	public:
		Sensor(string name, string id, string type, float value):Device(name,id)
		{
			sensor_type= new string(type);
			sensor_value= new float(value);
			cout<<"Childc class constructor, Memory allocated on heap..."<<endl;
		}
	~Sensor(){
		delete sensor_type;
		delete sensor_value;
		cout<<"Child class constructor called."<<endl;
	}
	void showdata()
	{
		cout<<"----Device Details----"<<endl;
		cout<<"Device name: "<<getname()<<endl;
		cout<<"Device id: "<<getid()<<endl;
		cout<<"Sensor type:"<<*sensor_type<<endl;
		cout<<"Sensor value:"<<*sensor_value<<endl;	
		cout<<"*****************************"<<endl;
	}
};
int main()
{
	Sensor *s1= new Sensor("Thermomemter", "TH-101", "Temperature(Ceslius)",36.9);
	s1->showdata();
	delete s1;
	return 0;
}