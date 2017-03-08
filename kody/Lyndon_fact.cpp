//wsyzstko dziala w czasie liniowym
//Lyndon_fact to podzial s na w_1, w_2, w_3, ..., w_k (s = w_1 + ... + w_k) takie, ze;
//w_1 >= w_2 >= ... >= w_k (leksykograficznie)
//w sa slowami Lyndona(sa swoimi scisle najwiekszymi przesunieciami cyklicznymi

vector < string > Lyndon_fact(const string& s)
{
	int start = 0, p = 0, m = 1;
	vector < string > odp;
	while(start < SZ(s))
	{
		if (m == SZ(s) || s[p] > s[m])
		{
			int d = m-p;
			while(start <= p)
			{
				odp.push_back(string(s, start, d));
				start += d;
			}
			p = start;
			m = p+1;
			continue;
		}
		if (s[p] == s[m])
			p++;
		else
			p = start;
		m++;
	}
	return odp;
}


int minimalne_leksykograficznie_przesuniecie_cykliczne(string s)
{
	int roz = SZ(s), pop = 0, ind = 1, a;
	s += s;
	auto v = Lyndon_fact(s);
	string ost = v[0];
	a = SZ(v[0]);
	while(a < roz)
	{	
		if (v[ind] != ost)
			pop = a;
		ost = v[ind];
		a += SZ(v[ind]);
		ind++;
	}
	return pop;
}
