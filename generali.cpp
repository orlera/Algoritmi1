#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void battaglie();


struct nodo{
  vector<int> figli;
  bool figlio;
};

vector<nodo> grafo;
vector<pair <int,int> > ris;
vector<int> capi; 
int N;

int main(){
  ifstream in("input.txt");
  int M;
  in>>N>>M;
  grafo.resize(N);
  for(int i=0;i<M;i++){
    int from, to;
    in>>from>>to;
    grafo[from].figli.push_back(to);
  }
  battaglie();
  ofstream out("output.txt");
  out<<capi.size()<<"\n";
  for(int i=0;i<capi.size();i++){
    out<<capi[i]<<" ";
  }
  out<<"\n";
  for (int i = 0; i < ris.size(); ++i){
    out<<ris[i].first<<" "<<ris[i].second<<"\n";
  }

}

void battaglie(){
  for(int i=0;i<N;i++){
    for(int j=0;j<grafo[i].figli.size();j++){
      int tmp=grafo[i].figli[j];
      bool val=false;
      for(int k=0;k<ris.size();k++){
        if(ris[k].second==tmp){
          val=true;
        }
      }
      if(!val){
        pair<int, int> x=make_pair(i,tmp);
        ris.push_back(x);
        grafo[tmp].figlio=true;
      }
    }
  }
  for(int i=0;i<N;i++){
    if(!grafo[i].figlio) {
      capi.push_back(i);
    }
  }
}
