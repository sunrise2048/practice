#include<bits/stdc++.h>
using namespace std;
using ll=long long;
struct node{
    string s;
    int cn;
    node()=default;
    node(string s,int cn):s(s),cn(cn){}
    bool operator<(const node& ls)const{
        return cn<ls.cn;
    }
}nd[27]={node("UW",11),node("UJ",9),node("UWR",8),node("MAP",7),node("PW",6),node("AGH",5),node("PG",4),node("NLU",3),node("PUT",3),node("PO",2),node("PWR",2),node("SGGW",2),node("UMCS",2),node("UR",2),node("ZUT",2),node("DTP",1),node("GOO",1),node("HUA",1),node("KUL",1),node("PL",1),node("PM",1),node("PS",1),node("UAM",1),node("UG",1),node("UMK",1),node("UO",1),node("WAT",1)};
const int n=8,m=10;
string s[n][m];
priority_queue<int> pq;
const int f[8][2]={{-1,0},{-1,1},{-1,-1},{0,-1},{0,1},{1,0},{1,-1},{1,1}};
bool ch(int x,int y,int id){
    for(auto [dx,dy]:f){
        int tx=x+dx,ty=y+dy;
        if(tx<0||tx>=n||ty<0||ty>=m)continue;
        if(s[tx][ty]==nd[id].s)return 0;
    }
    return 1;
}
void dfs(int x,int y){
    if(y==m){
        y=0;++x;
    }
    if(x==n)return;
    int z=-1;
    for(int i=0;i<27;++i){
        if(!ch(x,y,i))continue;
        if(z==-1||nd[z]<nd[i])z=i;
    }
    s[x][y]=nd[z].s;
    nd[z].cn--;
    dfs(x,y+1);
}
int main(){
    string ns;
    cin>>ns;
    s[0][0]=ns;
    for(int i=0;i<27;++i){
        if(ns==nd[i].s)nd[i].cn--;
    }
    dfs(0,1);
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            cout<<s[i][j]<<' ';
        }cout<<'\n';
    }
    return 0;
}