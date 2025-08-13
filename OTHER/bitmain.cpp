#include<iostream>
using namespace std;
void reversestr(int i, int j,string &str){
    if (i>j)
    {
        return;
    }
    swap(str[i],str[j]);
    i++;
    j--;
    reversestr(i,j,str);   
}
string decimaltobinary(int x){
  string res="";
  while (x!=0)
  {
    x=x/2;
    if(x%2==1){
       res=res+"1";
    }
    else{
       res=res+"0" ;
    }
    
  }
  return res;
}
void swap(int &a, int &b){
  a=a^b;//0010 i.e 2
  b=a^b;//0010  0100 i.e 3(0110) 
  a=a^b;//0100  0110 i.e 0010 2  
  cout<<" a is:"<<a<<endl;
  cout<<" b is:"<<b<<endl;
}
int setbits(int n){
  int cnt=0;
  while (n!=0)
  {
    n=(n&(n-1));
    cnt++;
  }
  return cnt; 
}
// ith set or not: (num&(1<<i)!=)
// ith clear: (num&~(1<<i))
// ith set to 1: (num |(1<<i))
// remove the rightmost setbit: (num&num-1)
// toggle ith set: num^(1<<i)
int main(){
    //int x;
    //cout<<"Enter the value of n:";
    //cin>>x;
    int num= INT32_MAX;
    int a=3;// 0110
    int b=2;// 0100
    int And= a&b;//0100
    int OR= a|b;//0110
    //int n=~a;// 1001
    int XOR= a^b;//0010
    //cout<<"and:"<<And<<endl;
    //cout<<"OR:"<<OR<<endl;
    //cout<<"not:"<<n<<endl;
    //cout<<"Xor:"<<XOR<<endl;
    //cout<<" a*(2^^n):"<<(a<<num)<<endl;
    //cout<<" a/(2^^n):"<<(b>>3)<<endl;
    swap(a,b);
    int ans=setbits(15);
    cout<<ans;
  return 0;
}