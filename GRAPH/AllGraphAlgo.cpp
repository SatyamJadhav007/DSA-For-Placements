#include<bits/stdc++.h>
using namespace std;
//ALL THE ALGORITHMS ARE REFERRED FROM STRIVER'S DSA SHEET
//KRUSKAL'S ALGO
/*
step 1:Write the disjoint set code{union by rank}
How to write the disjoint set code? 
*->Find the Ultimate parents of the components 
How to find the Ultimate parents?  
*-> Use Path compression:{every vertex only points to its ultimate parent}
*-> Base case: Ultimate parent of one node is the node itself!!!!! 
*-> use recursive backtraking for finding Ultimate parent of every vertex of a components
*->Do union of 2 components if they don't belong to the same component 
How to do that? 
*-> Find the Ultimate parents of both the components 
*-> Compare than, if equal no need to update any component 
*-> if not equal,compare the ranks 
*-> update the smaller ones rank if different 
*-> if ranks of the both the components are equal 
*-> then update any one of the component and increment the rank 

step 2:Sort the edgeList by weight 
step 3:for every edge compare the ultimate parents if not equal 
Do the Union of both the component and count the weight of them 
THIS IS YOUR MST! 
*/
class DisjointSet{
    vector<int> rank,parent,size;
    public:
    // parent===higher && rank===lower
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1,0);
        size.resize(n+1,1);
        for(int i=0;i<=n;i++){
            parent[i]=i;
        }
    }
    //this function updates the lower node's ultimate value and changes them(if any)!!! 
    int findUpar(int node){
        // if the parent of one node is the node it self then return that node 
        // as it is the ultimate parent 
        if(parent[node]==node){
            return node;
        }
        // path compresssion:: where the ultimate parent's are only stored for every node 
        //O(4 alpha)
        // backtrack and update the parent values of all the remaining nodes as the ultimate parent is 
        // changed 
        return parent[node]=findUpar(parent[node]);
    }
    // this function updates the components by adding edges in the components 
    void UnionByRank(int u,int v){
        //O(4 alpha)
        int UP_u=findUpar(u);
        int UP_v=findUpar(v);
        // same parent so no need of updating the parents
        if(UP_u==UP_v) return;
        // different parents so check the rank of the parents and update the components 
        // here U's rank is greater so update the parent value of V 
        if(rank[UP_u]>rank[UP_v]){
            parent[UP_v]=UP_u;
        }
        // here it's the vice-versa{V's  rank is greater so update the U's parent value}
        else if(rank[UP_v]>rank[UP_u]){
            parent[UP_u]=UP_v;
        }
        // here both rank's are same so update any node's value and update the NOT attached ones rank 
        // by one 
        else{
            // update the parent 
            parent[UP_u]=UP_v;
            // upadate the rank 
            rank[UP_v]++;
        }
    }
};
class Krus
{
    vector<vector<int>> edgelist;
    int V;
    vector<vector<int>>MST;
    public:
    Krus(int V)
    {
        this->V = V;
    }
    void addEdge(int x, int y, int w)
    {
        cout<<"Added:"<<x<<"<->"<<y<<" With weight"<<w<<endl;
        edgelist.push_back({w, x, y});
    }
    int kruskals_mst()
    {
        // 1. Sort all edges
        sort(edgelist.begin(), edgelist.end());
        // Initialize the DSU
        DisjointSet s(V);
        int ans = 0;
        for (auto edge : edgelist)
        {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];
 
            // take that edge in MST if it does form a cycle
            if (s.findUpar(x) != s.findUpar(y))
            {
                MST.push_back({x,y});
                s.UnionByRank(x, y);
                ans += w;
            }
        }
        return ans;
    }
    vector<vector<int>> getMst(){
        return MST;
    }
};

