//#define __STDC_LIMIT_MACROS 
#include<iostream>
#include <cassert>
#include <cstdint>
//#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <vector>
//#include <limits>

using namespace std;


int ind(int i,int j,int num){return i*num+j;}//num for total num (this is n*n mat)
int max(int x,int y){return x>y?x:y;}
/*
-100<=w<=100
*/

struct CycleBreaker
{
    char graphType;
    int n = 0;  //numOfVertices
    int m = 0;  //numOfEdges
    int64_t sum = 0;
    vector<int16_t> edges; //denote which vertex connect weight(-100~100)
    vector<int32_t> edgeIndex;//ith edge(m:50000000)
    vector<int16_t> keys;   //vertex key (-100~100)
    vector<int16_t> parents;//(10000)
    vector<bool> tree; //whether vertice is searched (n)
    vector<int16_t> edge_u;
    vector<int16_t> edge_v;
    vector<int16_t> edge_w;
    vector<bool> checkEdges;//store m edge 

    ofstream ofs;

    CycleBreaker(const char *inputFile){ //constructor
        ifstream ifs(inputFile);
        if(!ifs)
            return;
        ifs >> graphType;
        ifs >> n;
        ifs >> m;
        
        edges.assign(n*n,INT16_MIN);
        edgeIndex.assign(n*n,-1);
        keys.assign(n,INT16_MIN);
        parents.assign(n,-1);
        tree.assign(n,false);

        edge_u.assign(m,-1);
        edge_v.assign(m,-1);
        edge_w.assign(m,INT16_MIN);
        checkEdges.assign(m,false);

        for(int i = 0; i < m; i++){
            uint16_t a = 0,b = 0;
            int16_t w = 0;
            ifs >> a >> b >> w;
            edges[ind(a,b,n)] = w;
            edgeIndex[ind(a,b,n)] = i;
            edge_u[i] = a;
            edge_v[i] = b;
            edge_w[i] = w;

            sum+=w;
            if(i==0){
                keys[a]=0;
            }
            //weights[a] = w;
            if(graphType != 'd'){
                edges[ind(b,a,n)] = w;
                edgeIndex[ind(b,a,n)] = i;
            }
        }
        MST();
    }
    void MST(){
        if(graphType!='d'){
            MST_Undirected();
        }
        else{
            MST_Directed();
        }
    }
    void MST_Undirected(){
        for(int i = 0;i<n;i++){
            int u = extractMax();//On2
            if(i!=0){
                sum-=edges[ind(parents[u],u,n)];
                //edges[ind(parents[u],u,n)]=INT16_MIN;
                //edges[ind(u,parents[u],n)]=INT16_MIN;
                checkEdges[edgeIndex[ind(parents[u],u,n)]] = true;
            }
            for(int v = 0;v < n;v++){
                if(edges[ind(u,v,n)]!=INT16_MIN){
                    if(!tree[v]&&edges[ind(u,v,n)]>keys[v]){
                        parents[v]=u;
                        keys[v]=edges[ind(u,v,n)];
                    }
                }
            }
        }
    }
    void MST_Directed(){
        MST_Undirected();
        for(int i = 0;i<m;i++){
            if(!checkEdges[i]&&edge_w[i]>=0&&!checkCycle(i)){
                sum-=edge_w[i];
                checkEdges[i]=true;
            }
        }
    }
    bool checkCycle(int i){
        //TODO
        return true;
    }

    int extractMax(){
        int tempIndex = -1;
        int16_t tempKey = INT16_MIN;
        for(int i =0;i<n;i++){
            if(!tree[i]){
                int16_t temp = tempKey;
                tempKey = max(temp,keys[i]);
                if(temp!=tempKey)
                    tempIndex = i;  
            }
        }
        tree[tempIndex] = true;
        //cout << tempIndex << endl;
        return tempIndex;
    }

    void output(const char *outputFile){//outputfile
        ofs.open(outputFile);
        //check_io();
        ofs << sum << endl;
        printmlinear();
        ofs.flush();
        ofs.close();
    }
    void printmlinear(){
        for(int i = 0;i<m;i++){
            if(!checkEdges[i]){
                ofs << edge_u[i] << " " << edge_v[i] << " " << edge_w[i] << endl;
            }
        }
    }
    void printmn2(){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(edges[ind(i,j,n)]!=INT16_MIN){
                    ofs << i <<" "<<j<<" "<< edges[ind(i,j,n)]<<endl;
                    edges[ind(j,i,n)]=INT16_MIN;
                }   
            }
        }
    }
    void check_io(){
        ofs << graphType << endl;
        ofs << n << endl;
        ofs << m << endl;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(edges[ind(i,j,n)]<=100&&edges[ind(i,j,n)]>=-100)
                    ofs << i << " " << j << " " << edges[ind(i,j,n)] << endl;
            }
        }
    }
};


int main(int argc, char *argv[]){
    CycleBreaker breaker(argv[1]);
    breaker.output(argv[2]);
    return 0;
}
