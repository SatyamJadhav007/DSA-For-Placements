#include<bits/stdc++.h> 
using namespace std; 

struct Edge{
    int u, v, w;
};
int main(){
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    vector<vector<int>> dp(V,vector<int>(V,9999)); 
    
    dp[0][0]=0;

    for(int i=1;i<V;i++){
        for(int v=0;v<V;v++){
            dp[i][v]=dp[i-1][v];
        } 

        for(auto &e:edges){
            if(dp[i-1][e.u]!=9999 && dp[i-1][e.u]+e.w<dp[i][e.v]){
                dp[i][e.v]=dp[i-1][e.u]+e.w;
            }
        } 

        cout<<"Iteration"<<i<<":"; 
        for(int v=0;v<V;v++){
            cout<<dp[i][v]<<" ";
        } 
        cout<<"\n";
    } 

    cout<<"\nFinal Distances from Source (0):\n"; 
    for(int i=0;i<V;i++){
        cout<<"Vertex "<<i<<": "<<dp[V-1][i]<<"\n";
    }

    for (auto &e : edges) {
        if (dp[V - 1][e.u] + e.w < dp[V - 1][e.v]) {
            cout << "\nGraph contains a NEGATIVE WEIGHT CYCLE\n";
            return 0;
        }
    } 


    cout << "\nTime Complexity = O(V * E)\n";
    cout << "Here: O(" << V << " * " << E << ") = O(" << V * E << ")\n";

    return 0;
}