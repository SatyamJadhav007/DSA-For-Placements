#include <iostream>
#include <queue>
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
Node*tree(Node *&root)
{
  // entering the data of root
  int data;
  cout << "Enter data for tree:" << endl;
  cin >> data;
  //creating a root
  root = new Node(data);
  if (data == -1)
  {
    return NULL;
  }
  // enter left
  cout << "Enter in left for " << data << endl;
  root->left = tree(root->left);
  // enter right
  cout << "Enter in right for " << data << endl;
  root->right = tree(root->right);
  return root;
}
void levelordertraversal(Node *root)
{
  cout<<"the levelordertraversal is:"<< endl;
  queue<Node *> q;
  q.push(root);
  q.push(NULL);
  while (!q.empty())
  {
    Node *temp = q.front();
    q.pop();
    if (temp == NULL)
    {
      cout << endl;
      if (!q.empty())
      {
        q.push(NULL);
      }
    }
    else
    {
      cout << temp->data << " ";
      if (temp->left != NULL)
      {
        q.push(temp->left);
      }
      if (temp->right != NULL)
      {
        q.push(temp->right);
      }
    }
  }
}
void InOrder(Node* root){
  if(root!=NULL){
    InOrder(root->left);
    cout<<root->data;
    InOrder(root->right);
  }
}
void PreOrder(Node* root){
  if(root!=NULL){
    PreOrder(root->left);
    PreOrder(root->right);
    cout<<root->data;
  }
}
void postOrder(Node* root){
  if(root!=NULL){
    postOrder(root->left);
    postOrder(root->right);
    cout<<root->data<<endl;
  }
}
// you made here two containers
// as the func call for and right are common in usecases..... 
// diameter and height 
// created two pairs for calls in left and right and then used them in the recursive calls for diameter and height
pair<int,int> fastdiameter(Node* root){
  if (root==NULL)
  {
    pair<int,int> p= make_pair(0,0);
    return p;
  }
  pair<int,int> left=fastdiameter(root->left);
  pair<int,int> right=fastdiameter(root->right);
  // there are 3 posibilities:
  // diameter in left| right| combine;
  // diameter is the longest distance between two nodes till leaf node(L->R)
  // op3 is heightL + heightR + root;
  int op1= left.first;
  int op2=right.first;
  int op3=left.second+right.second+1;
  pair<int,int> ans;
  // diameter
  ans.first=max(op1,max(op2,op3));;
  // height
  ans.second=max(left.second,right.second)+1;
  return ans;
}
int height(Node*root){
  if (root==NULL)
  {
    return 0;
  }
  //recursive call for left
  int l=height(root->left);
  //recursive call for right
  int r=height(root->right);
  int ans=max(l,r) +1;
  return ans;
}
int diameter(Node* &root){
  return fastdiameter(root).first;
  // there is a better way to solve this question by using pairs
}
pair<bool,int> fastbalanced(Node*root){
  if (root==NULL)
  {
    pair<bool,int> p=make_pair(true,0);
    return p;
  }
  pair<int,int> left=fastbalanced(root->left);
  pair<int,int> right=fastbalanced(root->right);
  // check in left
  bool op1= left.first;
  // check in right
  bool op2= right.first;
  // diffrence in heights
  bool diff=abs(left.second-right.second)<=1;
  pair<bool,int> ans;
  ans.second=max(left.second,right.second)+1;
  if(op1 && op2 && diff){
    ans.first=true;
  }
  else{
    ans.first=false;
  }
}
bool isbalanced(Node* root){
    return fastbalanced(root).first;
  }
int main()
{
  Node *root = NULL;
  root = tree(root);
  levelordertraversal(root);
  int ans=height(root);
  int ans2=diameter(root);
  bool ans3=isbalanced(root);
  cout<<"the height of the tree is:"<<ans<<endl;
  cout<<"the diameter is:"<<ans<<endl;
  cout<<"the tree is balanced or not:"<<ans3;
  return 0;
}
// 1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 7 9 -1 -1 8 20 -1 -1 -1
//inorder{L,N,R}, preorder{N,L,R} , postorder{L,R,N} traversals