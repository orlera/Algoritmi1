#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

void battaglie();
void disprezza();


struct nodo{
  vector<int> figli;
  vector<int> disprezza;
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
  disprezza();
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



void disprezza(){
  for(int i=0;i<N;i++){
    queue<int> q;
    for(int j=0;j<grafo[i].figli.size();j++){
      grafo[i].disprezza.push_back(grafo[i].figli[j]);
      q.push(grafo[i].figli[j]);     
      grafo[grafo[i].figli[j]].figlio=true;
    }
    while(!q.empty()){
      int tmp=q.front();
      q.pop();
      for(int k=0;k<grafo[tmp].figli.size();k++){
        int t=grafo[tmp].figli[k];
        if(!grafo[t].figlio && t!=i){
          grafo[i].disprezza.push_back(t);
          q.push(t);
          grafo[t].figlio=true;
        }
      }
    }
    for(int k=0;k<N;k++){
      grafo[k].figlio=false;
    }
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
      for(int k=0;k<grafo[tmp].disprezza.size();k++){
        int t=grafo[tmp].disprezza[k];
        if(t==i){
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
