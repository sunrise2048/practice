#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
int T;
int n;
int d[N],s[N];
int ask(int no){
    cout<<"throw "<<no<<endl;
    int cn;
    cin>>cn;
    return cn;
}
stack<int> swp_id;
void cg(int l,int r){
    for (int i=r;i>=l;--i) {
        s[i]=s[i+d[i]]+1;
    }
}
void swp(int no){
    cout<<"swap "<<no<<endl;
    swap(d[no],d[no+1]);
    swp_id.push(no);
}
int main(){
    cin>>T;
    while (T--) {
        cin>>n;
        memset(d,0,sizeof(int)*(n+4));
        memset(s,0,sizeof(int)*(n+4));
        int ds=ask(n-1);
        if (ds==1) d[n-1]=2;
        else d[n-1]=1;
        swp(n-1);
        ds=ask(n-1);
        if (ds==1) d[n-1]=2;
        else d[n-1]=1;
        cg(n-1,n);
        for (int i=n-2;i;--i) {
            if (s[i+1]!=s[i+2]) {
                int cn=ask(i);
                s[i]=cn;
                if (cn==s[i+1]+1) d[i]=1;
                else d[i]=2;
                continue;
            }
            if (i!=1) {
                int cn=ask(i-1);
                s[i-1]=cn;
                if (cn==s[i+1]+1) d[i-1]=2;
                else d[i-1]=1;
                swp(i-1);
                cn=ask(i-1);
                if (cn==s[i+1]+1) d[i-1]=2;
                else d[i-1]=1;
                cg(i-1,i);
                --i;
                continue;
            }
            swp(i);
            int cn=ask(i+1);
            if (cn==s[i+3]+1) d[i+1]=2;
            else d[i+1]=1;
        }
        while (!swp_id.empty()) {
            swap(d[swp_id.top()],d[swp_id.top()+1]);
            swp_id.pop();
        }
        cout<<"! ";
        for (int i=1;i<=n;++i) cout<<d[i]<<' ';
        cout<<endl;
    }
    return 0;
}