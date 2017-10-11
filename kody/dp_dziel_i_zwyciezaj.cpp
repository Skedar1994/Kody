ll dp[21][100005];        
void ComputeDP(int i, int skad, int dokad, int klewo, int kprawo)
{
	if (skad >= dokad)
		return;
	int srodek = (skad + dokad)/2;
	dp[i][srodek] = INF;
	int najk = -1;
	for(int k=klewo; k<min(srodek, kprawo); k++)
	{
		int koszt = Ckoszt(k+1, srodek);//koszt za wziecie przedzialu wlacznie <k+1, srodek>
		if (dp[i][srodek] > dp[i-1][k] + koszt)
		{
			dp[i][srodek] = dp[i-1][k] + koszt;
			najk = k;
		}
	}
	ComputeDP(i, skad, srodek, klewo, najk+1);
	ComputeDP(i, srodek+1, dokad, najk, kprawo);
}        

//funkcje ponizej trzeba wywolac   
void compute_full_dp(int n, int k)
{
	//dp[0] liczymy wczesniej recznie, zwykla tablice indeksujemy od 1, stad wynik ostateczny jest w dp[k-1][n]
	for(int i=1; i<k; i++)
	{
		DBG(i);
		ComputeDP(i, 1, n+1, 1, n+1);
	}
}
