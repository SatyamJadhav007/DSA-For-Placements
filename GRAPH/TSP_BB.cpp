#include<bits/stdc++.h>
using namespace std;
int N;
int bestCost=INT_MAX; 
vector<int>bestPath;
void updateSol(vector<vector<int>>&cost,vector<int>&path,int currCost){
    int totalCost=currCost+cost[path[N-1]][path[0]]; 
    if(totalCost<bestCost){
        bestCost=totalCost; 
        bestPath=path; 
        bestPath.push_back(path[0]);
    }
}
void tspBB(vector<vector<int>>&cost,vector<bool>&visited,vector<int> &path,int level,int currCost){
    if(level==N){
        updateSol(cost,path,currCost); 
        return;
    }
    for(int city=0;city<N;city++){
        if(!visited[city]){
            //from current level->current city
            int newCost=currCost+cost[path[level-1]][city]; 
            //bound was applied here delete the node if the cost is worse than the current cost 
            if(newCost<bestCost){
                visited[city]=true; 
                path[level]=city; 
                tspBB(cost,visited,path,level+1,newCost); 
                //Backtrack if invalid 
                visited[city]=false;
            }
        }
    }
}
int main()
{
    cout<<"Enter the number of cities:"; 
    cin>>N; 
    vector<vector<int>>cost(N,vector<int>(N)); 
    cout<<"\nEnter Cost Matrix("<<N<<"x"<<N<<"):\n"; 
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>cost[i][j];
        }
    } 
    // Cost,Visited,path,level,currCost
    // iterate in all cities similar to what we are doing with n queens(all rows)
    // newCost khadd -> newCost=currCost+cost[path[level-1]][city]
    vector<int>path(N); 
    vector<bool>visited(N,false); 
    path[0]=0; 
    visited[0]=true; 
    cout<<"Solving TSP using LC Branch and Bound...\n"; 
    tspBB(cost,visited,path,1,0); 

    cout<<"\n Minimum Cost = "<< bestCost<<" \n"; 
    cout<<"Optimal Path = "; 
    for(int city:bestPath){
        cout<<city<<" ";
    } 
    cout<<"\n";
    return 0;
}