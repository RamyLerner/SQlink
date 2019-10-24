#include "virtio_t.h"
#include "asciiio_t.h"
#include "binio_t.h"
#include <iostream>

using namespace std;

template <class T>
void templRead(VirtIO_t* virtPtr){
	T elem;
	(*virtPtr) >> elem;
	cout << elem;
}

template <class T>
void templWrite(VirtIO_t* virtPtr){
	T elem;
	cout << "enter element\n";
	cin >> elem;
	(*virtPtr) << elem;
}

void readArr(VirtIO_t* virtPtr){
	long l;
	BinIO_t* binPtr = dynamic_cast<BinIO_t*>(virtPtr);
	if (binPtr != 0){
		(*binPtr) >> (void*)&l, sizeof(long);
		cout << l;
	}
}

void writeArr(VirtIO_t* virtPtr){
	long l = 123456789;
	BinIO_t* binPtr = dynamic_cast<BinIO_t*>(virtPtr);
	if (binPtr != 0)
		(*binPtr) << (void*)&l , sizeof(long);
}


void readHandler(VirtIO_t* virtPtr){
	char elemType;
	cout << "type 'i' for int, 'f' for float, 'c' for char, 'v' for void*\n";
	cin >> elemType;
	switch (elemType){
		case 'i': 
			templRead<int>(virtPtr);
			break;
		case 'f':
			templRead<float>(virtPtr);
			break;
		case 'c':
			templRead<char>(virtPtr);
			break;
		case 'v':
			readArr(virtPtr);
		default: cout << "invalid choice\n";
	}
}

void writeHandler(VirtIO_t* virtPtr){
	char elemType;
	cout << "type 'i' for int, 'f' for float, 'c' for char, 'v' for void*\n";
	cin >> elemType;
	switch (elemType){
		case 'i': 
			templWrite<int>(virtPtr);
			break;
		case 'f':
			templWrite<float>(virtPtr);
			break;
		case 'c':
			templWrite<char>(virtPtr);
			break;
		case 'v':
			writeArr(virtPtr);
		default: cout << "invalid choice\n";
	}
}

int main(){
	int input;
	string path, access;
	VirtIO_t* virtPtr = 0;
	size_t pos;

	cout << "type 1 for AsciiIO_t or 2 for BinIO_t\n";
	cin >> input;
	cout << "enter file name\n";
	cin >> path;
	cout << "enter access mode: r, w, r+ or w+\n";
	cin >> access;
	
	switch (input){
		case 1: virtPtr = new AsciiIO_t(path, access);
			break;
		case 2: virtPtr = new BinIO_t(path, access);
			break;
	}
	
	do{
		cout << "type 1 for >>\ntype 2 for <<\ntype 3 to get position\ntype 4 to set position\ntype 5 to get length\ntype -1 to exit\n";
		cin >> input;
		switch (input){
			case 1:
				readHandler(virtPtr);
				break;
			case 2:
				writeHandler(virtPtr);
				break;
			case 3:
				cout << virtPtr -> getPosition() << endl;
				break;
			case 4:
				cout << "enter new position" << endl;
				cin >> pos;
				if (virtPtr-> setPosition(pos))
					cout << "done\n";
				else
					cout << "position change failed\n";
				break;
			case 5:
				cout << virtPtr -> getLength() << endl;
		}
	}while (input != -1);
}