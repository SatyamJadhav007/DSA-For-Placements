#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int u, v,w;
};
int main()
{
    int V,E; 
    cout<<"Enter the number of Vertics:"; 
    cin>>V; 
    cout<<"\nEnter the number of Edges:"; 
    cin>>E; 
    vector<Edge> edges(E);
    for(int i=0;i<E;i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    } 
    vector<vector<int>>dp(V,vector<int>(V,9999)); 
    dp[0][0]=0; 
    for(int i=1;i<V;i++){
        for(int v=0;v<V;v++){
            dp[i][v]=dp[i-1][v];
        } 
        for(auto &e:edges){
            if(dp[i-1][e.u]!=9999&& dp[i-1][e.u]+e.w<dp[i][e.v]){
                dp[i][e.v]=dp[i-1][e.u]+e.w;
            }
        } 
        cout<<"Iteration"<<i<<" "; 
        for(int v=0;v<V;v++){
            cout<<dp[i][v]<<" ";
        } 
        cout<<"\n";
    } 
    for(auto &e:edges){
        if(dp[V-1][e.u]!=9999&& dp[V-1][e.u]+e.w<dp[V][e.v]){
            cout<<"THERE IS A NEGATIVE EDGE CYCLE!"; 
            return 0;
        }
    }
    cout<<"Final Distances are: ";
    for(int i=0;i<V;i++){
        cout<<dp[V-1][i]<<" ";
    } 
    return 0;
}