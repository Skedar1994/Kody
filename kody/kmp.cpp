//mozna wyszukac wzorca s w tekscie z wywolujac funkcje pi na s + '#' + z
vector < int > kmp_pi(const string& s)
{
	vector < int > V(SZ(s), 0);
	int akt = 0;
	for(int i=1; i<SZ(s); i++)
	{
		while(akt > 0 && s[i] != s[akt])
		{
			akt = V[akt-1];
		}
		if (s[i] == s[akt])
			akt++;
		V[i] = akt;
	}
	return V;
}

//zwraca tablice dlugosci tekstu
vector < int > kmp(const string& wzorzec, const string& tekst)
{
	vector < int > V(SZ(tekst), 0);
	vector < int > P = kmp_pi(wzorzec);
	int akt = 0;
	for(int i=0; i<SZ(tekst); i++)
	{
		while(akt > 0 && (akt == SZ(wzorzec) || wzorzec[akt] != tekst[i]))
			akt = P[akt-1];
		if (wzorzec[akt] == tekst[i])
			akt++;
		V[i] = akt;
	}
	return V;
}
