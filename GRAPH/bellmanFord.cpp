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
    // V,V wala DP create kr 
    dp[0][0]=0;//at start source node this is...

    for(int i=1;i<V;i++){
        //copy previous iterations results
        for(int v=0;v<V;v++){
            dp[i][v]=dp[i-1][v];
        } 
        // Relaxation Part
        for(auto &e:edges){
            //U should be reachable and dist[u]+currWeight <dist[v]
            if(dp[i-1][e.u]!=9999 && dp[i-1][e.u]+e.w<dp[i][e.v]){
                //why dp[i][v]?? and why dp[i-1][e.u]??(because your using previous u dist)
                //To update the current v dist
                dp[i][e.v]=dp[i-1][e.u]+e.w;
            }
        } 
        // Display the updates 
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
    //Vth iteration for negative edge cycle check...
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