#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,k;
struct node{
    int l,r;
    int id;
}nd[N];
int p[N];
int al[N];
set<int> np;
vector<int> as;
int nxt[18][N];
int smx[N];
int query(int x,int y){
    int cn=0;
    for(int i=17;i>=0;--i){
        if(nd[nxt[i][x]].r<=nd[y].l){
            cn+=(1<<i);
            x=nxt[i][x];
        }
    }
    return cn;
}
int sum;
bool ch(int x){
    auto it=np.lower_bound(x);
    if(it!=np.end()&&nd[*it].l<nd[x].r)return 0;
    if(it!=np.begin()&&nd[*prev(it)].r>nd[x].l)return 0;
    int pr,ne;
    if(it!=np.end())ne=*it;
    else ne=n+1;
    if(it!=np.begin())pr=*prev(it);
    else pr=0;
    int ts=sum-query(pr,ne)+query(pr,x)+1+query(x,ne);
    return ts>=k;
}
void ins(int x){
    auto it=np.lower_bound(x);
    int pr,ne;
    if(it!=np.end())ne=*it;
    else ne=n+1;
    if(it!=np.begin())pr=*prev(it);
    else pr=0;
    sum=sum-query(pr,ne)+query(pr,x)+1+query(x,ne);
    np.insert(x);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>nd[i].l>>nd[i].r;
        nd[i].id=i;
    }
    sort(nd+1,nd+n+1,[](const node& x,const node& y){
        return x.l<y.l;
    });
    for(int i=1;i<=n;++i){
        p[nd[i].id]=i;
    }
    for(int i=1;i<=n;++i)al[i]=nd[i].l;
    smx[n+1]=n+1;
    nxt[0][n+1]=n+1;
    nd[n+1].r=1e9+7;
    nd[n+1].l=1e9+1;
    for(int i=n;i;--i){
        smx[i]=smx[i+1];
        if(nd[i].r<nd[smx[i]].r)smx[i]=i;
    }
    nxt[0][0]=smx[1];
    for(int i=n;i;--i){
        int to=lower_bound(al+1,al+n+1,nd[i].r)-al;
        nxt[0][i]=smx[to];
    }
    for(int j=1;j<18;++j){
        for(int i=n+1;i>=0;--i){
            nxt[j][i]=nxt[j-1][nxt[j-1][i]];
        }
    }
    if((sum=query(0,n+1))<k){
        cout<<"-1\n";
        return 0;
    }
    for(int no=1;no<=n;++no){
        if(as.size()==k)break;
        if(ch(p[no])){
            ins(p[no]);
            as.push_back(no);
        }
    }
    for(int no:as)cout<<no<<'\n';
    return 0;
}