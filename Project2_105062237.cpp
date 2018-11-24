#include <iostream>
#include "bits/stdc++.h"

using namespace std;

int main()
{
    int row, column, battery;
    int i, j, k;
    int start_row, start_column;
    cin>>row>>column>>battery;
    bool visited[row][column];
    int visited_num = 0;
    char Map[row][column];
    int Dist[row][column];

    for(i=0;i<row;i++){//initializing
        for(j=0;j<column;j++){
            Dist[i][j] = -1;
            visited[i][j] = false;
        }
    }




    for(i=0;i<row;i++){//creating map
        for(j=0;j<column;j++){
            cin>>Map[i][j];
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

    Dist[start_row][start_column] = 0;
    bool dist_done = false;
    for(k=0;k<=(row*column/2)+max(row,column);k++){
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

    for(i=0;i<row;i++){
        for(j=0;j<row;j++){
            cout<<Dist[i][j]<<' ';
        }
        cout<<endl;
    }

    int dist_max = 0;
    int end_row, end_column;
    vector<pair<int, int> > AnsPath;
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            if(Dist[i][j]>dist_max){
                dist_max = Dist[i][j];
                end_row = i;
                end_column = j;
            }
        }
    }

    if(dist_max <= battery/2 && dist_max != 0){//if no way to clean all floor and return to R, or there's no need to do anything, don't do it.
        while(visited_num!=row*column){
            vector <pair<int,int> > Path;
            int B = battery/2;
            Path.push_back(make_pair(end_row, end_column));
            visited[end_row][end_column] = true;
            visited_num += 1;
            while(B>0){
                if(end_row==start_row&&end_column==start_column) break;
                if(B==dist_max){
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
                }else{
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
                    }else if(end_column-1&&visited[end_row][end_column+1]==false&&Dist[end_row][end_column+1]<=B-1){
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

            vector<pair<int, int> >::iterator it;
            for(it=Path.end()-1;it!=Path.begin();){
                --it;
                AnsPath.push_back(make_pair(it->first,it->second));
            }
            for(it=Path.begin()+1;it!=Path.end();it++){
                AnsPath.push_back(make_pair(it->first,it->second));
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
        vector<pair<int, int> >::iterator it;
        cout<<AnsPath.size()<<endl;
        for(it=AnsPath.begin();it!=AnsPath.end();it++){
            cout<<it->first<<' '<<it->second<<endl;
        }
    }else{
        cout<<"no way to clean all floor";
    }
}