//PRIM'S AND DIJKSTRA ALGO 
/*
Prim's algorithm: 
priority queue-->  for the importance of the edge 
visited array -->  to avoid taking the same vertex twice as it violates the MST defination 
iterate in the pq --> if not visited add the mst -->check for the  neighbours -->if neighbours not visited add to the pq-->repeat 
*/
/*
Dijkstra  algorithm: 
priority queue --> for the importance of the path 
path array -->to store the count of shortest distance from the source to THAT particular node  
step 1:distance of source=0 and initial push the source node in the priority queue 
step 2: loop in the priority queue 
extract the currnode and the distance from the top of the priority queue 
step 3: iterate in the adjnodes of the current node 
Now, get the adjvertex and the weight to get their  
step 4:fromdistance +Toweight <distance to get their 
then,update the distance at  that node 
and then push this instance to the priority queue 
*/
class DIJandPrim{
    public: 
    vector<int> dijkstra(int V,vector<vector<int>> adj[],int S){
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> Path(V,INT_MAX);
        Path[S]=0;
        //{Distance,Node}
        pq.push({0,S});
        while(!pq.empty()){
            int currNode=pq.top().second;
            int Dis=pq.top().first;
            pq.pop();
            for(auto it:adj[currNode]){
                int adjV=it[0];
                int adjW=it[1];
                //Kami padatai distance of jitun yetoi + jethe calaloi......<==(for jethe calaloi tyala distance peksha )
                if(Dis+adjW<Path[adjV]){
                    Path[adjV]=Dis+adjW;
                    //check for this next 
                    pq.push({(Dis+adjW),adjV});
                }
            }
        }
        return Path;
    }
    int prim(int V,vector<vector<int>> adj[]){
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        vector<int> vis(V,0);
        //{weight,node}
        pq.push({0,0});
        int mstwt=0;
        while(!pq.empty()){
            auto it=pq.top();
            pq.pop();
            int node=it.second;
            int wt=it.first;
            if(vis[node]==1)continue;
            vis[node]=1;
            mstwt+=wt;
            for(auto it:adj[node]){
                int v=it[0];
                int w=it[1];
                if(!vis[v]){
                    pq.push({w,v});
                }
            }
        }
        return mstwt;
    }
};
int main()
{
    cout<<"Kruskal's algo"<<endl;
    int V;
    cout<<"Enter the vertex of the graph:"<<endl;
    cin>>V;
    Krus g(V);
    while(1){
        cout<<"1.InsertEdge  2.MSTwt  3.MSTgraph 4.stop"<<endl;
        int op;
        cout<<"Enter your choice:"<<endl;
        cin>>op;
        if(op==1){
            int w, u, v;
            cout<<"Enter the Weight of the edge:"<<endl;
            cin>>w;
            cout<<"Enter the vertex u:"<<endl;
            cin>>u;
            cout<<"Enter the vertex  v:"<<endl;
            cin>>v;
            g.addEdge(u,v,w);
        }
        else if(op==2){
            int ans=g.kruskals_mst();
            cout<<"The mst weight is:"<<ans<<endl;
        }
        else if(op==3){
            cout<<"The MST graph is..."<<endl;
            vector<vector<int>>mst=g.getMst();
            for(auto it:mst){
                cout<<"{"<<it[0]<<","<<it[1]<<"}"<<" ";
            }
            cout<<endl;
        }
        else if(op==4){
            cout<<"Execution stoped"<<endl;
            break;
        }
        else{
            cout<<"Invalid choice"<<endl;
            break;
        }
    }
    cout<<"Dijkstra algo."<<endl;
    int VD,S;
    cout<<"Enter the vertex of the graph:"<<endl;
    cin>>VD;
    vector<vector<int>> adj[VD];
    DIJandPrim gr;
    DIJandPrim gp;
    while(1){
        cout<<"1.insert edge  2.shortest distance  3.stop"<<endl;
        cout<<"-------------------------------------------------"<<endl;
        int op;
        cout<<"Enter your choice:"<<endl;
        cin>>op;
        if(op==1){
            int w, u, v;
            cout<<"Enter the Weight of the edge:"<<endl;
            cin>>w;
            cout<<"Enter the vertex u:"<<endl;
            cin>>u;
            cout<<"Enter the vertex  v:"<<endl;
            cin>>v;
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
        else if(op==2){
            int Src;
            cout<<"Enter the source from where to find the shortest distance:"<<endl;
            cin>>Src;
            vector<int> ans=gr.dijkstra(VD,adj,Src);
            for(int i=0;i<VD;i++){
                cout<<ans[i]<<" ";
            }
            cout<<endl;
        }
        else if(op==3){
            cout<<"Execution stopped..."<<endl;
            break;
        }
        else{
            cout<<"Invalid choice"<<endl;
            break;
        }
    }
    cout<<"prim's algo"<<endl;
    cout<<"Enter the vertex of the graph:"<<endl;
    int VP;
    cin>>VP;
    vector<vector<int>> adjp[VP];
    while(1){
        cout<<"1.Insert edge 2.MstWt 3.stop"<<endl;
        int op;
        cout<<"Enter your choice:"<<endl;
        cin>>op;
        if(op==1){
            int w, u, v;
            cout<<"Enter the Weight of the edge:"<<endl;
            cin>>w;
            cout<<"Enter the vertex u:"<<endl;
            cin>>u;
            cout<<"Enter the vertex  v:"<<endl;
            cin>>v;
            adjp[u].push_back({v,w});
            adjp[v].push_back({u,w});
        }
        else if(op==2){
            int ans=gp.prim(VP,adjp);
            cout<<"The mst weight is:"<<ans<<endl;
        }
        else if(op==3){
            cout<<"Execution stopped..."<<endl;
            break;
        }
        else{
            cout<<"Invalid choice"<<endl;
            break;
        }
    }
    return 0;
}