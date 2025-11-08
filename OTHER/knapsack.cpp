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

double fractionalKnapsack(int W,vector<Item> items){
    //sort the items by value/weight ratio
    sort(items.begin(),items.end(),cmp); 

    int currWeight=0; 
    double finalValue=0.0; 
    cout<<"\n[Fractional Knapsack - Greedy Selection]\n"; 
    for(auto &it:items){
        // You can take the full weight for this portion...
        if(currWeight+it.weight<=W){
            currWeight+=it.weight; 
            finalValue+=it.value; 
            cout<<"Taking FULL item (Value="<<it.value<<", Weight="<<it.weight<<") --> Total Value = "<<finalValue<<"\n"; 
        }else{
            //Get the remaining portion...
            int remain=W-currWeight; 
            //Get the equivalent fractionValue from the current weight and value
            double fractionValue=it.value*((double)remain/it.weight); 
            finalValue+=fractionValue; 
            cout<<"Taking FRACTION of item (Value="<<it.value<<", Weight="<<it.weight<<", Taken="<<remain<<") --> Total Value = "<<finalValue<<"\n"; 
            break;
        }
    } 

    return finalValue;
} 


int knapSackDP(int W,vector<Item>items){
    int n=items.size();
    // dp[n][w] n=number of items(valuei,weighti),w=All the possible weight there can be 
    vector<vector<int>>dp(n+1,vector<int>(W+1,0)); 

    for(int i=1;i<=n;i++){
        for(int w=0;w<=W;w++){
            //If the previous item weight is less than current weight
            //It means that we can take this weight as the resultant value is not negative
            if(items[i-1].weight<=w){
                dp[i][w]=max(dp[i-1][w],items[i-1].value+dp[i-1][w-items[i-1].weight]);
            }else{
                // keep the previous result as it is if the current weight is impossible
                dp[i][w]=dp[i-1][w];
            }
        }
    }

    cout<<"\n[0/1 Knapsack DP Table]\n"; 
    for(int i=0;i<=n;i++){
        for(int w=0;w<=W;w++){
            cout<<dp[i][w]<<" ";
        } 
        cout<<"\n";
    }

    return dp[n][W];
}
int main()
{
    vector<Item>items={{60,10},{100,20},{120,30}}; 
    int capacity=50;
    cout << "Items (Value, Weight): ";
    for (auto &it : items)
        cout << "(" << it.value << "," << it.weight << ") ";
    cout << "\nCapacity = " << capacity << "\n";

    // Fractional Knapsack Result
    double fractionalResult = fractionalKnapsack(capacity, items);
    cout << "\nFinal Result (Fractional Knapsack - Greedy) = "
         << fractionalResult << "\n";

    // 0/1 Knapsack DP Result
    int dpResult = knapSackDP(capacity, items);
    cout << "\nFinal Result (0/1 Knapsack - DP) = "
         << dpResult << "\n";

    // Show that Greedy does NOT give optimal solution for 0/1 case
    cout << "\n[Comparison]\n";
    cout << "Fractional (Greedy) = " << fractionalResult << "\n";
    cout << "0/1 DP (Optimal)    = " << dpResult << "\n";

    if (fractionalResult != dpResult)
        cout << "\nConclusion: Greedy strategy does NOT yield an optimal solution "
                "for 0/1 Knapsack.\n";
    else
        cout << "\n(For this dataset, both values matched, but greedy is STILL "
                "not reliable for 0/1 knapsack.)\n";

    // Time Complexity
    cout << "\nTime Complexity:\n";
    cout << "Fractional Knapsack (Greedy) = O(n log n)\n";
    cout << "0/1 Knapsack (DP)            = O(n * W)\n";
    return 0;
}