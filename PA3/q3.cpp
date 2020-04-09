#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
using namespace std;

int insertLinear(int x, vector<int> & linear);
int insertQuad(int x, vector<int> & quad);
int insertDuble(int x, int dubHash, vector<int> & duble);

int main()
{
  int linCollides=0;
  int quadCollides= 0;
  int dubCollides = 0;
  int quadInc;
  int tableSize;
  bool fail = false;
  int x, count=0;
  int doubleHash;

  srand(time(NULL));
  cout<<"enter the size of the table ";
  cin>>tableSize;
  vector<int> linear(tableSize,-1);//initalize each table to -1 for empty
  vector<int> quad(tableSize,-1);  //initalize each table to -1 for empty
  vector<int> duble(tableSize,-1);  //initalize each table to -1 for empty
  do{
   doubleHash = rand()%tableSize;
  }while (doubleHash < tableSize/10 && doubleHash%tableSize==0);

  while(count < tableSize && !fail)
  {
    x= rand()%tableSize;// value to insert
	quadInc=insertQuad(x,linear);
	if (quadInc < 0)
		fail = true;
	else
	{
	 quadCollides += quadInc;
	 linCollides+=insertLinear(x,linear);
	 dubCollides+=insertDuble(x,doubleHash, duble);
	}
	count++;
  }
  cout<<"Num linear collides "<<linCollides<<endl;
  cout<<"Num quadratic collides "<<quadCollides<<endl;
  cout<<"Num double hash collides "<<dubCollides<<endl;
  return 0;
}

int insertLinear(int x, vector<int> & linear)
{
  // Remove below line after your implementaion
  int col = 0;
  int pos = x;
  bool same = false;
  while(linear.at(pos) != -1 && pos < linear.size() && !same){
      col += 1;
      pos += 1;
      pos = pos % linear.size();
      if (x == linear.at(pos)){  //check if the number insertig is the same as the number inside of hash table
          same = true;
      }
  }
  linear.at(pos) = x;
  return col;
}

int insertQuad(int x, vector<int> & quad)
{
  // Remove below line after your implementaion
  int i = 0;
  int pos = x % quad.size();
  int col = 0;
  bool ins = false;
  bool find = false;  //check if the element has already been inserted
  while (quad.at(pos) != -1 && col < quad.size() && !ins && !find){
      i += 1;
      col += 1;
      if (i+i*i > quad.size()){
          ins = true;
      }
      if (x == quad.at(pos)){
          find = true;
      }
      pos = pos + i + i*i;
      pos = pos % quad.size();
  }
  if (pos >= quad.size() || ins){   //if insertion fail
      return -1;
  }
  else{
      quad.at(pos) = x;
      return col;
  }
  return 0;
}

int insertDuble(int x, int dubHash, vector<int> & duble)
{
  // Remove below line after your implementaion
  int col = 0;
  int pos = x % duble.size();
  while(duble.at(pos) != -1 && col < duble.size()){
      col += 1;
      pos += dubHash - x % dubHash;
      pos = pos % duble.size();
      if (x == duble.at(pos)){
          break;
      }
  }
  duble.at(pos) = x;
  return col;
}
