class Flow{
public:
    int s,t;
    struct edge{
        int v;
        int w;
        int ne;
    }e[M];
    int head[N];
    int cn;
    Flow(int s,int t):s(s),t(t),cn(1){}
    void add(int u,int v,int w){
        e[++cn].v=v;
        e[cn].w=w;
        e[cn].ne=head[u];
        head[u]=cn;
    }
    void adde(int u,int v,int w){
        add(u,v,w);add(v,u,0);
    }
    int cur[N];
    int d[N];
    bool bfs(){
        memset(d,0x3f,sizeof(d));
        memcpy(cur,head,sizeof(cur));
        queue<int> q;
        d[s]=0;
        q.push(s);
        while(!q.empty()){
            int no=q.front();
            q.pop();
            if(no==t)return 1;
            for(int i=head[no];i;i=e[i].ne){
                if(!e[i].w)continue;
                int to=e[i].v;
                if(d[to]!=0x3f3f3f3f)continue;
                d[to]=d[no]+1;
                q.push(to);
            }
        }
        return 0;
    }
    int dfs(int no,int mif){
        if(no==t)return mif;
        int s=0;
        for(int& i=cur[no];i;i=e[i].ne){
            if(!e[i].w)continue;
            int to=e[i].v;
            if(d[to]!=d[no]+1)continue;
            int nf=dfs(to,min(e[i].w,mif));
            if(nf){
                s+=nf;
                mif-=nf;
                e[i].w-=nf;
                e[i^1].w+=nf;
            }
            if(!mif)break;
        }
        if(s==0)d[no]=-1;
        return s;
    }
    int dinic(){
        int cn=0;
        while(bfs()){
            cn+=dfs(s,1e9);
        }
        return cn;
    }
}flow(1,2);