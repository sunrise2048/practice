#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,m;
ll a[N],b[N];
int sta[N],stb[N];
int ra,rb;
ll ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=m;++i){
        cin>>b[i];
    }
    for(int i=1;i<=n;++i){
        while(ra>1&&(a[sta[ra]]-a[sta[ra-1]])*(i-sta[ra])>=(a[i]-a[sta[ra]])*(sta[ra]-sta[ra-1]))--ra;
        sta[++ra]=i;
    }
    for(int i=1;i<=m;++i){
        while(rb>1&&(b[stb[rb]]-b[stb[rb-1]])*(i-stb[rb])>=(b[i]-b[stb[rb]])*(stb[rb]-stb[rb-1]))--rb;
        stb[++rb]=i;
    }
    int x=1,y=1;
    while(x!=ra||y!=rb){
        if(x==ra){
            ans+=a[sta[x]]*(stb[y+1]-stb[y]);
            ++y;
            continue;
        }
        if(y==rb){
            ans+=b[stb[y]]*(sta[x+1]-sta[x]);
            ++x;
            continue;
        }
        if((a[sta[x+1]]-a[sta[x]])*(stb[y+1]-stb[y])>(b[stb[y+1]]-b[stb[y]])*(sta[x+1]-sta[x])){
            ans+=a[sta[x]]*(stb[y+1]-stb[y]);
            ++y;
        }
        else{
            ans+=b[stb[y]]*(sta[x+1]-sta[x]);
            ++x;
        }
    }
    cout<<ans<<'\n';
    return 0;
}