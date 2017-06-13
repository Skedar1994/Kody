//RMQ
//Pamięć O(nlogn)
//Query w O(1)

const int MAXN=110000, MAXLOGN=20;

int A[MAXN];
int M[MAXN][MAXLOGN];
int n,l,r;

void Compute_ST(int N){
    int i,j;
    for(i=0;i<N;i++)
        M[i][0]=i;
    for(j=1;(1<<j) <=N ;j++){
        for(i=0;i+(1<<(j-1))<N;i++){
            if(A[M[i][j-1]]<=A[M[i+(1<<(j-1))][j-1]]) //'<' na '>', by dostać element maksymalny
                M[i][j]=M[i][j-1];
            else
                M[i][j]=M[i+(1<<(j-1))][j-1];
        }
    }
}

int RMQ(int s,int e){
    int k=e-s;
    k=31-__builtin_clz(k+1); // k = log(e-s+1)
    if(A[M[s][k]]<=A[M[e-(1<<k)+1][k]]) //'<' na '>', by dostać element maksymalny
        return M[s][k];
    return M[e-(1<<k)+1][k];
}


int main(){
  cin>>n;
  for(int i=0;i<n;i++) cin>>A[i];
  Compute_ST(n);//preprocessing
  RMQ(a,b);//włącznie, włącznie, zwraca indeks
  
  
}
