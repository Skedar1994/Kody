#define MAXN 100001

int odl[MAXN], str[MAXN], para[MAXN], odw[MAXN];
vector < vector < int > > V;

bool DFS(int v, int ojciec, int zostalo)
{
    if (zostalo < 0)
        return false;
    odw[v] = 1;
    if (!str[v])
    {
        if (!para[v])
            return para[v] = ojciec;
        if (DFS(para[v], v, zostalo-1))
            return para[v] = ojciec;
        return false;
    }
    for(int i=0; i<V[v].size(); i++)
        if (odl[ V[v][i] ] == odl[v] + 1 && !odw[ V[v][i] ] && DFS(V[v][i], v, zostalo-1))
            return para[v] = V[v][i];
    return false;
}

int sciezki(int n) 
{
    memset(odl, 0, 4*(n+1));
    memset(odw, 0, 4*(n+1));
    int minodl = 2*MAXN, ilezmian = 0;
    queue < pair <int, int> > Q;
    for(int i=1; i<=n; i++)
        if (str[i] && !para[i])
        {
            Q.push(make_pair(i, 1));
            odl[i] = 1;
        }
    while(!Q.empty())
    {
        int akt = Q.front().first, od=Q.front().second; Q.pop();
        if (!str[akt])
        {
            if (para[akt])
            {
                Q.push(make_pair(para[akt], od+1));
                odl[ para[akt] ] = od+1;
            }
            else
                minodl = min(minodl, od);                
            continue;
        }
        for(int i=0; i<V[akt].size(); i++)
            if (odl[ V[akt][i] ] == 0)
            {
                Q.push(make_pair(V[akt][i], od+1));
                odl[ V[akt][i] ] = od+1;
            }
    }
    for(int i=1; i<=n; i++)
        if (!odw[i] && str[i] && !para[i])
            ilezmian += DFS(i, -1, minodl-1);
    return ilezmian;
}

int matching(int n)
{
    int ile = 0, akt;
    while(akt = sciezki(n))
        ile+=akt;
    return ile;
}
/*
1. W str[i] kazdy wierzcholek powinien miec nr 0 lub 1 -> w zaleznosci od tego, po ktorej stronie grafu dwudzielnego jest
2. Wierzcholki numerujemy od 1!
*/
