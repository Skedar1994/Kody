
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
