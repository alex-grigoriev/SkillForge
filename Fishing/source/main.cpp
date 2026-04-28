#include "Fishing.h"

int main()
{
    Field* field[9];
    load(*field);
    bool ch = true;
    while(ch)
    {
        try
        {
            cout << "&" << endl;
            ponds(*field);
        }
        catch(const exception& e)
        {
            ch = false;
            cerr << e.what();
        }
    }
}