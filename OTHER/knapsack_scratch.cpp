#include<bits/stdc++.h> 
using namespace std; 

struct Item{
    int value,weight; 
    Item(int v,int w):value(v),weight(w){}
}; 

bool cmp(Item a,Item b){
    double r1=(double)a.value/a.weight; 
    double r2=(double)b.value/b.weight; 
    return r1>r2;
} 

double fracKS(int W,vector<Item> Items){
    sort(Items.begin(),Items.end(),cmp); 

    int curr_weight=0; 
    double final_value=0.0; 
    cout<<"[Fractional-KnapSack(greedy approach)]"<<"\n";
    for(auto &it:Items){
        if(curr_weight+it.weight<=W){
            curr_weight+=it.weight; 
            final_value+=it.value;
        }else{
            int remain=W-curr_weight; 
            double fractional_Add=it.value*((double)remain/it.weight); 
            final_value+=fractional_Add; 
            break;
        }
    } 
    return final_value;
}

int KSdp(int W,vector<Item>Items){
    int n=Items.size(); 
    vector<vector<int>> dp(n+1,vector<int>(W+1,0)); 

    for(int i=1;i<=n;i++){
        for(int w=0;w<=W;w++){
            // Had a confusion here....
            // we are creating the answer on the basis of the current values
            if(Items[i-1].weight<=w){
                dp[i][w]=max(dp[i-1][w],Items[i-1].value+dp[i-1][w-Items[i-1].weight]);
            }else{
                dp[i][w]=dp[i-1][w];
            }
        }
    }
    for(int i=0;i<=n;i++){
        for(int w=0;w<=W;w++){
            cout<<dp[i][w]<<" ";
        } 
        cout<<endl;
    } 
    return dp[n][W];
}
int main(){
    vector<Item>items={{60,10},{100,20},{120,30}}; 
    int capacity=50;
    cout << "Items (Value, Weight): ";
    for (auto &it : items)
        cout << "(" << it.value << "," << it.weight << ") ";
    cout << "\nCapacity = " << capacity << "\n";

    // Fractional Knapsack Result
    double fractionalResult = fracKS(capacity, items);
    cout << "\nFinal Result (Fractional Knapsack - Greedy) = "
         << fractionalResult << "\n";

    // 0/1 Knapsack DP Result
    int dpResult = KSdp(capacity, items);
    cout << "\nFinal Result (0/1 Knapsack - DP) = "
         << dpResult << "\n";
}