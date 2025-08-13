#include <iostream>
#include<map>
using namespace std;
class Node
{
public:
  int data;
  Node *next;
  // constructor was created to make nodes
  Node(int data)
  {
    this->data = data;
    this->next = NULL;
  }
  ~Node()
  {
    int value = this->data;
    if (this->next != NULL)
    {
      delete next;
      this->next = NULL;
    }
  }
};
void inserttail(Node *&tail, int d)
{
  // neww node
  Node *temp = new Node(d);
  // last element chan pointer la tu temp che pointer dele
  tail->next = temp;
  // tail was updated
  tail = temp;
}
void inserthead(Node *&head, int d)
{
  // new node was created here
  Node *temp = new Node(d);
  // jho temp cha pointer ahe tyala head cha pointer dela
  temp->next = head;
  // head was updated
  head = temp;
}
void printll(Node *&head)
{
  // phudcha pointer la mi head pointer chi value deli
  Node *phudcha = head;
  cout << "[ ";
  // javarparayant phudcha doesnt reach Null print kr
  while (phudcha != NULL)
  {

    cout << phudcha->data << "->";
    phudcha = phudcha->next;
  }
  cout << "NULL ]";
  cout << endl;
}
void insertatposition(Node *&head, int position, int data, Node *tail)
{

  // temp at head
  // case 1: insert at 1st position
  if (position == 1)
  {
    inserthead(head, data);
    return;
  }

  Node *temp = head;
  int count = 1;
  // updating temp till n-1
  while (count < position - 1)
  {
    temp = temp->next;
    count++;
  }
  // case2 : inserting at last position
  if (temp->next == NULL)
  {
    inserttail(tail, data);
    tail = tail->next;
    return;
  }
  // creating the node we are supposed to add
  Node *nodetoadd = new Node(data);
  //[NTA cha next]------>[TEMP CHA NEXT}]
  nodetoadd->next = temp->next;
  //[temp cha next]----->[NTA ]
  (*temp).next = nodetoadd;
}
void deletehead(int position, Node *&head)

{
  Node *prev = NULL;
  Node *curr = head;
  if (position == 1)
  {
    Node *temp = head;
    head = head->next;
    temp->next = NULL;
    delete temp;
  }
  else
  {
    Node *prev = NULL;
    Node *curr = head;
    int count = 1;
    while (count < position)
    {
      prev = curr;
      curr = curr->next;
      count++;
    }
    prev->next = curr->next;
    curr->next = NULL;
    delete curr;
  }
}
void reverse(Node *&head)
{
  Node *prev = NULL;
  Node *curr = head;
  while (curr != NULL)
  {
    Node *forward = curr->next;
    curr->next = prev;
    prev = curr;
    curr = forward;
  }
  head = prev;
}
void middleofll(Node *&head)
{
  Node *temp1 = head;
  int len = 1;
  while (temp1 != NULL)
  {
    temp1 = temp1->next;
    len++;
  }
  cout << "the middle is " << (len / 2) << endl;
}
void reversek(Node* &head, int k){
  Node* curr=head;
  Node* prev=NULL;
  Node* forward=curr->next;
  int cnt=0;
  while (cnt<k && curr!=NULL)
  {
    Node *forward = curr->next;
    curr->next = prev;
    prev = curr;
    curr = forward;
    cnt++;
  }

  prev=head;
}
bool iscircular(Node*&head){
  Node *temp=head->next;
  while(temp!=NULL && temp!=head){
    temp=temp->next;
  }
  if (temp==head)
  {
    return true;
  }
  else return false;
  
}
int main()
{
  Node *n2 = new Node(1);
  Node *head = n2;
  Node *tail = n2;
  printll(head);
  inserttail(tail, 2);
  printll(head);
  inserttail(tail, 3);
  printll(head);
  inserttail(tail, 4);
  printll(head);
  inserttail(tail, 5);
  printll(head);
  inserttail(tail, 6);
  printll(head);
  inserttail(tail, 7);
  insertatposition(head,4,12,tail);
  printll(head);
  deletehead(4,head);
  printll(head);
  reverse(head);
  printll(head);
}