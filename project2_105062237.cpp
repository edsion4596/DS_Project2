#include <iostream>
#include "bits/stdc++.h"

bool visited[1000][1000];
char Map[1000][1000];
int Dist[1000][1000];
int visited_num = 0;

using namespace std;

void visit(vector<pair<int,int> > path){
    vector<pair<int, int> >::iterator it;
    for(it=path.begin();it!=path.end();it++){
        if(visited[it->first][it->second]!=true){
            visited[it->first][it->second] = true;
            visited_num += 1;
        }
    }
}

vector<pair<int, int> > findpath(int row, int column, int battery, int start_row, int start_column, int end_r, int end_c){
    vector<pair<int,int> > Path;
    if(Map[start_row][start_column]=='1'||Map[end_r][end_c]=='1') return Path;
    if(start_row<0||start_row==row||start_column<0||start_column==column||end_r<0||end_r==row||end_c<0||end_c==column) return Path;
    int dist[row][column];
    int i, j, k;
    for(i=0;i<row;i++){//initializing
        for(j=0;j<column;j++){
            dist[i][j] = -1;
        }
    }
    dist[start_row][start_column] = 0;
    bool dist_done = false;
    for(k=0;k<=(row*column/2)+max(row,column);k++){//setting distance from start point
        dist_done = true;
        for(i=0;i<row;i++){
            for(j=0;j<column;j++){
                if(dist[i][j]!=-1){
                    if(i!=0 && Map[i-1][j]!='1'){
                        if(dist[i-1][j]==-1||dist[i-1][j]>dist[i][j]+1)
                            dist[i-1][j] = dist[i][j] + 1;
                            dist_done = false;
                    }
                    if(i!=row-1 && Map[i+1][j]!='1'){
                        if(dist[i+1][j]==-1||dist[i+1][j]>dist[i][j]+1)
                            dist[i+1][j] = dist[i][j] + 1;
                            dist_done = false;
                    }
                    if(j!=0 && Map[i][j-1]!='1'){
                       if(dist[i][j-1]==-1||dist[i][j-1]>dist[i][j]+1)
                            dist[i][j-1] = dist[i][j] + 1;
                            dist_done = false;
                    }
                    if(j!=column-1 && Map[i][j+1]!='1'){
                        if(dist[i][j+1]==-1||dist[i][j+1]>dist[i][j]+1)
                            dist[i][j+1] = dist[i][j] + 1;
                            dist_done = false;
                    }
                }
            }
        }
        if(dist_done==true) break;
    }

    int end_row = end_r;
    int end_column = end_c;
    int B = battery-2;

    if(dist[end_row][end_column]<=B){
        Path.push_back(make_pair(end_row, end_column));
        while(B>0){
            if(end_row==start_row&&end_column==start_column) break;
            if(end_row!=row-1&&dist[end_row+1][end_column]==dist[end_row][end_column]-1){
                end_row = end_row + 1;
            }else if(end_row!=0&&dist[end_row-1][end_column]==dist[end_row][end_column]-1){
                end_row = end_row - 1;
            }else if(end_column!=column-1&&dist[end_row][end_column+1]==dist[end_row][end_column]-1){
                end_column = end_column + 1;
            }else if(end_column!=0&&dist[end_row][end_column-1]==dist[end_row][end_column]-1){
                end_column = end_column - 1;
            }
            Path.push_back(make_pair(end_row, end_column));
        }
    }
    return Path;
}

