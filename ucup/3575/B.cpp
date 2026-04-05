#include<bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
const int N=2005;
int n,m;
string s[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;++i)cin>>s[i];
    const int BASE=32;
    const int NODE=64;
    const int W=(m+64)>>6;
    vector<ull> msk(n*NODE*W,0);
    auto get_ptr=[&](int i,int node)->ull* {
        return &msk[(i*NODE+node)*W];
    };
    auto get_cptr=[&](int i,int node)->const ull* {
        return &msk[(i*NODE+node)*W];
    };
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            int c=s[i][j]-'a';
            ull *lf=get_ptr(i,BASE+c);
            lf[j>>6]|=(ull)1<<(j&63);
        }
        for(int node=BASE-1;node>=1;--node){
            ull *no=get_ptr(i,node);
            const ull *ls=get_cptr(i,node<<1),*rs=get_cptr(i,node<<1|1);
            for(int w=0;w<W;++w)no[w]=ls[w]|rs[w];
        }
    }
    auto get_j=[&](const ull* a,const ull* b)->bool {
        for(int w=0;w<W;++w){
            if(a[w]&b[w])return 1;
        }
        return 0;
    };
    auto get_minc=[&](int i,const ull* a)->int {
        if(!get_j(get_cptr(i,1),a))return 26;
        int node=1;
        while(node<BASE){
            if(get_j(get_cptr(i,node<<1),a))node<<=1;
            else node=node<<1|1;
        }
        return node-BASE;
    };
    vector<ull> A(n*W),B(n*W);
    auto ptr_A=[&](int i)->ull* {
        return &A[i*W];
    };
    auto cptr_A=[&](int i)->const ull* {
        return &A[i*W];
    };
    auto ptr_B=[&](int i)->ull* {
        return &B[i*W];
    };
    int las_w=m>>6;
    int las_b=m&63;
    ull las=(las_b==63?~0ull:((1ull<<(las_b+1))-1));
    for(int i=0;i<n-1;++i){
        ull *a=ptr_A(i);
        for(int w=0;w<las_w;++w)a[w]=~0ull;
        a[las_w]=las;
    }
    ptr_A(n-1)[0]|=1;
    string ans;
    ans.reserve(m);
    for(int no=m;no;--no){
        int bst=26;
        for(int i=0;i<n;++i){
            int cur=get_minc(i,cptr_A(i));
            if(cur<bst)bst=cur;
            if(!bst)break;
        }
        ans.push_back('a'+bst);
        fill(B.begin(),B.end(),0);
        int lf=BASE+bst;
        int st=n;
        for(int i=0;i<n;++i){
            const ull *a=cptr_A(i);
            const ull *mk=get_cptr(i,lf);
            ull *b=ptr_B(i);
            ull ca=0;
            bool fl=0;
            for(int w=0;w<W;++w){
                ull x=a[w]&mk[w];
                ull y=(x<<1)|ca;
                ca=x>>63;
                b[w]=y;
                fl|=(y!=0);
            }
            if(i==0){
                if((b[las_w]>>las_b)&1)st=min(st,1);
            }
            else{
                if(fl&&i+1<n){
                    st=min(st,i+1);
                }
            }
        }
        for(int i=st;i<n;++i)ptr_B(i)[0]|=1;
        A.swap(B);
    }
    cout<<ans;
    return 0;
}