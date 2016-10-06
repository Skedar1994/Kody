#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1<<17;
int load[2*N], sub[2*N], odp[200000];


void dodaj(int a, int b, int v)
{
          int l = N + a, r = N + b;
          int length = 1; // długość przedziałów na aktualnie odwiedzanym poziomie
          load[l] += v;
          sub[l] += v;
          // jeśli a==b to nie dodajemy obciążenia dwukrotnie
          if(r != l)
          {
                    load[r] += v;
                    sub[r] += v;
          }
          while(l >= 1)
          {
                    // jeśli l i r nie są sąsiadami w drzewie, to sprawdzamy czy
                    // nie trzeba uaktualnić węzłów wewnętrznych
                    if(l < r - 1)
                    {
                              if(l % 2 == 0) // l jest lewym synem swego ojca
                              {
                                        load[l + 1] += v;
                                        sub[l + 1] += v * length;
                              }
                              if(r % 2 == 1) // r jest prawym synem swego ojca
                              {
                                        load[r - 1] += v;
                                        sub[r - 1] += v * length;
                              }
                    }
                    // jeśli l i r nie są liśćmi, to uaktualniamy ich wartości sub
                    if(r < N)
                    {
                              sub[l] = sub[2 * l] + sub[2 * l + 1] + load[l] * length;
                              sub[r] = sub[2 * r] + sub[2 * r + 1] + load[r] * length;
                    }
                    // przechodzimy poziom wyżej
                    l /= 2; r /= 2; length *= 2;
          }
}

int znajdzsume(int a, int b)
{
          int l = N + a, r = N + b;
          int length = 1; // długość przedziałów na aktualnie odwiedzanym poziomie
          // w llen i rlen pamiętamy ile punktów przedziału [a,b] zawiera
          // się w poddrzewie o korzeniu l i r odpowiednio
          int llen = 1, rlen = (a != b ? 1 : 0);
          int res = 0;
          while(l >= 1)
          {
                    // sumujemy obciążenia z węzłów l i r
                    res += llen * load[l] + rlen * load[r];
                    // jeśli l i r nie są sąsiadami w drzewie to sprawdzamy czy
                    // istnieją węzły wewnętrzne z obciążeniem
                    if(l < r - 1)
                    {
                              if(l % 2 == 0) // l jest lewym synem swego ojca
                              {
                                        res += sub[l + 1];
                                        llen += length;
                              }
                              if(r % 2 == 1) // r jest prawym synem swego ojca
                              {
                                        res += sub[r - 1];
                                        rlen += length;
                              }
                    }
                    l /= 2; r /= 2; length *= 2;
          }
          return res;
}
int main()
{
}
