
//BITSET
	bitset < 10 > B;
	B[3] = 1;
	B[7] = 1;
	cout << B._Find_first(); //znajduje indeks pierwszego zapalonego bitu 
	cout << B._Find_next(8); //znajduje indeks pierwszego zapalonego bitu wiekszy niz 8
  	//jesli nie znajdzie, to zwroci rozmiar bitsetu(10)
//unique
	vector < int > V = {1, 3, 2, 1};
	sort(all(V));
	V.resize( distance(V.begin(), unique(all(V))) );

//builtin, mozna na koncu nazwy funkcji dodaj ll jesli argumentum jest unsigned long long
— Built-in Function: int __builtin_clz (unsigned int x)
Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.

— Built-in Function: int __builtin_ctz (unsigned int x)
Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.

— Built-in Function: int __builtin_popcount (unsigned int x)
Returns the number of 1-bits in x.

— Built-in Function: int __builtin_parity (unsigned int x)
Returns the parity of x, i.e. the number of 1-bits in x modulo 2.

/*
Maksymalna liczba dzielników dla:
Niewiekszych niz: 10^1 maksymalna liczba dzielnikow : 4
Niewiekszych niz: 10^2 maksymalna liczba dzielnikow : 12
Niewiekszych niz: 10^3 maksymalna liczba dzielnikow : 32
Niewiekszych niz: 10^4 maksymalna liczba dzielnikow : 64
Niewiekszych niz: 10^5 maksymalna liczba dzielnikow : 128
Niewiekszych niz: 10^6 maksymalna liczba dzielnikow : 240
Niewiekszych niz: 10^7 maksymalna liczba dzielnikow : 448
Niewiekszych niz: 10^8 maksymalna liczba dzielnikow : 768
Niewiekszych niz: 10^9 maksymalna liczba dzielnikow : 1344
Niewiekszych niz: 10^10 maksymalna liczba dzielnikow : 2304
Niewiekszych niz: 10^11 maksymalna liczba dzielnikow : 4032
Niewiekszych niz: 10^12 maksymalna liczba dzielnikow : 6720
Niewiekszych niz: 10^13 maksymalna liczba dzielnikow : 10752
Niewiekszych niz: 10^14 maksymalna liczba dzielnikow : 17280
Niewiekszych niz: 10^15 maksymalna liczba dzielnikow : 26880
Niewiekszych niz: 10^16 maksymalna liczba dzielnikow : 41472
Niewiekszych niz: 10^17 maksymalna liczba dzielnikow : 64512
*/
