#include<bits/stdc++.h>
using namespace std;
using ll=long long;
void Solve(int,int);
int Query(const vector<int> &x);
void Answer(const vector<int> &a);
vector<int> id;
mt19937 mt(time(0));
vector<bool> fl;
int n,m;
int qu(vector<int>& ve){
    vector<bool> nf(n*m);
    for(int id:ve)nf[id-1]=1;
    vector<int> tq;
    for(int i=0;i<n*m;++i){
        if(!nf[i])tq.push_back(i+1);
    }
    return Query(tq);
}
void Solve(int n,int m){
    ::n=n;::m=m;
    id.resize(n*m);
    fl.resize(n*m+1);
    iota(id.begin(),id.end(),1);
    shuffle(id.begin(),id.end(),mt);
    int k=m;
    while(k--){
        vector<int> nd;
        for(int i=0;i<id.size();++i){
            nd.push_back(id[i]);
            if(qu(nd)<m-1)nd.pop_back();
            else fl[id[i]]=1;
            if(nd.size()==n)break;
        }
        Answer(nd);
        vector<int> nid;
        for(int no:id){
            if(!fl[no])nid.push_back(no);
        }
        shuffle(nid.begin(),nid.end(),mt);
        swap(nid,id);
    }
}