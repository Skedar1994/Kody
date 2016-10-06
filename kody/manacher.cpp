#include <iostream>
#include <string>

using namespace std;

string s;
int tab[1000005];

void manacher()//tylko dla parystych, zdublowac kazda litere!
{
    int naj=0, r = 0, aktr;
    for(int i=0; i<s.size(); i++)
    {
        aktr = 0;
        if (naj+r > i)
            aktr = min(tab[naj-(i-naj)], r+naj-i);
        while(i-aktr >= 0 && i+aktr+1<s.size() && s[i+aktr+1] == s[i-aktr])
            aktr++;
        tab[i] = aktr;
        if (aktr+i > naj+r)
        {
            naj = i;
            r = aktr; 
        }
    }
}

int main()
{

    return 0;
}
