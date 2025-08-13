#include<bits/stdc++.h>
using namespace std;
class Node
{
public:
  int data;
  Node *left;
  Node *right;
  Node(int d)
  {
    this->data = d;
    this->left = NULL;
    this->right = NULL;
  }
};
vector<int> InorderByThread(Node* root){
    vector<int> Inorder;
    Node* curr=root;
    while(curr!=NULL){
        // case 1: here there is no left node so take the node's data and GO RIGHT!!! 
        if(curr->left==NULL){
            Inorder.push_back(curr->data);
            curr=curr->right;
        }
        // case 2: left exists.....................
        //OBSERVATION:WE ALWAYS DO THE LEFT CHA RIGHT CHECK IN IF IT EXISTS 
        //AND THEN IF IT EXISTS THEN WE CHECK FOR THREAD OR NOT.... 
        else{
            // GO IN LEFT SUBTREE'S RIGHT-MOST NODE
            Node*prev=curr->left;
            while(prev->right &&prev->right!=curr){
                prev=prev->right;
            }
            // case 3: if there is no thread then make a thread and go left...(By defination of inorder)!!! 
            if(prev->right==NULL){
                prev->right=curr;
                curr=curr->left;
            }
            //case 4: there exists a thread as prev is pointing to something so 
            //cut the thread and go to right!!!! 
            else{
                prev->right=NULL;
                Inorder.push_back(curr->data);
                curr=curr->right;
            }
        }
    }
    return Inorder;
}

// Same code for preorder just one change instead of taking the node when coming from thread 
// We will take the node while making a thread 
vector<int> PreorderByThread(Node* root){
    vector<int> preorder;
    Node* curr=root;
    while(curr!=NULL){
        // case 1: here there is no left node so take the node's data and GO RIGHT!!! 
        if(curr->left==NULL){
            preorder.push_back(curr->data);
            curr=curr->right;
        }
        // case 2: left exists.....................
        //OBSERVATION:WE ALWAYS DO THE LEFT CHA RIGHT CHECK IN IF IT EXISTS 
        //AND THEN IF IT EXISTS THEN WE CHECK FOR THREAD OR NOT.... 
        else{
            // GO IN LEFT SUBTREE'S RIGHT-MOST NODE
            Node*prev=curr->left;
            while(prev->right &&prev->right!=curr){
                prev=prev->right;
            }
            // case 3: if there is no thread then make a thread and go left...(By defination of inorder)!!! 
            if(prev->right==NULL){
                prev->right=curr;
                preorder.push_back(curr->data);
                curr=curr->left;
            }
            //case 4: there exists a thread as prev is pointing to something so 
            //cut the thread and go to right!!!! 
            else{
                prev->right=NULL;
                curr=curr->right;
            }
        }
    }
    return preorder;
}
int main()
{
    
    return 0;
}