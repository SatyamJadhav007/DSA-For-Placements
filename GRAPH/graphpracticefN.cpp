#include<iostream>
#include<vector>
#include<queue>
using namespace std;
// this is 16th sep i will practice 4 graph question (i will embrace the difficult!)
//QUESTON 1 OF GRAPH : 
// dfs function to mark neighbours in visited 
void dfs(int node,vector<int> adjlist[],int  visited[]){
    visited[node]=1;
    for(auto it:adjlist[node]){
        if(!visited[it]){
            dfs(it,adjlist,visited);
        }
    }
}
int numProvinces(vector<vector<int>> adj, int v){
    vector<int> adjlist[v];
    for(int i=0;i<adj.size();i++){
        // creating an adje list not taking duplicate stuff
        for(int j=0;i<adj[0].size();j++){
            if(adj[i][j]==1 && i!=j){
                adjlist[i].push_back(j);
                adjlist[j].push_back(i);
            }
        }
    }
    int  visited[v];
    visited[0]=1;
    int answer=0;
    for(int i=0;i<=v;i++){
        if(!visited[i]){
            answer++;
            dfs(i,adjlist,visited);
        }
    }
    return answer;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// QUESTION 2: ROTTEN ORANGES 
int orangesRotting(vector<vector<int>>& grid){
    int m=grid.size(),n=grid[0].size(),tot=0,days=0,cnt=0;
    queue<pair<int,int>> rotten;
    // to count total number of oranges 
    for(int i=0;i<m;i++){
        for(int j=0;i<n;j++){
            if(grid[i][j]==2)rotten.push({i,j});
            if(grid[i][j]!=0) tot++;
        }
    }
    int nx[4]={0,0,1,-1};
    int ny[4]={1,-1,0,0};
    // initital it will not be as there is an rotten orange in the queue
    while(!rotten.empty()){
        int k=rotten.size();
        // the counts the number of rotten oranges by queue size 
        cnt+=k;
        //
        while(k--){
            // rotten cordinate 
            int X=rotten.front().first,Y=rotten.front().second;
            rotten.pop();
            for(int i=0;i<4;i++){
                // from the rotten coordinate to the neightbours 
                int nextX=X+nx[i];
                int nextY=Y+ny[i];
                // we are taking the rotten oranges for the instances 
                if(nextX<0 || nextY<0|| nextX>=m || nextY>=n || grid[nextX][nextY]!=1) continue;
                grid[nextX][nextY]=2;
                rotten.push({nextX,nextY});
            }
        }
        // this means that the queue has rotten oranges and thus increased 
        if(!rotten.empty()) days++;
    }
    // this means all oranges are rotten and valid time else not and reuturn -1
    return tot==cnt ? days: -1;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// QUESTION 3: FLOOR FILL 
void dfs(int row,int col,vector<vector<int>>& image,vector<vector<int>>& ans,int inicolor,int newcolor,int delrow[],int delcol[]){
    ans[row][col]=newcolor;
    int m=image.size();
    int n= image[0].size();
    for(int i=0;i<4;i++){
        int nrow=row+delrow[i];
        int ncol=col+delcol[i];
        if(nrow>=0 && ncol>=0 && nrow<m && ncol<n&& image[nrow][ncol]==inicolor && ans[nrow][ncol]!=newcolor){
            dfs(nrow,ncol,image,ans,inicolor,newcolor,delrow,delcol);
        }
    }
}
vector<vector<int>> floodFill(vector<vector<int>>& image, 
    int sr, int sc, int newcolor)
{
    vector<vector<int>> ans=image;
    int inicolor=image[sr][sc];
    int delrow[]={0,0,-1,1};
    int delcol[]={1,-1,0,0};
    dfs(sr,sc,image,ans,inicolor,newcolor,delrow,delcol);
    return ans;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
int main()
{
    
    return 0;
}