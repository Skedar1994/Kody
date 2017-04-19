//http://blog.ruofeidu.com/treap-in-45-lines-of-c/
const int INF = 200000000; 
 
class treap{
public:
    class node{
    public:
        int x,y,c; 
        node *l,*r; 
        node(int data=0):x(data),c(0),l(0),r(0){y=((rand()<<15)+rand())%INF;}
    };
    node *root, *null; 
public:
    treap(){null=new node(); null->l=null->r=null; null->y=INF; root=null; }
    void update(node*&p){ if(p!=null){p->c=p->l->c+p->r->c+1; }}
    void lr(node *&p){ node *q=p->l; p->l=q->r; q->r=p; update(p); update(q); p=q; }
    void rr(node *&p){ node *q=p->r; p->r=q->l; q->l=p; update(p); update(q); p=q; }
    void ins(node *&p, int x){
        if (p==null){ p=new node(x); p->l=p->r=null; p->c=1; } else
        if (x<p->x) { ins(p->l,x); if(p->l->y<p->y) lr(p); } else
                    { ins(p->r,x); if(p->r->y<p->y) rr(p); }
        update(p);
    }
    void del(node *&p, int x){
        if (p==null) return; 
        if (p->x==x) del(p); else
        if (x<p->x) del(p->l,x); else del(p->r,x);
        if (p!=null) update(p);
    }
    void del(node *&p){
        if (p->l==null&&p->r==null) {delete p; p=null; return; }
        if (p->l->y<p->r->y) {lr(p); del(p->r); } else {rr(p); del(p->l); }
        update(p); 
    }
    bool find(node *&p, int x){
        if(p==null) return false; 
        if (x==p->x) return true; 
        if (x<p->x) return find(p->l,x); else return find(p->r,x); 
    }
    int rfs(node *&p, int k){
        if (k<=p->l->c) return rfs(p->l,k); else
        if (k==p->l->c+1) return p->x; else return rfs(p->r,k-p->l->c-1); 
    }
    
    void ins(int x){ ins(root,x); }
    void del(int x){ del(root,x); }
    bool find(int x){ return find(root,x); }
    int rfs(int k){if (k>=1&&k<=root->c) return rfs(root,k); else return -1; }
}; 
 
treap t; 
int n,m,x; 
char s[2]; 
 
int main(){
    srand(time(0)^141592653); 
    freopen("BST.in","r",stdin); 
    freopen("BST.out","w",stdout);
    scanf("%d%d",&m,&n);
    for (int i = 0; i < n; ++i ){
        scanf("%s%d",&s,&x);
        switch (s[0]) {
            case 'I': t.ins(x); break; 
            case 'D': t.del(x); break; 
            case 'F': printf("%d\n",t.rfs(x)); break; 
            case 'B': printf("%d\n",t.find(x)); break; 
        }
    }
    return 0; 
}
