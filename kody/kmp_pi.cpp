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
