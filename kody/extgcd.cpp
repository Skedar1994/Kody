#define LL long long
pair < LL, LL > NWD (LL a, LL b)
{
    pair < LL, LL > P;
    if (b<a)
    {
        P = NWD(b, a);
        swap(P.first, P.second);
        return P;
    }
    if (a==0)
        return make_pair(0, 1);
    P = NWD(b%a, a);
    pair < LL, LL > P2 = make_pair(P.second - (b/a)*P.first, P.first);
    return P2; 
}
