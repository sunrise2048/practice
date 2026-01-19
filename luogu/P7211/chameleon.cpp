#include"chameleon.h"
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
vector<int> e[N];
int s[N];
bool fl[N];
void finde(int no,vector<int> id){
    if(id.empty())return;
    id.push_back(no);
    if(Query(id)==id.size())return;
    id.pop_back();
    int l=-1,r=id.size()-1;
    while(l<r-1){
        int mid=(l+r>>1);
        vector<int> qu;
        for(int i=0;i<=mid;++i)qu.push_back(id[i]);
        qu.push_back(no);
        if(Query(qu)==qu.size())l=mid;
        else r=mid;
    }
    e[no].push_back(id[r]);
    e[id[r]].push_back(no);
    vector<int> tq;
    for(int i=r+1;i<id.size();++i)tq.push_back(id[i]);
    finde(no,tq);
}
void solve(vector<int> id){
    vector<int> dl;
    vector<int> fd;
    for(int no:id){
        dl.push_back(no);
        if(dl.size()!=1&&Query(dl)!=dl.size()){
            dl.pop_back();
            fd.push_back(no);
        }
    }
    if(!fd.size())return;
    for(int no:fd){
        finde(no,dl);
    }
    solve(fd);
}
mt19937 mt(time(0));
void Solve(int n){
    n*=2;
    vector<int> id(n);
    iota(id.begin(),id.end(),1);
    shuffle(id.begin(),id.end(),mt);
    solve(id);
    for(int no:id){
        if(e[no].size()==1)continue;
        int a=e[no][0],b=e[no][1],c=e[no][2];
        if(Query(vector<int>{no,a,b})==1){
            s[c]+=no;
            s[no]+=c;
            continue;
        }
        if(Query(vector<int>{no,a,c})==1){
            s[b]+=no;
            s[no]+=b;
            continue;
        }
        s[a]+=no;
        s[no]+=a;
    }
    for(int no:id){
        if(fl[no])continue;
        int to=-s[no];
        for(int x:e[no])to+=x;
        Answer(no,to);
        fl[to]=1;
    }
}
