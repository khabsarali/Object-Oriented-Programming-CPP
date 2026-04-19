#include <iostream>
using namespace std;

class Printer 
{
public:
    void print_document()
	{
        cout << "Printing document..." << endl;
    }
};


class Scanner
{
public:
    void scan_document()
	{
        cout << "Scanning document..." << endl;
    }
};


class Photocopier : public Printer, public Scanner
{
public:
    void photocopy()
	{
        cout << "Photocopy process started:" << endl;
        	cout<<""<<endl; 
        scan_document(); 
        print_document(); 
        cout << "Photocopy completed." << endl;
    }
};

int main() {
    Photocopier p;

    cout << "--- Using Photocopier as Printer ---" << endl;
    p.print_document();

    cout << "\n--- Using Photocopier as Scanner ---" << endl;
    p.scan_document();

    cout << "\n--- Using Photocopier to Photocopy ---" << endl;
    p.photocopy();

    return 0;
}