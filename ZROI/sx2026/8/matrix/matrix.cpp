#include<bits/stdc++.h>
#include"matrix.h"
using namespace std;
using ll=long long;
const int N=2005;
int a[N][N];
int n;
vector<pair<int,int>> nd;
bool ch(int x,int y){
    return (0<x&&x<=n)&&(0<y&&y<=n);
}
vector<pair<int,int>> solve(int n,int cid){
    ::n=n;
    nd.clear();
    priority_queue<pair<int,int>> px[2],py[2];
    vector<int> pa[2];
    for(int i=0;i<=n+1;++i){
        pa[0].push_back(ask(i,i)*2);
    }
    int cn=pa[0][0]-pa[0][1];cn/=2;
    for(int i=1;i<=n+1;++i){
        pa[1].push_back(ask(i,i-1)*2);
    }
    for(int i=2;i<=2*n;++i){
        int qu=pa[(i+1)&1][(i-1)/2]-pa[(i+1)&1][(i-1)/2+1];
        int ncn=cn-qu/2;
        for(int j=i;j<=2*n+2;++j){
            pa[j&1][j/2]-=ncn*abs(j-i);
        }
        cn-=ncn;
        if(ncn)px[i&1].emplace(ncn,i);
    }
    pa[0].clear();pa[1].clear();
    for(int i=0;i<=n+1;++i){
        pa[0].push_back(ask(i,n+1-i)*2);
    }
    cn=pa[0][0]-pa[0][1];cn/=2;
    for(int i=0;i<=n;++i){
        pa[1].push_back(ask(i,n-i)*2);
    }
    for(int i=-n+1;i<n;++i){
        const int op=((abs(i+1)&1)==(n&1));
        int qu=pa[op][(i+n)/2]-pa[op][(i+n)/2+1];
        int ncn=cn-qu/2;
        for(int j=i;j<=n+1;++j){
            const int pj=((abs(j)&1)==(n&1));
            pa[pj][(j+n+1)/2]-=ncn*abs(j-i);
        }
        cn-=ncn;
        if(ncn)py[abs(i)&1].emplace(ncn,i);
    }
    vector<pair<int,int>> ans;
    return ans;
}