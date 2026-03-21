#include"starmap.h"
#include<bits/stdc++.h>
using namespace std;
const int N=505;
void init(int c, int t){}
bitset<N> e[N];
int op[N][N];
int d[N];
int k;
void flip(int x,int y){
    if(e[x][y]){
        --d[x];--d[y];
    }
    else{
        ++d[x];++d[y];
    }
    e[x][y]=e[y][x]=!e[x][y];
}
void inv(vector<int> id){
    invert(id);
    for(int i=0;i<k;++i){
        for(int j=0;j<i;++j){
            flip(id[i],id[j]);
        }
    }
}
void ope(int x,int y){op[max(x,y)][min(x,y)]^=1;}
void syh(int a,int b,int c,int d){
    ope(c,d);ope(a,d);ope(a,b);ope(b,c);
    flip(a,b);flip(b,c);flip(c,d);flip(d,a);
}
vector<pair<int,int>> hl,st;
vector<int> ed[N];
void dfs(int no){
    while(!ed[no].empty()){
        int to=ed[no].back();
        ed[no].pop_back();
        if(!e[no][to])continue;
        e[no][to]=e[to][no]=0;
        dfs(to);
        st.emplace_back(no,to);
    }
}
void starmap(int n,int m,int k,int p,vector<int> u,vector<int> v){
    ::k=k;
    for(int i=1;i<=n;++i){
        memset(op[i],0,sizeof(op[i]));
        e[i].set();
        e[i][i]=0;
        d[i]=n-1;
    }
    int cnt=n*(n-1)/2;
    for(int i=0;i<m;++i){
        int x=u[i],y=v[i];
        e[x][y]=e[y][x]=0;
        d[x]--;d[y]--;
    }
    if(k==2){
        report(n*(n-1)/2);
        for(int i=1;i<=n;++i){
            for(int j=1;j<i;++j){
                if(e[i][j]){
                    invert({i,j});
                }
            }
        }
        return;
    }
    if(k%4==0){
        if((n*(n-1)/2-m)&1){
            --cnt;
            flip(1,2);
        }
    }
    else if(k%4==1){
        vector<int> id;
        for(int i=1;i<=n;++i){
            if(d[i]&1)id.push_back(i);
        }
        cnt-=id.size()/2;
        if((n*(n-1)/2-m-id.size()/2)&1){
            if(id.empty()){
                flip(1,2);flip(1,3);flip(2,3);
                cnt-=3;
            }
            else{
                int x=id[0],y=id[1];
                int z=1;
                if(x==z)++z;
                if(y==z)++z;
                flip(x,y);flip(y,z);flip(x,z);
                cnt--;
            }
        }
        for(int i=0;i<id.size();i+=2){
            int x=id[i],y=id[i+1];
            flip(x,y);
        }
    }
    else if(k%4==3){
        vector<int> id;
        for(int i=1;i<=n;++i){
            if(d[i]&1)id.push_back(i);
        }
        cnt-=id.size()/2;
        for(int i=0;i<id.size();i+=2){
            int x=id[i],y=id[i+1];
            flip(x,y);
        }
    }
    report(cnt);
    while(n>k+2){
        if(d[n]&1){
            vector<int> ve;
            for(int i=1;i<n;++i){
                if(ve.size()==k-1)break;
                if(e[i][n])ve.push_back(i);
            }
            for(int i=1;i<n;++i){
                if(ve.size()==k-1)break;
                if(!e[i][n])ve.push_back(i);
            }
            ve.push_back(n);
            inv(ve);
        }
        vector<int> ve;
        for(int i=1;i<n;++i){
            if(e[i][n])ve.push_back(i);
        }
        while(!ve.empty()){
            int x=ve.back();ve.pop_back();
            int y=ve.back();ve.pop_back();
            vector<int> id;
            for(int i=1;i<n;++i){
                if(i==x||i==y)continue;
                if(id.size()==k-2)break;
                id.push_back(i);
            }
            id.push_back(n);id.push_back(x);
            invert(id);
            flip(x,n);
            for(int i=0;i<k-2;++i)flip(id[i],x);
            id.pop_back();id.push_back(y);
            flip(y,n);
            for(int i=0;i<k-2;++i)flip(id[i],y);
            invert(id);
        }
        --n;
    }
    {
        int cn=0;
        for(int i=1;i<=n;++i){
            for(int j=1;j<i;++j){
                cn+=e[i][j];
            }
        }
        if(cn&1){
            op[n][n-1]^=1;
            for(int i=1;i<n-1;++i){
                for(int j=1;j<i;++j){
                    flip(i,j);
                }
            }
        }
    }
    {
        vector<int> id;
        for(int i=1;i<=n;++i){
            if(d[i]&1)id.push_back(i);
        }
        for(int i=0;i<id.size();i+=2){
            int x=id[i],y=id[i+1];
            int z=1;
            if(x==z)++z;
            if(y==z)++z;
            ope(x,z);ope(y,z);
            for(int j=1;j<=n;++j){
                if(j==x||j==y||j==z)continue;
                flip(x,j);flip(y,j);
            }
        }
    }
    {
        vector<int> id;
        for(int i=2;i<=n;++i){
            if(e[1][i])id.push_back(i);
        }
        for(int i=0;i<id.size();i+=2){
            int x=id[i];
            int y=id[i+1];
            int z=2;
            if(z==x)++z;
            if(z==y)++z;
            syh(1,x,z,y);
        }
    }
    for(int i=1;i<=n;++i){
        ed[i].clear();
        for(int j=1;j<=n;++j){
            if(e[i][j])ed[i].push_back(j);
        }
    }
    hl.clear();
    for(int i=2;i<=n;++i){
        if(ed[i].empty())continue;
        pair<int,int> le={0,0};
        if(hl.size())le={hl.back().second,i};
        if(le.first)hl.push_back(le);
        st.clear();
        dfs(i);
        reverse(st.begin(),st.end());
        for(auto no:st)hl.push_back(no);
        st.clear();
        if(le.first)hl.emplace_back(le.second,le.first);
    }
    for(int i=0;i<hl.size();i+=2){
        int x=hl[i].first,y=hl[i].second,z=hl[i+1].second;
        syh(1,x,y,z);
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<i;++j){
            if(!op[i][j])continue;
            vector<int> ve;
            for(int k=1;k<=n;++k){
                if(k==i||k==j)continue;
                ve.push_back(k);
            }
            invert(ve);
        }
    }
}