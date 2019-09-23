#include "string_t.h"
#include <iostream>

using namespace std;

void opHandler(String_t &st, int op)
{
    char raw[STR_MAX_SIZE];
    cout << "enter second operand string\n";
    cin >> raw;
    String_t s2(raw);
    switch (op)
    {
    case 1:
        cout << (st < s2) << endl;
        break;
    case 2:
        cout << (st > s2) << endl;
        break;
    case 3:
        cout << (st <= s2) << endl;
        break;
    case 4:
        cout << (st >= s2) << endl;
        break;
    case 5:
        cout << (st == s2) << endl;
        break;
    case 6:
        cout << (st != s2) << endl;
        break;
    case 7:
        (st += s2).printString();
        break;
    }
}

int main()
{
    int input = 0, op;
    char raw[STR_MAX_SIZE];
    char c;

    cout << "creating a new object. insert a string:\n";
    cin >> raw;
    String_t s1(raw);
    while (input != -1)
    {
        cout << "type 1 for getLength()" << endl
             << "type 2 for setString()" << endl
             << "type 3 for subscript" << endl
             << "type 4 to compare" << endl
             << "type 5 to print and test operator <<" << endl
             << "type 6 for upperCase()" << endl
             << "type 7 for lowerCase()" << endl
             << "type 8 for operator selection" << endl
             << "type 9 for prepend()" << endl
             << "type 10 for contains()" << endl
             << "-1 to exit" << endl;
        cin >> input;
        switch (input)
        {
        case 1:
            cout << "length: " << s1.getLength() << endl;
            break;
        case 2:
            cout << "insert string to set:\n";
            cin >> raw;
            s1.setString(raw);
            break;
        case 3:
            cout << "insert index number:\n";
            cin >> op;
            cout << s1[op] << endl;
            if (s1[op] != 0)
            {
                cout << "change to:" << endl;
                cin >> c;
                s1[op] = c;
            }
            break;
        case 4:
        {
            cout << "enter a string to compare with\n";
            cin >> raw;
            String_t s2(raw);
            cout << "comparison result: " << s1.compareString(s2) << endl;
            break;
        }
        case 5:
            s1.printString();
            cout << endl;
            break;
        case 6:
            s1.toUpperString();
            break;
        case 7:
            s1.toLowerString();
            break;
        case 8:
            cout << "type 1 for <\ntype 2 for >\ntype 3 for <=\ntype 4 for >=\ntype 5 for ==\ntype 6 for !=\ntype 7 for += \n";
            cin >> op;
            opHandler(s1, op);
            break;
        case 9:
        {
            cout << "enter a string to prepend\n";
            cin >> raw;
            String_t s2(raw);
            s1.prepend(s2);
            break;
        }
        case 10:
        {
            cout << "enter a substring to check\n";
            cin >> raw;
            String_t s2(raw);
            cout << s1.contains(s2) << endl;
            break;
        }
        case -1:
            break;
        default:
            cout << "invalid input\n";
        }
    }
}