#include <map>
#include <string>
#include <iostream>
using namespace std;

string add(string phone)
{
    string key; int bfr = 0; char val[8];
    bfr = stoi(phone.substr(0,2));
    sprintf (val, "%.i", bfr); key += val;
    bfr = stoi(phone.substr(3,6));
    sprintf (val, "%.i", bfr); key += val;
    bfr = stoi(phone.substr(6,8));
    sprintf (val, "%.i", bfr); key += val;
    return key;
}

int main()
{
  int phone_num = 0;
  string operation, phone, sname;
  map<int, string> phonebook;
  map<int, string>::iterator it;
  while (operation != "q")
  {
    cout << "Insert operation: ";
    cin >> operation;
    if (operation == "add")
    {
      cout << "Insert phone number: ";
      cin >> phone;
      try
      { phone_num = stoi(add(phone)); }
      catch (const exception& e)
      { cerr << "Input error: " << e.what() << endl; continue; }
      it = phonebook.find(phone_num);
      if (it->first == phone_num)
      { cerr << "Phone is already reserved" << endl; continue; }
      cout << "Insert Surname: ";
      cin >> sname;
      phonebook.insert(pair<int, string> (phone_num, sname));
    }
    else if (operation == "phone")
    {
      cout << "Insert phone number: ";
      cin >> phone;
      try
      { phone_num = stoi(add(phone)); }
      catch (const exception& e)
      { cerr << "Input error: incorrect phone _" << e.what() << endl; continue; }
      it = phonebook.find(phone_num);
      if (it->first == phone_num)
        cout << "#" << it->first << " " << it->second << endl;
      else cerr << "Not found" << endl;
    }
    else if (operation == "sname")
    {
      bool ch = false;
      cout << "Insert Surname: ";
      cin >> sname;
      for (it = phonebook.begin(); it != phonebook.end(); ++it)
      {
        if (it->second == sname)
        { cout << "#" << it->first << " " << it->second << endl; ch = true; }
      }
      if (!ch) cerr << "Not found" << endl;
    }
    else if (operation != "q") cerr << "Input error: incorrect operation" << endl;
  }
}
