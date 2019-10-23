#include "virtio.h"
#include "asciiio.h"
#include "binio.h"
#include <iostream>

using namespace std;

int main(){
	int input;
	string path, access;
	VirtIO_t* virtPtr = 0;
	double arr[3];

	cout << "type 1 for AsciiIO_t or 2 for BinIO_t\n";
	cin >> input;
	cout << "enter file name\n"
	cin >> path;
	cout << "enter access mode: r, w, r+ or w+\n";
	cin >> access;
	
	switch (input){
		case 1: virPtr = new AsciiIO_t(path, access);
			break;
		case 2: virPtr = new BinIO_t(path, access);
			break;
	}
	
	do{
		cout << "type 1 for >>\ntype 2 for <<\ntype 3 to get position\ntype 4 to set position\ntype 5 to get length\ntype -1 to exit\n";
		cin >> input;
		switch (input){
			case 1: 
			case 2: day.print();
				break;
			case 3: {cout << "enter starting hour\n";
				cin >> start;
				Meeting_t* m = day.find(start);
				if (m == 0)
					cout << "meeting was not found\n";
				else
					cout << "Meeting from " << m->getStart() << " until " << m->getEnd() << " about: " << m->getTopic() << endl;	
				break;
			}
			case 4: cout << "enter starting hour\n";
				cin >> start;
				if(!day.remove(start))
					cout << "meeting was not found\n";
				else
					cout << "done\n";
		}
	}while (input != -1);
}