int ktore = 1;
void rob(vector < int>& V)
{
	cout << ktore << ": " ;
	for(auto& el : V)
		cout << el << " ";
	cout << endl;
	ktore++;
}

void rek(int n, int mini, vector < int >& V)
{
	if (n == 0)
	{
		rob(V);
		return;
	}
	if (n < mini)
		return;
	for(int i = mini; i<=n; i++)
	{
		V.pb(i);
		rek(n-i, i, V);
		V.pop_back();
	}
	return;
}

int main()
{
	vector < int > V;
	rek(10, 1, V);//Pierwsze to liczba do rozlozenia
	return 0;
}
