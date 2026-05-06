#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cmath>
using namespace std;

struct Pos {
    int row, col;
    Pos(int r, int c) : row(r), col(c) {}
    bool operator<(const Pos& other) const {
        if (row != other.row) return row < other.row;
        return col < other.col;
    }
    bool operator==(const Pos& other) const {
        return row == other.row && col == other.col;
    }
};

vector<Pos> tracePath(const vector<string>& grid, int n, int m, char target) {
    Pos start(-1,-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]==target && (i==0||i==n-1||j==0||j==m-1)){
                start=Pos(i,j);
                break;
            }
        }
        if(start.row!=-1) break;
    }

    if(start.row==-1) return vector<Pos>();

    vector<Pos> path;
    set<pair<int,int>> visited;
    path.push_back(start);
    visited.insert({start.row,start.col});

    Pos current=start;
    int dr[]={0,1,0,-1};
    int dc[]={1,0,-1,0};

    while(true){
        bool found=false;
        for(int d=0;d<4;d++){
            int ni=current.row+dr[d];
            int nj=current.col+dc[d];
            if(ni>=0 && ni<n && nj>=0 && nj<m &&
               visited.find({ni,nj})==visited.end() &&
               grid[ni][nj]==target){
                Pos next(ni,nj);
                path.push_back(next);
                visited.insert({ni,nj});
                current=next;
                found=true;
                break;
            }
        }
        if(!found) break;
    }
    return path;
}

int findInPath(const vector<Pos>& path,const Pos& pos){
    for(int i=0;i<path.size();i++)
        if(path[i]==pos) return i;
    return -1;
}

int solveCableWrap(int n,int m,vector<string>& grid){
    vector<Pos> cablePath=tracePath(grid,n,m,'C');
    vector<Pos> rodPath=tracePath(grid,n,m,'R');

    if(cablePath.empty() || rodPath.empty()) return 0;

    set<pair<int,int>> rodSet;
    for(const Pos& p:rodPath) rodSet.insert({p.row,p.col});

    int linkingNumber=0;
    for(int i=0;i<cablePath.size()-1;i++){
        Pos curr=cablePath[i];
        Pos nextPos=cablePath[i+1];

        if(rodSet.find({curr.row,curr.col})!=rodSet.end()){
            int rodIdx=findInPath(rodPath,curr);
            if(rodIdx==-1) continue;

            int rodDirR, rodDirC;
            if(rodIdx>0 && rodIdx<rodPath.size()-1){
                Pos rodPrev=rodPath[rodIdx-1];
                Pos rodNext=rodPath[rodIdx+1];
                rodDirR=rodNext.row-rodPrev.row;
                rodDirC=rodNext.col-rodPrev.col;
            } else if(rodIdx==0){
                Pos rodNext=rodPath[rodIdx+1];
                rodDirR=rodNext.row-curr.row;
                rodDirC=rodNext.col-curr.col;
            } else {
                Pos rodPrev=rodPath[rodIdx-1];
                rodDirR=curr.row-rodPrev.row;
                rodDirC=curr.col-rodPrev.col;
            }

            int cableDirR=nextPos.row-curr.row;
            int cableDirC=nextPos.col-curr.col;

            int crossProduct=cableDirR*rodDirC-cableDirC*rodDirR;
            if(crossProduct!=0){
                char onTop=grid[curr.row][curr.col];
                linkingNumber+=(onTop=='R')?((crossProduct>0)?1:-1):((crossProduct>0)?-1:1);
            }
        }
    }

    return abs(linkingNumber);
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<string> grid(n);
    for(int i=0;i<n;i++) cin>>grid[i];

    int result=solveCableWrap(n,m,grid);
    cout<<result<<endl;
    return 0;
}
