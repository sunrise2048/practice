#include<bits/stdc++.h>
using namespace std;
namespace fastio
{
    const int bufl=1<<16;
    const double base1[16]={1,1e-1,1e-2,1e-3,1e-4,1e-5,1e-6,1e-7,1e-8,1e-9,1e-10,1e-11,1e-12,1e-13,1e-14,1e-15};
    const double base2[16]={1,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11,1e12,1e13,1e14,1e15};
    struct IN{
        FILE *IT;char ibuf[bufl],*is=ibuf,*it=ibuf;
        IN(){IT=stdin;}IN(char *a){IT=fopen(a,"r");}
        inline char getChar(){if(is==it){it=(is=ibuf)+fread(ibuf,1,bufl,IT);if(is==it)return EOF;}return *is++;}
        template<typename Temp>inline void getInt(Temp &a){a=0;int b=0,c=getChar();while(c<48||c>57)b^=(c==45),c=getChar();while(c>=48&&c<=57)a=(a<<1)+(a<<3)+c-48,c=getChar();if(b)a=-a;}
        template<typename Temp>inline void getDouble(Temp &a){a=0;int b=0,c=getChar(),d=0;__int128 e=0,f=0;while(c<48||c>57)b^=(c==45),c=getChar();while(c>=48&&c<=57)e=(e<<1)+(e<<3)+c-48,c=getChar();if(c==46){c=getChar();while(c>=48&&c<=57)d++,f=(f<<1)+(f<<3)+c-48,c=getChar();}a=e+base1[d]*f;if(b)a=-a;}
        IN& operator>>(char &a){a=getChar();return *this;}
        IN& operator>>(char *a){do{*a=getChar();}while(*a<=32);while(*a>32)*++a=getChar();*a=0;return *this;}
        IN& operator>>(string &a){char b=getChar();while(b<=32)b=getChar();while(b>32)a+=b,b=getChar();return *this;}
        IN& operator>>(int &a){getInt(a);return *this;}
        IN& operator>>(long long &a){getInt(a);return *this;}
        IN& operator>>(__int128 &a){getInt(a);return *this;}
        IN& operator>>(float &a){getDouble(a);return *this;}
        IN& operator>>(double &a){getDouble(a);return *this;}
        IN& operator>>(long double &a){getDouble(a);return *this;}
    };
    struct OUT{
        FILE *IT;char obuf[bufl],*os=obuf,*ot=obuf+bufl;int Eps;long double Acc;
        OUT(){IT=stdout,Eps=6,Acc=1e-6;}OUT(char *a){IT=fopen(a,"w"),Eps=6,Acc=1e-6;}
        inline void ChangEps(int x=6){Eps=x;}
        inline void flush(){fwrite(obuf,1,os-obuf,IT);os=obuf;}
        inline void putChar(int a){*os++=a;if(os==ot)flush();}
        template<typename Temp>inline void putInt(Temp a){if(a<0){putChar(45);a=-a;}if(a<10){putChar(a+48);return;}putInt(a/10);putChar(a%10+48);}
        template<typename Temp>inline void putDouble(Temp a){if(a<0){putChar(45);a=-a;}__int128 b=a;putInt(b);a-=b;a*=base2[Eps];b=a+Acc;putChar(46);putInt(b);}
        OUT& operator<<(char a){putChar(a);return *this;}
        OUT& operator<<(char *a){while(*a>32)putChar(*a++);return *this;}
        OUT& operator<<(string a){for(auto c:a)putChar(c);return *this;}
        OUT& operator<<(int a){putInt(a);return *this;}
        OUT& operator<<(long long a){putInt(a);return *this;}
        OUT& operator<<(__int128 a){putInt(a);return *this;}
        OUT& operator<<(float a){putDouble(a);return *this;}
        OUT& operator<<(double a){putDouble(a);return *this;}
        OUT& operator<<(long double a){putDouble(a);return *this;}
        ~OUT(){flush();}
    };
}
using fastio::IN;
using fastio::OUT;
IN fin;
OUT fout;
using ll=long long;
const int N=1e6+5;
const int M=5e6+5;
const int mod=998244353;
int T;
int n,m;
int p[N];
pair<int,int> q[M];
vector<pair<int,int>> ve;
int ndt[M];
bool fl[M];
struct node{
    int trt;
    bool fl;
    int fail;
}nd[M];
int fa[M],d[M];
int f[M];
int g[M],fg[M];
int cnt;
queue<int> acq;
class SGT{
public:
    struct node{
        int lson,rson;
    }t[M*15];
    int cn;
    #define mid (l+r>>1)
    #define rs(k) t[k].rson
    #define ls(k) t[k].lson
    void update(int l,int r,int& k,int x,int d){
        if(l==r){
            k=d;
            return;
        }
        if(!k)k=++cn;
        if(x<=mid)update(l,mid,ls(k),x,d);
        else update(mid+1,r,rs(k),x,d);
    }
    int query(int l,int r,int k,int x){
        if(!k)return 0;
        if(l==r)return k;
        if(x<=mid)return query(l,mid,ls(k),x);
        return query(mid+1,r,rs(k),x);
    }
    void query0(int l,int r,int k){
        if(!k)return;
        if(l==r){
            nd[k].fail=0;
            acq.push(k);
            return;
        }
        query0(l,mid,ls(k));query0(mid+1,r,rs(k));
    }
    void merge(int l,int r,int& k0,int k1){
        if(!k0){
            k0=k1;
            return;
        }
        if(l==r){
            nd[k0].fail=k1;
            acq.push(k0);
            return;
        }
        merge(l,mid,ls(k0),ls(k1));
        merge(mid+1,r,rs(k0),rs(k1));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
vector<int> c;
vector<int> td[N];
int vis[N];
void clear(){
    for(int i=1;i<=n;++i)td[i].clear();
    for(int i=0;i<=cnt;++i){
        nd[i].trt=nd[i].fail=0;
        nd[i].fl=0;
        f[i]=g[i]=fg[i]=0;
        vis[i]=0;
    }
    cnt=0;
    for(int i=1;i<=sgt.cn;++i){
        sgt.t[i].lson=sgt.t[i].rson=0;
    }
    sgt.cn=0;
    ve.clear();
}
int ins(){
    int no=0;
    for(int i=0;i<c.size();++i){
        int to=sgt.query(1,n,nd[no].trt,c[i]);
        if(!to){
            to=++cnt;
            td[c[i]].push_back(to);
            fa[to]=no;
            sgt.update(1,n,nd[no].trt,c[i],to);
        }
        no=to;
    }
    if(nd[no].fl)return -1;
    nd[no].fl=1;
    return no;
}
vector<int> qe[N],qq[N];
int main(){
    fin>>T;
    while(T--){
        fin>>n;
        for(int i=1;i<=n;++i){
            int a;
            fin>>a;
            p[a]=i;
        }
        clear();
        fin>>m;
        for(int i=1;i<=m;++i){
            fl[i]=1;
            int si;
            fin>>si;
            c.resize(si);
            int la=0;
            bool fl=1;
            for(int j=0;j<si;++j){
                int a;
                fin>>a;
                c[j]=p[a];
                if(c[j]<=la){
                    fl=0;
                }
                la=c[j];
            }
            if(!fl){
                --m;--i;
                continue;
            }
            q[i]={c[0],c.back()};
            ndt[i]=ins();
            if(ndt[i]==-1){
                --i;--m;
            }
        }
        ve.reserve(m);
        sgt.query0(1,n,nd[0].trt);
        while(!acq.empty()){
            int no=acq.front();
            acq.pop();
            d[no]=d[nd[no].fail]+1;
            nd[no].fl|=nd[nd[no].fail].fl;
            sgt.merge(1,n,nd[no].trt,nd[nd[no].fail].trt);
        }
        for(int i=1;i<=m;++i){
            bool fl=!nd[nd[ndt[i]].fail].fl;
            int no=fa[ndt[i]];
            while(fl&&no){
                fl&=(!nd[no].fl);
                no=fa[no];
            }
            if(fl){
                ve.push_back(q[i]);
            }
        }
        sort(ve.begin(),ve.end(),[](const pair<int,int>& x,const pair<int,int>& y){
            return x.second<y.second;
        });
        f[0]=g[0]=1;
        for(int i=1;i<=n;++i){
            if(td[i].empty()){
                int d=g[0];
                f[0]=(f[0]+d)%mod;
                g[0]=(g[0]+d)%mod;
                continue;
            }
            int mxd=0;
            for(int no:td[i]){
                fg[no]=0;
                qe[d[fa[no]]].push_back(no);
                mxd=max(mxd,d[fa[no]]);
            }
            for(int dd=mxd;dd>=0;--dd){
                for(int no:qe[dd]){
                    int fa=::fa[no];
                    if(vis[fa]!=i){
                        vis[fa]=i;
                        fg[fa]=0;
                        qq[d[fa]].push_back(fa);
                    }
                    if(!nd[no].fl)f[no]=(g[fa]-fg[fa]+mod)%mod;
                    fg[fa]=g[fa];
                }
                for(int no:qq[dd]){
                    if(!no)continue;
                    int fa=nd[no].fail;
                    if(vis[fa]!=i){
                        vis[fa]=i;
                        fg[fa]=0;
                        qq[d[fa]].push_back(fa);
                    }
                    fg[fa]=(fg[fa]+fg[no])%mod;
                }
                qe[dd].clear();qq[dd].clear();
            }
            int fd=(g[0]-fg[0]+mod)%mod;
            f[0]=(f[0]+fd)%mod;g[0]=(g[0]+fd)%mod;
            mxd=0;
            for(int no:td[i]){
                fg[no]=f[no];
                vis[no]=-i;
                mxd=max(mxd,d[no]);
                qq[d[no]].push_back(no);
            }
            for(int dd=mxd;dd>=0;--dd){
                for(int no:qq[dd]){
                    g[no]=(g[no]+fg[no])%mod;
                    int fa=nd[no].fail;
                    if(no&&vis[fa]!=-i){
                        vis[fa]=-i;
                        fg[fa]=0;
                        qq[d[fa]].push_back(fa);
                    }
                    fg[fa]=(fg[fa]+fg[no])%mod;
                }
                qq[dd].clear();
            }
        }
        fout<<g[0]-1<<'\n';
    }
    return 0;
}