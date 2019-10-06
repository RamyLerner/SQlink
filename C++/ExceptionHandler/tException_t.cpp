#include "tException_t.h"
#include <iostream>
#include <string>
using namespace std;

int getIndex(){
	int i;
	cout << "enter elemnt index to retrieve from arr[6]" << endl;
	cin >> i;
	if (i >= 6)
		throw TException_t<int>(i, "Index too big", __FILE__, __LINE__);
	if (i < 0)
		throw TException_t<std::string>("oops", "Negative Index", __FILE__, __LINE__);
	return i;
}

int main(){
	int arr[6] = {0};
	try {
		cout << arr[getIndex()];
	}
	catch (const TException_t<int>& excep){
		excep.print();
	}
	catch (const TException_t<std::string>& excep){
		excep.print();
	}
}