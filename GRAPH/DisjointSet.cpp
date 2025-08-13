#include<bits/stdc++.h>
using namespace std;
// it is used to find components in almost constant time !! 
// peudo steps: 
// find the ultimate parents of the both the vertex
// use the path compression to find the parents of all the component's node 
// path compression uses recursive backtracking to find the parents 
// while backtracking update the values to the new parent 
// then compare their ranks==>(attach the smaller one to the larger one)
// find==> update the parent array 
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
    void UnionBySize(int u,int v){
        //O(4 alpha)
        int UP_u=findUpar(u);
        int UP_v=findUpar(v);
        // same parent so no need of updating the parents
        // here you will only compare the size of the components 
        if(UP_u==UP_v) return;
        if(size[UP_u]>size[UP_v]){
            size[UP_v]=UP_u;
            size[UP_u]+=size[UP_u];
        }
        else {
            size[UP_u]=UP_v;
            size[UP_v]+=size[UP_u];
        }
    }
};
// by prim's algo.
int MST(int V,vector<vector<int>> adjList){
    int vis[V]={0};
    //PQ is used to maintain the importance of a edge by it's weight 
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    // {wt,node}
    pq.push({0,0});
    int sum=0;
    while(!pq.empty()){
        // We know  that the Priority queue's top will be the minimum,as it contains the least weight 
        auto it=pq.top();
        int node=it.second;
        int Wt=it.first;
        // already visted so don't add to the MST 
        if(vis[node]==1)continue;
        // Not visited so add it to the MST 
        vis[node]=1;
        sum+=Wt;
        // check the neighbours of that instance node 
        for(int it:adjList[node]){
            int currNode=it;// [0]
            int currWt=it;//[1]
            // here neighbouring node of the instance node is not visited 
            // so add it to the priority queue 
            if(!vis[currNode]){
                pq.push({currWt,currNode});
            }
        }
    }
    // in the end return the sum of the weight of the MST or the MST if necessary 
    return sum;
}

// Kruskal's algo 
int Kruskal(int V,vector<vector<int>> adjList){
    DisjointSet Set(V);
    // sorted the adjlist by weight 
    sort(adjList.begin(),adjList.end());
    int cost=0;
    // looping in the adjlist 
    for(auto it:adjList){
        // extacting the data of u,v and weight 
        int u=it[0];
        int v=it[1];
        int val=it[2];
        // if the Ulitimate parents of the components are different add it to the MST 
        // else don't 
        // For referance: striver's disjoint set video and kruskal's algo video 
        if(Set.findUpar(u)!=Set.findUpar(v)){
            cost+=val;
            // take the two components and join them as they don't belong to the same component 
            Set.UnionByRank(u,v);
        }
    }
    return cost;
}
int main()
{
    DisjointSet ds(7);
    ds.UnionByRank(1,2);
    ds.UnionByRank(2,3);
    ds.UnionByRank(4,5);
    ds.UnionByRank(6,7);
    ds.UnionByRank(5,6);
    if(ds.findUpar(3)==ds.findUpar(7)){
        cout<<"same\n";
        return 0;
    }
    cout<<"notsame\n";
    ds.UnionByRank(3,7);
    if(ds.findUpar(3)==ds.findUpar(7)){
        cout<<"same\n";
        return 0;
    }
    cout<<"notsame\n";
    return 0;
}