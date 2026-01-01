#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e3+5;
int n;
int a[N],b[N];
int cn;
struct ope{
    int i,j,k,l;
    ope(int i,int j,int k,int l):i(i),j(j),k(k),l(l){}
};
vector<ope> op;
int p[N];
int ch(){
    for(int i=1;i<=n;++i){
        if(a[i]!=i)return i;
    }
    return 0;
}
void upd(int i,int j,int k,int l){
    cn=0;
    op.emplace_back(i,j,k,l);
    for(int x=1;x<i;++x)b[++cn]=a[x];
    for(int x=k;x<=l;++x)b[++cn]=a[x];
    for(int x=j+1;x<k;++x)b[++cn]=a[x];
    for(int x=i;x<=j;++x)b[++cn]=a[x];
    for(int x=l+1;x<=n;++x)b[++cn]=a[x];
    memcpy(a,b,sizeof(int)*(n+1));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    int no;
    while((no=ch())!=0){
        int ne=0;
        for(int i=1;i<=n;++i){
            p[a[i]]=i;
        }
        for(int i=no+1;i<=n;++i){
            if(p[i]<p[no]){
                if(p[i]==no){
                    upd(no,p[no]-1,p[no],p[i-1]);
                }
                else upd(no,p[i]-1,p[no],p[i-1]);
                break;
            }
        }
    }
    cout<<op.size()<<'\n';
    for(auto [i,j,k,l]:op){
        cout<<i<<' '<<j<<' '<<k<<' '<<l<<'\n';
    }
    return 0;
}