#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <limits>
#include <queue>
#include <cmath>
using namespace std;
int table[1002][1002]={0};
bool marked[1002][1002]={false};
class Edge{
public:
    int sourceX;
    int sourceY;
    int destX;
    int destY;
    int distance;
    Edge(int sX,int sY,int dX,int dY,int d){


        this->sourceX=sX;
        this->sourceY=sY;
        this->destX=dX;
        this->destY=dY;
        this->distance=d;
    }
    struct Bigger{
        bool operator()(const Edge& distance1,const Edge& distance2){
            return distance1.distance>distance2.distance;
        }
    };
};

int LeastLeader(int sX,int sY,int dX,int dY){

    Edge src(sX,sY,sX,sY,0);
    priority_queue<Edge,vector<Edge>,Edge::Bigger>* q1 =new priority_queue<Edge,vector<Edge>,Edge::Bigger>();

    q1->push(src);
    while(!q1->empty()){
        vector<Edge> temp;

        vector<Edge>::iterator itr;

        if(table[q1->top().destX+1][q1->top().destY]!=0){
            if(!marked[q1->top().destX+1][q1->top().destY]){
                Edge right(q1->top().destX,q1->top().destY,q1->top().destX+1,q1->top().destY,max(q1->top().distance,abs(table[q1->top().destX][q1->top().destY]-table[q1->top().destX+1][q1->top().destY])));
                // cout<<q1->top().distance<<endl;
                //  cout<<abs(table[q1->top().sourceX][q1->top().sourceY]-table[q1->top().sourceX+1][q1->top().sourceY])<<endl;
                // cout<<right.distance<<endl;
                //cout<<max(q1->top().distance,abs(table[q1->top().sourceX][q1->top().sourceY]-table[q1->top().sourceX+1][q1->top().sourceY]))<<endl;
                temp.push_back(right);
            }
        }
        if(table[q1->top().destX-1][q1->top().destY]==0) {
            //  cout << "limit" << endl;
        }else{
            if(!marked[q1->top().destX-1][q1->top().destY]){
                Edge left(q1->top().destX,q1->top().destY,q1->top().destX-1,q1->top().destY,max(q1->top().distance,abs(table[q1->top().destX][q1->top().destY]-table[q1->top().destX-1][q1->top().destY])));
                temp.push_back(left);
                //cout<<left.distance<<endl;
            }
        }
        if(table[q1->top().destX][q1->top().destY+1]!=0){
            if(!marked[q1->top().destX][q1->top().destY+1]){
                Edge up(q1->top().destX,q1->top().destY,q1->top().destX,q1->top().destY+1,max(q1->top().distance,abs(table[q1->top().destX][q1->top().destY]-table[q1->top().destX][q1->top().destY+1])));
                temp.push_back(up);
                //cout<<up.distance<<endl;
            }
        }
        if(table[q1->top().destX][q1->top().destY-1]!=0){
            if(!marked[q1->top().destX][q1->top().destY-1]){
                Edge down(q1->top().destX,q1->top().destY,q1->top().destX,q1->top().destY-1,max(q1->top().distance,abs(table[q1->top().destX][q1->top().destY]-table[q1->top().destX][q1->top().destY-1])));
                temp.push_back(down);
            }
        }
        marked[q1->top().destX][q1->top().destY]=true;
        if(q1->top().destX==dX&&q1->top().destY==dY){
            return q1->top().distance;
        }

        q1->pop();
        for(itr=temp.begin();itr!=temp.end();++itr){
            Edge a=*itr;
            // cout<<a.distance<<endl;
            q1->push(a);
        }


    }

}
//
int main(int argc,char*argv[]) {
    if (argc != 3) {
        cout << "Run the code with the follwing command: ./project4 [input_file] [output_file]" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);
    int n, m;
    infile >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            infile >> x;
            table[i][j] = x;
        }
    }
    int q;
    infile >> q;
    int sX, sY, dX, dY;
    infile >> sX >> sY >> dX >> dY;



    outfile << LeastLeader(sX, sY, dX, dY);
    outfile.close();


    return 0;
}