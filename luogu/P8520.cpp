#include<bits/stdc++.h>
using namespace std;
using ll=long long;
void build(vector<int> u,vector<int> v,vector<int> a,vector<int> b);
const int N=2e5+5;
int n;
vector<pair<int,int>> ve;
map<pair<int,int>,int> id;
set<pair<int,int>> st;
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int construct_roads(vector<int> x,vector<int> y){
    n=x.size();
    ve.resize(n);
    for(int i=0;i<n;++i){
        ve[i]={x[i],y[i]};
        id[ve[i]]=i;
    }
    iota(fa,fa+n,0);
    sort(ve.begin(),ve.end(),[](const pair<int,int>& x,const pair<int,int>& y){
        return x.second!=y.second?x.second>y.second:x.first<y.first;
    });
    vector<int> u,v,a,b;
    for(auto [x,y]:ve){
        int no=id[{x,y}];
        if(id.count({x+2,y})){
            int to=id[{x+2,y}];
            if(find(no)!=find(to)){
                int na=x+1,nb=y-1;
                if(((na+1)/2+(nb+1)/2)%2==0){
                    nb+=2;
                }
                if(st.count({na,nb})==0){
                    st.emplace(na,nb);
                    u.push_back(no);v.push_back(to);
                    fa[find(no)]=find(to);
                    a.push_back(na);b.push_back(nb);
                }
            }
        }
        if(id.count({x,y-2})){
            int to=id[{x,y-2}];
            if(find(no)!=find(to)){
                int na=x-1,nb=y-1;
                if(((na+1)/2+(nb+1)/2)%2==1){
                    na+=2;
                }
                if(st.count({na,nb})==0){
                    st.emplace(na,nb);
                    u.push_back(no);v.push_back(to);
                    fa[find(no)]=find(to);
                    a.push_back(na);b.push_back(nb);
                }
            }
        }
    }
    for(int i=0;i<n;++i){
        if(find(i)!=find(0))return 0;
    }
    build(u,v,a,b);
    return 1;
}