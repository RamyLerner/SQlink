#include <iostream>
#include <string>
#include "meeting_t.h"
#include "day_t.h"

using namespace std;

int main(){
	int input;
	float start, finish;
	string topic;
	Day_t day;
	do{
		cout << "type 1 to insert\ntype 2 to print\ntype 3 to find\ntype 4 to remove\ntype -1 to exit\n";
		cin >> input;
		switch (input){
			case 1: {cout << "enter start and finish times and topic: \n";
				cin >> start >> finish >> topic;
				try{
					Meeting_t* m = new Meeting_t(start, finish, topic);
					if (!day.insert(m))
						cout << "insertion did not occure\n";
				}
				catch (string st){
					cout << st << endl;
				}
				break;
			}
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