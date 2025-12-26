#include<bits/stdc++.h>
using namespace std;
using ll=long long;
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
const int N=3e5+5;
const int B=490;
const int K=1005;
int n,m;
ll ans[N];
int a[N];
struct lb{
    int pr,ne;
}bl[N];
int head[N];
vector<int> tid;
bool flt[N];
int ta[N];
ll al[N];
class CALC{
public:
    int ks;
    int fl[N],fr[N];
    int kid[N];
    int L[K],R[K];
    ll kans[K];
    int kl[K],kr[K];
    bool vis[N];
    void Init(){
        ks=(n+B-1)/B;
        for(int i=1;i<=ks;++i){
            L[i]=R[i-1]+1;
            R[i]=i*B;
        }
        R[ks]=n;
        for(int i=1;i<=ks;++i){
            for(int j=L[i];j<=R[i];++j){
                kid[j]=i;
            }
        }
    }
    void init(){
        for(int i=1;i<=n;++i){
            fl[i]=fr[i]=i;
            vis[i]=0;
        }
        for(int i=1;i<=ks;++i){
            kl[i]=kr[i]=0;
            kans[i]=0;
        }
    }
    vector<int> ve;
    void ins(int x,bool tf=0){
        const int nok=kid[x];
        const int kL=L[nok],kR=R[nok];
        vis[x]=1;
        kans[nok]++;
        int nl=x,nr=x;
        if(x!=kL&&vis[x-1]){
            if(tf)ve.push_back(x);
            const int tl=fl[x-1],tr=x-1;
            int len=tr-tl+1;
            kans[nok]-=al[len];
            kans[nok]--;
            fl[x]=tl;fr[tl]=x;
            nl=tl;
            len=nr-nl+1;
            kans[nok]+=al[len];
        }
        if(x!=kR&&vis[x+1]){
            if(tf)ve.push_back(x+1);
            const int tl=x+1,tr=fr[x+1];
            int len=tr-tl+1;
            kans[nok]-=al[len];
            len=nr-nl+1;
            kans[nok]-=al[len];
            fr[nl]=tr;fl[tr]=nl;
            nr=tr;
            len=nr-nl+1;
            kans[nok]+=al[len];
        }
        if(nl==kL)kl[nok]=nr-nl+1;
        if(nr==kR)kr[nok]=nr-nl+1;
    }
    void cl(int x){
        const int nok=kid[x];
        kans[nok]--;
        vis[x]=0;
        if(x==L[nok])kl[nok]=0;
        if(x==R[nok])kr[nok]=0;
    }
    void era(int x){
        const int nok=kid[x];
        const int lL=fl[x-1],rR=fr[x];
        kans[nok]-=al[rR-lL+1];
        fr[lL]=x-1;fl[rR]=x;
        kans[nok]+=al[x-lL]+al[rR-x+1];
        if(lL==L[nok])kl[nok]=x-lL;
        if(rR==R[nok])kr[nok]=rR-x+1;
    }
    void cx(){
        while(ve.size()){
            era(ve.back());
            ve.pop_back();
        }
    }
    ll query(int x,int y){
        if(kid[x]==kid[y]){
            int len=0;
            ll ans=0;
            for(int i=x;i<=y;++i){
                if(vis[i]){
                    ++len;
                }
                else{
                    ans+=al[len];
                    len=0;
                }
            }
            return ans+al[len];
        }
        int nlen=0;
        ll ans=0;
        for(int i=x;i<=R[kid[x]];++i){
            if(vis[i]){
                ++nlen;
            }
            else{
                ans+=al[nlen];
                nlen=0;
            }
        }
        for(int kd=kid[x]+1;kd<kid[y];++kd){
            if(kl[kd]==R[kd]-L[kd]+1){
                nlen+=kl[kd];
                continue;
            }
            ans+=kans[kd]-al[kl[kd]]-al[kr[kd]];
            nlen+=kl[kd];
            ans+=al[nlen];
            nlen=kr[kd];
        }
        for(int i=L[kid[y]];i<=y;++i){
            if(vis[i])++nlen;
            else{
                ans+=al[nlen];
                nlen=0;
            }
        }
        return ans+al[nlen];
    }
}calc;
struct ques{
    int l,r,x;
    int id;
    ques(int l,int r,int x,int id):l(l),r(r),x(x),id(id){}
};
vector<ques> qs;
struct upq{
    int x,y,id;
    upq(int x,int y,int id):x(x),y(y),id(id){}
};
vector<upq> pq;
void solve(){
    calc.init();
    tid.clear();
    for(auto [x,y,id]:pq){
        if(flt[x])continue;
        flt[x]=1;
        if(head[a[x]]==x)head[a[x]]=bl[x].ne;
        bl[bl[x].ne].pr=bl[x].pr;
        bl[bl[x].pr].ne=bl[x].ne;
        tid.push_back(x);
    }
    sort(qs.begin(),qs.end(),[](const ques& x,const ques& y){
        return x.x<y.x;
    });
    int nv=0;
    for(auto [l,r,x,id]:qs){
        while(nv<x){
            ++nv;
            int no=head[nv];
            while(no){
                calc.ins(no);
                no=bl[no].ne;
            }
        }
        for(int no:tid)ta[no]=a[no];
        for(auto [x,y,pid]:pq){
            if(pid>id)break;
            ta[x]=y;
        }
        for(int no:tid){
            if(ta[no]<=x)calc.ins(no,1);
        }
        ans[id]=calc.query(l,r);
        calc.cx();
        for(int no:tid){
            if(ta[no]<=x)calc.cl(no);
        }
    }
    for(auto [x,y,pid]:pq){
        a[x]=y;
    }
    for(auto [x,y,id]:pq){
        if(flt[x]){
            bl[x].ne=head[a[x]];
            bl[bl[x].ne].pr=x;
            bl[x].pr=0;
            head[a[x]]=x;
            flt[x]=0;
        }
    }
    pq.clear();qs.clear();
}
int main(){
    fin>>n>>m;
    for(int i=1;i<=n;++i){
        fin>>a[i];
        bl[i].ne=head[a[i]];
        bl[bl[i].ne].pr=i;
        head[a[i]]=i;
        al[i]=1ll*i*(i+1)/2;
    }
    calc.Init();
    const int BB=1800;
    for(int t=1;t<=m;++t){
        int op;
        fin>>op;
        if(op==1){
            int x,y;
            fin>>x>>y;
            pq.emplace_back(x,y,t);
            ans[t]=-1;
        }
        else{
            int l,r,x;
            fin>>l>>r>>x;
            qs.emplace_back(l,r,x,t);
        }
        if(t%BB==0){
            solve();
        }
    }
    if(qs.size())solve();
    for(int i=1;i<=m;++i){
        if(ans[i]!=-1)fout<<ans[i]<<'\n';
    }
    return 0;
}