#include "string_t.h"
#include <iostream>

using namespace std;

void opHandler(String_t &st, int op)
{
    char c;
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
    unsigned int len;
    char raw[STR_MAX_SIZE];
    char c;
    String_t s2;

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
             << "type 11 for getCaseSens()" << endl
             << "type 12 for setCaseSens()" << endl
             << "type 13 for getNumOfStrings()" << endl 
             << "type 14 for firstOcc()" << endl
             << "type 15 for lastOcc()" << endl
             << "type 16 for sustring operator()" <<endl
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
            cin >> s2;
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
            cin >> s2;
            s1.prepend(s2);
            break;
        }
        case 10:
        {
            cout << "enter a substring to check\n";
            cin >> s2;
            cout << s1.contains(s2) << endl;
            break;
        }
        case 11:
            cout << String_t::getCaseSens() << endl;
            break;
        case 12:
            cout << "enter flag value\n";
            cin >> op;
            String_t::setCaseSens(op);
            break;
        case 13:
            cout << String_t::getNumOfStrings << endl;
            break;
        case 14:
            cout << "enter char to find\n";
            cin >> c;
            cout << s1.firstOcc(c) << endl;
            break;
        case 15:
            cout << "enter char to find\n";
            cin >> c;
            cout << s1.lastOcc(c) << endl;
            break;
        case 16:
            cout << "enter start index and length\n";
            cin >> op >> len;
            s2 = s1(op, len);
            cout << s2 << endl;
            delete &s2;
            break;
        case -1:
            break;
        default:
            cout << "invalid input\n";
        }
    }
}