int main(int argc, char **argv)
{
    string folder;
    folder = folder + argv[1] + "/floor.data";

    ifstream fin;
    fin.open(folder);
    if(!fin.is_open()) return -1;

    int row, column, battery;
    int i, j, k;
    int start_row, start_column;
    fin>>row>>column>>battery;


    for(i=0;i<row;i++){//initializing
        for(j=0;j<column;j++){
            Dist[i][j] = -1;
            visited[i][j] = false;
        }
    }

    for(i=0;i<row;i++){//creating map
        for(j=0;j<column;j++){
            fin>>Map[i][j];
            if(Map[i][j]=='R'){
                visited[i][j] = true;
                visited_num += 1;
                start_row = i;
                start_column = j;
            }else if(Map[i][j]=='1'){
                visited[i][j] = true;
                visited_num += 1;
            }
        }
    }
    fin.close();

    Dist[start_row][start_column] = 0;
    bool dist_done = false;
    for(k=0;k<=(row*column/2)+max(row,column);k++){//setting distance from start point
        dist_done = true;
        for(i=0;i<row;i++){
            for(j=0;j<column;j++){
                if(Dist[i][j]!=-1){
                    if(i!=0 && Map[i-1][j]!='1'){
                        if(Dist[i-1][j]==-1||Dist[i-1][j]>Dist[i][j]+1)
                            Dist[i-1][j] = Dist[i][j] + 1;
                            dist_done = false;
                    }
                    if(i!=row-1 && Map[i+1][j]!='1'){
                        if(Dist[i+1][j]==-1||Dist[i+1][j]>Dist[i][j]+1)
                            Dist[i+1][j] = Dist[i][j] + 1;
                            dist_done = false;
                    }
                    if(j!=0 && Map[i][j-1]!='1'){
                        if(Dist[i][j-1]==-1||Dist[i][j-1]>Dist[i][j]+1)
                            Dist[i][j-1] = Dist[i][j] + 1;
                            dist_done = false;
                    }
                    if(j!=column-1 && Map[i][j+1]!='1'){
                        if(Dist[i][j+1]==-1||Dist[i][j+1]>Dist[i][j]+1)
                            Dist[i][j+1] = Dist[i][j] + 1;
                            dist_done = false;
                    }
                }
            }
        }
        if(dist_done==true) break;
    }

    int dist_max = 0;
    int end_row, end_column;
    vector<pair<int, int> > AnsPath;

    for(i=0;i<row;i++){//find first end point
        for(j=0;j<column;j++){
            if(Dist[i][j]>dist_max){
                dist_max = Dist[i][j];
                end_row = i;
                end_column = j;
            }
        }
    }

    if(dist_max <= battery/2 && dist_max != 0){//if no way to clean all floor and return to R, or there's no need to do anything, don't do
        vector <pair<int,int> > UtoD, UtoR, UtoL, LtoR, LtoD, RtoD;
        vector <pair<int,int> > P1,P2,P3,P4,P5,P6;
        Map[start_row][start_column] = '1';
        if(start_row!=0&&start_row!=row-1)              P1 = findpath(row,column,battery,start_row+1,start_column,start_row-1,start_column);//UtoD
        if(start_row!=0&&start_column!=0)               P2 = findpath(row,column,battery,start_row,start_column-1,start_row-1,start_column);//UtoL
        if(start_row!=0&&start_column!=column-1)        P3 = findpath(row,column,battery,start_row,start_column+1,start_row-1,start_column);//UtoR
        if(start_column!=0&&start_column!=column-1)     P4 = findpath(row,column,battery,start_row,start_column+1,start_row,start_column-1);//LtoR
        if(start_column!=0&&start_row!=row-1)           P5 = findpath(row,column,battery,start_row+1,start_column,start_row,start_column-1);//LtoD
        if(start_column!=column-1&&start_row!=row-1)    P6 = findpath(row,column,battery,start_row+1,start_column,start_row,start_column+1);//RtoD
        Map[start_row][start_column] = 'R';
        bool UD = false,UR = false,UL = false,LR = false,LD = false,RD = false;

        if((P1.size()<=P2.size()+P5.size()+1||P5.size()==0)&&(P1.size()<=P3.size()+P6.size()+1||P3.size()==0||P6.size()==0)&&P1.size()!=0){
            UtoD.insert(UtoD.end(),P1.begin(),P1.end());
        }else if((P2.size()+P5.size()+1<=P1.size()||P1.size()==0)&&(P2.size()+P5.size()<=P3.size()+P6.size()||P3.size()==0||P6.size()==0)&&P2.size()!=0&&P5.size()!=0){
            UtoD.insert(UtoD.end(),P2.begin(),P2.end());
            UtoD.push_back(make_pair(start_row,start_column));
            UtoD.insert(UtoD.end(),P5.begin(),P5.end());
        }else if((P3.size()+P6.size()+1<=P1.size()||P1.size()==0)&&(P3.size()+P6.size()<=P2.size()+P5.size()||P2.size()==0||P5.size()==0)&&P3.size()!=0&&P6.size()!=0){
            UtoD.insert(UtoD.end(),P3.begin(),P3.end());
            UtoD.push_back(make_pair(start_row,start_column));
            UtoD.insert(UtoD.end(),P6.begin(),P6.end());
        }

        if((P4.size()<=P2.size()+P3.size()+1||P2.size()==0||P3.size()==0)&&(P4.size()<=P5.size()+P6.size()+1||P5.size()==0||P6.size()==0)&&P4.size()!=0){
            LtoR.insert(LtoR.end(),P4.begin(),P4.end());
        }else if((P2.size()+P3.size()+1<=P4.size()||P4.size()==0)&&(P2.size()+P3.size()<=P5.size()+P6.size()||P5.size()==0||P6.size()==0)&&P2.size()!=0&&P3.size()!=0){
            LtoR.insert(LtoR.end(),P2.begin(),P2.end());
            reverse(LtoR.begin(),LtoR.end());
            LtoR.push_back(make_pair(start_row,start_column));
            LtoR.insert(LtoR.end(),P3.begin(),P3.end());
        }else if((P5.size()+P6.size()+1<=P4.size()||P4.size()==0)&&(P5.size()+P6.size()<=P2.size()+P3.size()||P2.size()==0||P3.size()==0)&&P5.size()!=0&&P6.size()!=0){
            LtoR.insert(LtoR.end(),P5.begin(),P5.end());
            LtoR.push_back(make_pair(start_row,start_column));
            reverse(P6.begin(),P6.end());
            LtoR.insert(LtoR.end(),P6.begin(),P6.end());
            reverse(P6.begin(),P6.end());
        }

        if(P2.size()!=0){
            UtoL.insert(UtoL.end(),P2.begin(),P2.end());
        }else if((UtoD.size()+P5.size()<=P3.size()+P4.size()||P3.size()==0||P4.size()==0)&&P5.size()!=0&&UtoD.size()!=0){
            UtoL.insert(UtoR.end(),UtoD.begin(),UtoD.end());
            UtoL.push_back(make_pair(start_row,start_column));
            reverse(P5.begin(),P5.end());
            UtoL.insert(UtoR.end(),P6.begin(),P6.end());
            reverse(P5.begin(),P5.end());
        }else if((P3.size()+P4.size()<=UtoD.size()+P6.size()||UtoD.size()==0||P6.size()==0)&&P3.size()!=0&&P4.size()!=0){
            UtoL.insert(UtoR.end(),P3.begin(),P3.end());
            UtoL.push_back(make_pair(start_row,start_column));
            reverse(LtoR.begin(),LtoR.end());
            UtoL.insert(UtoL.end(),LtoR.begin(),LtoR.end());
            reverse(LtoR.begin(),LtoR.end());
        }

        if(P3.size()!=0){
            UtoR.insert(UtoR.end(),P3.begin(),P3.end());
        }else if((UtoD.size()+P6.size()<=UtoL.size()+LtoR.size()||UtoL.size()==0||LtoR.size()==0)&&UtoD.size()!=0&&P6.size()!=0){
            UtoR.insert(UtoR.end(),UtoD.begin(),UtoD.end());
            UtoR.push_back(make_pair(start_row,start_column));
            reverse(P6.begin(),P6.end());
            UtoR.insert(UtoR.end(),P6.begin(),P6.end());
            reverse(P6.begin(),P6.end());
        }else if((UtoL.size()+LtoR.size()<=UtoD.size()+P6.size()||UtoD.size()==0||P6.size()==0)&&UtoL.size()!=0&&LtoR.size()!=0){
            UtoR.insert(UtoR.end(),UtoL.begin(),UtoL.end());
            UtoR.insert(UtoR.end(),LtoR.begin(),LtoR.end());
        }

        if(P5.size()!=0){
            LtoD.insert(LtoD.end(),P5.begin(),P5.end());
        }else if((LtoR.size()+P6.size()<=UtoL.size()+UtoD.size()||UtoL.size()==0||UtoD.size()==0)&&LtoR.size()!=0&&P6.size()!=0){
            LtoD.insert(LtoD.end(),LtoR.begin(),LtoR.end());
            LtoD.insert(LtoD.end(),P6.begin(),P6.end());
        }else if((UtoL.size()+UtoD.size()<=LtoR.size()+P6.size()||LtoR.size()==0||P6.size()==0)&&UtoL.size()!=0&&UtoD.size()!=0){
            reverse(UtoL.begin(),UtoL.end());
            LtoD.insert(LtoD.end(),UtoL.begin(),UtoL.end());
            reverse(UtoL.begin(),UtoL.end());
            LtoD.insert(LtoD.end(),UtoD.begin(),UtoD.end());
        }

        if(P6.size()!=0){
            RtoD.insert(RtoD.end(),P6.begin(),P6.end());
        }else if((LtoR.size()+LtoD.size()<=UtoR.size()+UtoD.size()||UtoR.size()==0||UtoD.size()==0)&&LtoR.size()!=0&&LtoD.size()!=0){
            reverse(LtoR.begin(),LtoR.end());
            RtoD.insert(RtoD.end(),LtoR.begin(),LtoR.end());
            reverse(LtoR.begin(),LtoR.end());
            RtoD.insert(RtoD.end(),LtoD.begin(),LtoD.end());
        }else if((UtoR.size()+UtoD.size()<=LtoR.size()+LtoD.size()||LtoR.size()==0||LtoD.size()==0)&&UtoR.size()!=0&&UtoD.size()!=0){
            reverse(UtoR.begin(),UtoR.end());
            RtoD.insert(RtoD.end(),UtoR.begin(),UtoR.end());
            reverse(UtoR.begin(),UtoR.end());
            RtoD.insert(RtoD.end(),UtoD.begin(),UtoD.end());
        }

        while(visited_num!=row*column){
            vector<pair<int, int> >::iterator it;
            vector <pair<int,int> > Path, Path2;
            int end_row2 = end_row;
            int end_column2 = end_column;
            int dist_max2 = dist_max;
            int B = battery/2;
            Path.push_back(make_pair(end_row, end_column));
            visited[end_row][end_column] = true;
            visited_num += 1;
            while(B>0){
                if(end_row==start_row&&end_column==start_column) break;//at start point
                if(B==dist_max){//need to hurry back to start point
                    if(end_row!=row-1&&Dist[end_row+1][end_column]==dist_max-1&&visited[end_row+1][end_column]!=true){
                        visited[end_row+1][end_column] = true;
                        visited_num += 1;
                        end_row = end_row + 1;
                    }else if(end_row!=0&&Dist[end_row-1][end_column]==dist_max-1&&visited[end_row-1][end_column]!=true){
                        visited[end_row-1][end_column] = true;
                        visited_num += 1;
                        end_row = end_row - 1;
                    }else if(end_column!=column-1&&Dist[end_row][end_column+1]==dist_max-1&&visited[end_row][end_column+1]!=true){
                        visited[end_row][end_column+1] = true;
                        visited_num += 1;
                        end_column = end_column + 1;
                    }else if(end_column!=0&&Dist[end_row][end_column-1]==dist_max-1&&visited[end_row][end_column-1]!=true){
                        visited[end_row][end_column-1] = true;
                        visited_num += 1;
                        end_column = end_column - 1;
                    }else if(end_row!=row-1&&Dist[end_row+1][end_column]==dist_max-1){
                        end_row = end_row + 1;
                    }else if(end_row!=0&&Dist[end_row-1][end_column]==dist_max-1){
                        end_row = end_row - 1;
                    }else if(end_column!=column-1&&Dist[end_row][end_column+1]==dist_max-1){
                        end_column = end_column + 1;
                    }else if(end_column!=0&&Dist[end_row][end_column-1]==dist_max-1){
                        end_column = end_column - 1;
                    }
                    B = B - 1;
                    dist_max = dist_max - 1;
                    Path.push_back(make_pair(end_row, end_column));
                }else{//take times to move 1.not yet visited and farther 2.not yet visited 3.closer to the start point
                    if(end_row!=row-1&&visited[end_row+1][end_column]==false&&Dist[end_row+1][end_column]<=B-1&&Dist[end_row+1][end_column]>Dist[end_row][end_column]){
                            visited[end_row+1][end_column] = true;
                            visited_num += 1;
                            end_row = end_row + 1;
                    }else if(end_row!=0&&visited[end_row-1][end_column]==false&&Dist[end_row-1][end_column]<=B-1&&Dist[end_row-1][end_column]>Dist[end_row][end_column]){
                            visited[end_row-1][end_column] = true;
                            visited_num += 1;
                            end_row = end_row - 1;
                    }else if(end_column!=column-1&&visited[end_row][end_column+1]==false&&Dist[end_row][end_column+1]<=B-1&&Dist[end_row][end_column+1]>Dist[end_row][end_column]){
                            visited[end_row][end_column+1] = true;
                            visited_num += 1;
                            end_column = end_column + 1;
                    }else if(end_column!=0&&visited[end_row][end_column-1]==false&&Dist[end_row][end_column-1]<=B-1&&Dist[end_row][end_column-1]>Dist[end_row][end_column]){
                            visited[end_row][end_column-1] = true;
                            visited_num += 1;
                            end_column = end_column - 1;
                    }else if(end_row!=row-1&&visited[end_row+1][end_column]==false&&Dist[end_row+1][end_column]<=B-1){
                            visited[end_row+1][end_column] = true;
                            visited_num += 1;
                            end_row = end_row + 1;
                    }else if(end_row!=0&&visited[end_row-1][end_column]==false&&Dist[end_row-1][end_column]<=B-1){
                            visited[end_row-1][end_column] = true;
                            visited_num += 1;
                            end_row = end_row - 1;
                    }else if(end_column!=column-1&&visited[end_row][end_column+1]==false&&Dist[end_row][end_column+1]<=B-1){
                            visited[end_row][end_column+1] = true;
                            visited_num += 1;
                            end_column = end_column + 1;
                    }else if(end_column!=0&&visited[end_row][end_column-1]==false&&Dist[end_row][end_column-1]<=B-1){
                            visited[end_row][end_column-1] = true;
                            visited_num += 1;
                            end_column = end_column - 1;
                    }else if(end_row!=row-1&&Dist[end_row+1][end_column] == Dist[end_row][end_column]-1){
                        end_row = end_row + 1;
                    }else if(end_row!=0&&Dist[end_row-1][end_column] == Dist[end_row][end_column]-1){
                        end_row = end_row - 1;
                    }else if(end_column!=column-1&&Dist[end_row][end_column+1] == Dist[end_row][end_column]-1){
                        end_column = end_column + 1;
                    }else if(end_column!=0&&Dist[end_row][end_column-1] == Dist[end_row][end_column]-1){
                        end_column = end_column - 1;
                    }
                    B = B - 1;
                    dist_max = Dist[end_row][end_column];
                    Path.push_back(make_pair(end_row, end_column));
                }
            }

            end_row = end_row2;
            end_column = end_column2;
            dist_max = dist_max2;
            B = battery/2;

            while(B>0){
                if(end_row==start_row&&end_column==start_column) break;//at start point
                if(B==dist_max){//need to hurry back to start point
                    if(end_row!=row-1&&Dist[end_row+1][end_column]==dist_max-1&&visited[end_row+1][end_column]!=true){
                        visited[end_row+1][end_column] = true;
                        visited_num += 1;
                        end_row = end_row + 1;
                    }else if(end_row!=0&&Dist[end_row-1][end_column]==dist_max-1&&visited[end_row-1][end_column]!=true){
                        visited[end_row-1][end_column] = true;
                        visited_num += 1;
                        end_row = end_row - 1;
                    }else if(end_column!=column-1&&Dist[end_row][end_column+1]==dist_max-1&&visited[end_row][end_column+1]!=true){
                        visited[end_row][end_column+1] = true;
                        visited_num += 1;
                        end_column = end_column + 1;
                    }else if(end_column!=0&&Dist[end_row][end_column-1]==dist_max-1&&visited[end_row][end_column-1]!=true){
                        visited[end_row][end_column-1] = true;
                        visited_num += 1;
                        end_column = end_column - 1;
                    }else if(end_row!=row-1&&Dist[end_row+1][end_column]==dist_max-1){
                        end_row = end_row + 1;
                    }else if(end_row!=0&&Dist[end_row-1][end_column]==dist_max-1){
                        end_row = end_row - 1;
                    }else if(end_column!=column-1&&Dist[end_row][end_column+1]==dist_max-1){
                        end_column = end_column + 1;
                    }else if(end_column!=0&&Dist[end_row][end_column-1]==dist_max-1){
                        end_column = end_column - 1;
                    }
                    B = B - 1;
                    dist_max = dist_max - 1;
                    Path2.push_back(make_pair(end_row, end_column));
                }else{//take times to move 1.not yet visited and farther 2.not yet visited 3.closer to the start point
                    if(end_row!=row-1&&visited[end_row+1][end_column]==false&&Dist[end_row+1][end_column]<=B-1&&Dist[end_row+1][end_column]>Dist[end_row][end_column]){
                            visited[end_row+1][end_column] = true;
                            visited_num += 1;
                            end_row = end_row + 1;
                    }else if(end_row!=0&&visited[end_row-1][end_column]==false&&Dist[end_row-1][end_column]<=B-1&&Dist[end_row-1][end_column]>Dist[end_row][end_column]){
                            visited[end_row-1][end_column] = true;
                            visited_num += 1;
                            end_row = end_row - 1;
                    }else if(end_column!=column-1&&visited[end_row][end_column+1]==false&&Dist[end_row][end_column+1]<=B-1&&Dist[end_row][end_column+1]>Dist[end_row][end_column]){
                            visited[end_row][end_column+1] = true;
                            visited_num += 1;
                            end_column = end_column + 1;
                    }else if(end_column!=0&&visited[end_row][end_column-1]==false&&Dist[end_row][end_column-1]<=B-1&&Dist[end_row][end_column-1]>Dist[end_row][end_column]){
                            visited[end_row][end_column-1] = true;
                            visited_num += 1;
                            end_column = end_column - 1;
                    }else if(end_row!=row-1&&visited[end_row+1][end_column]==false&&Dist[end_row+1][end_column]<=B-1){
                            visited[end_row+1][end_column] = true;
                            visited_num += 1;
                            end_row = end_row + 1;
                    }else if(end_row!=0&&visited[end_row-1][end_column]==false&&Dist[end_row-1][end_column]<=B-1){
                            visited[end_row-1][end_column] = true;
                            visited_num += 1;
                            end_row = end_row - 1;
                    }else if(end_column!=column-1&&visited[end_row][end_column+1]==false&&Dist[end_row][end_column+1]<=B-1){
                            visited[end_row][end_column+1] = true;
                            visited_num += 1;
                            end_column = end_column + 1;
                    }else if(end_column!=0&&visited[end_row][end_column-1]==false&&Dist[end_row][end_column-1]<=B-1){
                            visited[end_row][end_column-1] = true;
                            visited_num += 1;
                            end_column = end_column - 1;
                    }else if(end_row!=row-1&&Dist[end_row+1][end_column] == Dist[end_row][end_column]-1){
                        end_row = end_row + 1;
                    }else if(end_row!=0&&Dist[end_row-1][end_column] == Dist[end_row][end_column]-1){
                        end_row = end_row - 1;
                    }else if(end_column!=column-1&&Dist[end_row][end_column+1] == Dist[end_row][end_column]-1){
                        end_column = end_column + 1;
                    }else if(end_column!=0&&Dist[end_row][end_column-1] == Dist[end_row][end_column]-1){
                        end_column = end_column - 1;
                    }
                    B = B - 1;
                    dist_max = Dist[end_row][end_column];
                    Path2.push_back(make_pair(end_row, end_column));
                }
            }

            if(AnsPath.size()!=0){
                int out_row, out_column, out_row2, out_column2;
                int in_row, in_column;
                it = AnsPath.end()-2;
                in_row = it->first;
                in_column = it->second;
                it = (Path.end()-2);
                out_row = it->first;
                out_column = it->second;
                it = (Path2.end()-2);
                out_row2 = it->first;
                out_column2 = it->second;
                if(in_row==out_row&&in_column==out_column){
                    reverse(Path.begin(),Path.end());
                    for(it=Path.begin()+1;it!=Path.end();it++){
                        AnsPath.push_back(make_pair(it->first,it->second));
                    }
                    for(it=Path2.begin();it!=Path2.end();it++){
                        AnsPath.push_back(make_pair(it->first,it->second));
                    }
                }else if(in_row==out_row2&&in_column==out_column2){
                    reverse(Path2.begin(),Path2.end());
                    for(it=Path2.begin()+1;it!=Path2.end();it++){
                        AnsPath.push_back(make_pair(it->first,it->second));
                    }
                    for(it=Path.begin();it!=Path.end();it++){
                        AnsPath.push_back(make_pair(it->first,it->second));
                    }
                }else {
                    if(in_row==start_row-1){
                        if(out_row==start_row+1){
                            if(UD!=true){
                                UD = true;
                                visit(UtoD);
                            }
                            AnsPath.insert(AnsPath.end(),UtoD.begin(),UtoD.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }else if(out_column=start_column-1){
                            if(UL!=true){
                                UL=true;
                                visit(UtoL);
                            }
                            AnsPath.insert(AnsPath.end(),UtoL.begin(),UtoL.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }else if(out_column=start_column+1){
                            if(UR!=true){
                                UR=true;
                                visit(UtoR);
                            }
                            AnsPath.insert(AnsPath.end(),UtoR.begin(),UtoR.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }
                    }else if(in_column==start_column-1){
                        if(out_row==start_row-1){
                            if(UL!=true){
                                UL=true;
                                visit(UtoL);
                            }
                            reverse(UtoL.begin(),UtoL.end());
                            AnsPath.insert(AnsPath.end(),UtoL.begin(),UtoL.end());
                            reverse(UtoL.begin(),UtoL.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }else if(out_row==start_row+1){
                            if(LD!=true){
                                LD=true;
                                visit(LtoD);
                            }
                            AnsPath.insert(AnsPath.end(),LtoD.begin(),LtoD.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }else if(out_column==start_column+1){
                            if(LR!=true){
                                LR=true;
                                visit(LtoR);
                            }
                            AnsPath.insert(AnsPath.end(),LtoR.begin(),LtoR.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }
                    }else if(in_column==start_column+1){
                        if(out_row==start_row-1){
                            if(UR!=true){
                                UR=true;
                                visit(UtoR);
                            }
                            reverse(UtoR.begin(),UtoR.end());
                            AnsPath.insert(AnsPath.end(),UtoR.begin(),UtoR.end());
                            reverse(UtoR.begin(),UtoR.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }else if(out_row==start_row+1){
                            if(UD!=true){
                                UD=true;
                                visit(UtoD);
                            }
                            AnsPath.insert(AnsPath.end(),RtoD.begin(),RtoD.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }else if(out_column==start_column-1){
                            if(LR!=true){
                                LR=true;
                                visit(LtoR);
                            }
                            reverse(LtoR.begin(),LtoR.end());
                            AnsPath.insert(AnsPath.end(),LtoR.begin(),LtoR.end());
                            reverse(LtoR.begin(),LtoR.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }
                    }else if(in_row==start_row+1){
                        if(out_row==start_row-1){
                            if(UD!=true){
                                UD=true;
                                visit(UtoD);
                            }
                            reverse(UtoD.begin(),UtoD.end());
                            AnsPath.insert(AnsPath.end(),UtoD.begin(),UtoD.end());
                            reverse(UtoD.begin(),UtoD.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }else if(out_column==start_column-1){
                            if(LD!=true){
                                LD=true;
                                visit(LtoD);
                            }
                            reverse(LtoD.begin(),LtoD.end());
                            AnsPath.insert(AnsPath.end(),LtoD.begin(),LtoD.end());
                            reverse(LtoD.begin(),LtoD.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }else if(out_column==start_column+1){
                            if(RD!=true){
                                RD=true;
                                visit(RtoD);
                            }
                            reverse(RtoD.begin(),RtoD.end());
                            AnsPath.insert(AnsPath.end(),RtoD.begin(),RtoD.end());
                            reverse(RtoD.begin(),RtoD.end());
                            AnsPath.push_back(make_pair(start_row,start_column));
                            reverse(Path.begin(),Path.end());
                            for(it=Path.begin()+1;it!=Path.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                            for(it=Path2.begin();it!=Path2.end();it++){
                                AnsPath.push_back(make_pair(it->first,it->second));
                            }
                        }
                    }
                }

            }else{
                reverse(Path.begin(),Path.end());
                for(it=Path.begin()+1;it!=Path.end();it++){
                    AnsPath.push_back(make_pair(it->first,it->second));
                }
                for(it=Path2.begin();it!=Path2.end();it++){
                    AnsPath.push_back(make_pair(it->first,it->second));
                }
            }


            dist_max = 0;
            for(i=0;i<row;i++){
                for(j=0;j<column;j++){
                    if(visited[i][j]==false&&Dist[i][j]>dist_max){
                        dist_max = Dist[i][j];
                        end_row = i;
                        end_column = j;
                    }
                }
            }
        }

        string output;
        output = output + argv[1] + "/final.path";
        ofstream fout(output);

        vector<pair<int, int> >::iterator it;
        fout<<AnsPath.size()<<endl;
        for(it=AnsPath.begin();it!=AnsPath.end();it++){
            fout<<it->first<<' '<<it->second<<endl;
        }
        fout<<"UtoR!!!"<<endl;
        for(it=UtoR.begin();it!=UtoR.end();it++){
            fout<<it->first<<' '<<it->second<<endl;
        }
        fout<<"UtoL!!!"<<endl;
        for(it=UtoL.begin();it!=UtoL.end();it++){
            fout<<it->first<<' '<<it->second<<endl;
        }
        fout<<"UtoD!!!"<<endl;
        for(it=UtoD.begin();it!=UtoD.end();it++){
            fout<<it->first<<' '<<it->second<<endl;
        }
        fout<<"LtoR!!!"<<endl;
        for(it=LtoR.begin();it!=LtoR.end();it++){
            fout<<it->first<<' '<<it->second<<endl;
        }
        fout<<"LtoD!!!"<<endl;
        for(it=LtoD.begin();it!=LtoD.end();it++){
            fout<<it->first<<' '<<it->second<<endl;
        }
        fout<<"RtoD!!!"<<endl;
        for(it=RtoD.begin();it!=RtoD.end();it++){
            fout<<it->first<<' '<<it->second<<endl;
        }
        fout.close();
    }else{
        string output;
        output = output + argv[1] + "/final.path";
        ofstream fout(output);
        fout<<"No way to clean all or no need to move."<<endl;
        fout.close();
    }
}
