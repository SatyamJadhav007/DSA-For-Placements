#include<bits/stdc++.h>
using namespace std; 
int a[100005],seg[100005]; //hard-coded the size of the array and the segment tree for convenience 

//The build function is used to build the segment tree 
//i=>index of the segment tree ,l=>left index of the array ,r=>right index of the array
void build(int i,int l,int r){
    // You have reached the leaf node so update the seg's i val with the array's i val 
    // why??
    if(l==r){
        seg[i]=a[i]; 
        return;
    } 
    int mid=(l+r)/2; 
    //left part of the tree 
    build(2*i+1,l,mid); 
    //right part of the tree 
    build(2*i+2,mid+1,r); 
    //update the value of the parent 
    //it's like we found the answers for leaf nodes and then we update the parent 
    seg[i]=seg[2*i+1]+seg[2*i+2];
}
//in trees i=>root, then 2*i+1 is the left child and 2*i+2 is the right child for array representation 
//segment tree => is the tree of ranges sum 
//     root 
//   /     \ while going down (divide....)->compute the left val and on the basis of that compute the parent val's
// left   right 
//................. 
//Query in ST
// l,r is the range of the question that we are asked (i.e. give me the sum of the range from l to r) 
//low,high => is our segment tree's range and idx =>starting index for the search 
int query(int idx,int low,int high,int l,int r){
    if(low<=l && high>=r){ //The node is compeletely inside the range 
        return seg[idx];
    } 
    if(low>r || high<l){//The node is compeletely outside the range
        return INT_MIN;
    } 
    //here some nodes are a part of our range and some are not so eliminate the nodes and add!
    int mid=(low+high)/2; 
    return query(2*idx+1,low,mid,l,r)+query(2*idx+2,mid+1,high,l,r);
}
int main()
{
    int n; 
    cin>>n; 
    for(int i=0;i<n;i++){
        cin>>a[i];
    } 
    build(0,0,n-1);
    int q; 
    cin>>q; 
    while(q--){
        int l,r; 
        cin>>l>>r; 
        cout<<query(0,0,n-1,l,r)<<endl;

    }
    return 0;
}