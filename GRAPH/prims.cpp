#include<bits/stdc++.h>
using namespace std;
class graph{
    vector<vector<pair<int,int>>>AdjList;
    public:
    graph(int V){
        int u,v,w;
        while(V--){
            cout<<"Enter the source edge"<<endl;
            cin>>u;
            cout<<"Enter the destination edge"<<endl;
            cin>>v;
            cout<<"Enter the weight for the graph"<<endl;
            cin>>w;
            AdjList[u].push_back({v,w});
        }
    }
    int PrimsAlgo(int V){
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        int vis[V]={0};
        pq.push({0,0});
        int sum=0;
        while(!pq.empty()){
            auto it=pq.top();
            int node=it.first;
            int weight=it.second;
            if(vis[node]==1) continue;
            vis[node]=1;
            sum+=weight;
            for(auto it:AdjList[node]){
                int currNode=it.first;
                int currWeight=it.second;
                if(!vis[currNode]){
                    pq.push({currNode,currWeight});
                }
            }
        }
        return sum;
    }

};
int main()
{
    graph G(4);
    int sum=G.PrimsAlgo(4);
    cout<<"The sum is "<<endl;
    cout<<sum<<endl;
    return 0;
}