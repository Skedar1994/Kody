struct Bignum //tylko na dodatnich, mnozenie wolne
{
    static const ll baza = 10LL, dl = 1;
//    ll baza = 1000000000000000LL, dl = 15;
    vector < ll > V;
    Bignum(ll x)
    {
        V = {x};
        popraw();
    }
    Bignum()
    {
        V = {0};
    }
    Bignum(string s)
    {
        reverse(all(s));
        V.resize(SZ(s)/dl+2);
        vector < ll > Z = {1};
        for(int i=1; i<=dl; i++)
            Z.pb(Z.back() * 10);
        //return;
        for(int i=0; i<SZ(s); i++)
        {
            ll cyfra = s[i] - '0';
            ll komorka = i/dl;
            ll ile_zer = i%dl;
            //cout << i << " " << komorka << endl;
            V[komorka] += cyfra * Z[ile_zer];
            //cout << i << endl;
        }
        //return;
        popraw();
    }
    Bignum(string z, int a, int b)
    {
        string s;
        for(int i=a; i<b; i++)
            s += z[i];
        (*this) = Bignum(s);
    }

    void popraw()
    {
        while(SZ(V) > 1 && V.back() == 0)
            V.pop_back();
        for(int i=0; i+1<SZ(V); i++)
        {
            if (V[i] >= baza)
            {
                V[i+1] += V[i]/baza;
                V[i] %= baza;
            }
        }
        while(V.back() >= baza)
        {
            ll ile = V.back() / baza;
            V.back() %= baza;
            V.pb(ile);
        }
    }
    bool operator<(const Bignum& b)
    {
        if (SZ(V) > SZ(b.V))
            return false;
        if (SZ(V) < SZ(b.V))
            return true;

        for(int i = SZ(V)-1; i>=0; i--)
        {
            if (V[i] > b.V[i])
                return false;
            if (V[i] < b.V[i])
                return true;
        }
        return false;
    }
    Bignum& operator+=(const Bignum& b)
    {
        if (SZ(V) <= SZ(b.V))
            V.resize(SZ(b.V));
        for(int i=0; i<SZ(b.V); i++)
            V[i] += b.V[i];
        popraw();
        return *this;
    }
    Bignum& operator-=(const Bignum& b)
    {
    	assert(! ( (*this) < b ));
        if (SZ(V) <= SZ(b.V))
            V.resize(SZ(b.V));
        for(int i=0; i<SZ(b.V); i++)
            V[i] -= b.V[i];
        for(int i=0; i+1<SZ(V); i++)
        	if (V[i]< 0)
        	{
        		V[i] += baza;
        		V[i+1]--;
        	}
        popraw();
        return *this;
    }
    Bignum operator+(const Bignum& b)
    {
        Bignum res;
        res = (*this);
        res += b;
        return res;
    }
    Bignum operator-(const Bignum& b)
    {
        Bignum res;
        res = (*this);
        res -= b;
        return res;
    }
    Bignum operator*(const Bignum& b)
    {
    	int s1 = SZ(b.V);
    	int s2 = SZ(V);
    	vector < ll > resV(s1+s2, 0);
    	for(int i=0; i<s1; i++)
    		for(int j=0; j<s2;j++)
    			resV[i+j] += V[j] * b.V[i];
        Bignum res;
        res.V = resV;
        res.popraw();
        return res;
    }
    void wypisz()
    {
        cout << V.back();
        //cout.width(dl);
        //cout.fill('0');
        for(int i = SZ(V)-2; i>=0; i--)
        {
            stringstream ss;
            ss << V[i];
            string s = ss.str();
            while(SZ(s)< dl)
                s = "0" + s;
            cout << s;
        }
        cout<<"\n";
        //cout << endl;
    }
};
