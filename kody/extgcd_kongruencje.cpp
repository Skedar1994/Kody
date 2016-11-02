#define LL long long

LL nwd;
pair < LL, LL > NWD (LL a, LL b)
{
    if (a==0)
    {
    	nwd = b;
      return make_pair(0, 1);
    }
    pair < LL, LL > P = NWD(b%a, a);
    pair < LL, LL > P2 = make_pair ((P.second - (b/a)*P.first), (P.first));
    if (b != nwd)
    	P2.ft %= (b/nwd), P2.sd %= (a/nwd);
    return P2; 
}

pair < LL, LL > dwie_kongr(pair < LL, LL> P1, pair < LL, LL > P2)
{
	pair < LL, LL > euk = NWD(P1.sd, P2.sd);
	LL nww = P1.sd / nwd * P2.sd;
	LL roz = (nww + P2.ft - P1.ft)%nww;
	if (roz % nwd != 0)
		return make_pair(0, 0);
	LL t = P1.ft % nwd;
	P1.ft /= nwd, P2.ft /= nwd;
	LL ans = (euk.ft * P1.sd * P2.ft + euk.sd * P2.sd * P1.ft + t )%nww;
	ans = (ans + nww)%nww;
	return make_pair(ans, nww);
}

//{2, 3} -> x przystaje do 2 mod 3
pair < LL, LL> uklad_kongr(const vector < pair < LL ,LL > >& V)
{
	assert(V.size() > 0);
	pair < LL, LL > ans = V[0];
	for(int i=1; i<SZ(V); i++)
	{
		ans = dwie_kongr(ans, V[i]);
		if (ans.sd == 0)
			return make_pair(0, 0); 
	}
	return ans;
}
