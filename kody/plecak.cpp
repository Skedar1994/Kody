/*
dajemy przez referencje bitset w ktorym chcemy miec wynik i vector z rzeczami do zapakowania
*/

const int MAXN = 1000005;

void pakuj(bitset < MAXN >& B, const vector < int >& V)
{
	B = 1;
	map < int, int > M;
	for(auto& el : V)
		M[el]++;
	for(auto& el : M)
	{
		if (el.sd < 200)
		{
			for(int i=0; i<el.sd; i++)
				B |= (B<<el.ft);
			continue;
		}
		vector < int > Ile(MAXN, IINF);
		for(int i=0; i<MAXN-el.ft; i++)
		{
			if (B[i])
				Ile[i] = 0;
			Ile[i+el.ft] = min(Ile[i+el.ft], Ile[i] + 1);
			if (Ile[i] <= el.sd) 
				B[i] = true;
		}
		for(int i=MAXN-el.ft; i<MAXN; i++)
			if (Ile[i] <= el.sd)
				B[i] = true;
	}
}

bitset<MAXN> pakuj(const vector < int >& V)
{
	bitset<MAXN> B = 1;
	map < int, int > M;
	for(auto& el : V)
		M[el]++;
    	for(auto& el : M){
        	rep(_, 0, 2 - (el.sd & 1))
            		B |= B << el.ft;
        	if((el.sd >> 1) - 1 + (el.sd & 1))
           		M[el.ft << 1] += (el.sd >> 1) - 1 + (el.sd & 1);
   	}	
    	return B;
}
