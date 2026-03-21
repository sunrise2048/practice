#include"subway.h"
#include<bits/stdc++.h>
using namespace std;
int m;
void init(int n,int m,int lm){
    ::m=m;
}
stack<pair<int,int>> st;
int r;
int cna;
void pop(){
    if(!cna){
        queue<int> nst;
        while(!st.empty()){
            int no=st.top().second;
            st.pop();
            undo();
            nst.push(no);
        }
        cna=nst.size();
        while(!nst.empty()){
            int no=nst.front();
            nst.pop();
            st.emplace(1,no);
            merge(no);
        }
    }
    if(st.top().first){
        undo();
        --cna;
        st.pop();
        return;
    }
    int lb=(cna&-cna);
    stack<int> nst[2];
    while(lb){
        auto [op,no]=st.top();
        st.pop();
        undo();
        lb-=op;
        nst[op].push(no);
    }
    for(int op:{0,1}){
        while(!nst[op].empty()){
            int no=nst[op].top();
            nst[op].pop();
            merge(no);
            st.emplace(op,no);
        }
    }
    undo();
    --cna;
    st.pop();
}
int solve(int l){
    while(r!=m&&check(r+1)){
        ++r;
        merge(r);
        st.emplace(0,r);
    }
    pop();
    return r;
}