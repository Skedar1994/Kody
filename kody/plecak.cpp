bitset<MAXN> pakuj(const vector < pair <int, int> >& V)
{
	bitset<MAXN> B = 1;
	map < int, int > M;
	for(auto& el : V)
		M[el.ft]+=el.sd;
	for(auto& el : M){
		rep(_, 0, 2 - (el.sd & 1))
				B |= B << el.ft;
		if((el.sd >> 1) - 1 + (el.sd & 1))
			M[el.ft << 1] += (el.sd >> 1) - 1 + (el.sd & 1);
	}	
    return B;
}
