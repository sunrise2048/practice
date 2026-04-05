#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int q;
int n;
int a[N];
int s[N],fi[N];
struct ope{
    int op,x;
    int lfn,lfx;
    int ls;
};
vector<ope> st;
int main(){
    cin>>q;
    while(q--){
        char op;
        int x;
        cin>>op;
        if(op!='?'&&op!='!')cin>>x;
        if(op=='+'){
            ++n;
            st.push_back({0,a[n],fi[a[n]],fi[x],s[n]});
            if(fi[a[n]]==n){
                fi[a[n]]=0;
            }
            a[n]=x;
            s[n]=s[n-1];
            if(!fi[x]||fi[x]>n){
                fi[x]=n;
                s[n]++;
            }
        }
        else if(op=='-'){
            st.push_back({1,x,0,0,0});
            n-=x;
        }
        else if(op=='!'){
            auto [lp,x,lfn,lfx,ls]=st.back();
            st.pop_back();
            if(lp)n+=x;
            else{
                fi[a[n]]=lfx;
                a[n]=x;
                s[n]=ls;
                fi[a[n]]=lfn;
                --n;
            }
        }
        else{
            cout<<s[n]<<endl;
        }
    }
    return 0;
}