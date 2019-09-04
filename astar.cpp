#include<bits/stdc++.h>
using namespace std;

#define ROW 9000
#define COL 6000

typedef pair<int, int> pii;
typedef pair<double, pair<int, int>> pdp;

struct cell { 
	int parent_i, parent_j;
	double f, g, h; 
}; 

bool isValid(int row, int col){
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnblocked(bool grid[][COL], int row, int col){
    return grid[row][col];
}

bool isDestination(int row, int col, pii dest){
    return (row == dest.first && col == dest.second);
}

double calculateHValue(int row, int col, pii dest){
    return ((double) sqrt(pow((row - dest.first), 2) + pow((col - dest.second), 2)));
}

void tracePath(cell cellDetails[][COL], pii dest){
    printf("Caminho a ser seguido: ");
    int row = dest.first;
    int col = dest.second;

    stack<pii> path;

    while (!(cellDetails[row][col].parent_i == row 
			&& cellDetails[row][col].parent_j == col )) 
	{ 
		path.push (make_pair (row, col)); 
		int temp_row = cellDetails[row][col].parent_i; 
        int temp_col = cellDetails[row][col].parent_j; 
        row = temp_row; 
		col = temp_col; 
	} 

    path.push(make_pair(row, col));

    while(!path.empty()){
        pii p = path.top();
        path.pop();
        printf("-> (%d, %d)", p.first, p.second);
    }
    
}

bool closedList[ROW][COL];
cell cellDetails[ROW][COL];

void aStarSearch(bool grid[][COL], pii src, pii dest){
    if(!isValid(src.first, src.second)) return;
    if(!isValid(dest.first, dest.second)) return;
    if(!isUnblocked(grid, src.first, src.second)) return;
    if(!isUnblocked(grid, dest.first, dest.second)) return;
    if(isDestination(src.first, src.second, dest)) return;

    memset(closedList, false, sizeof(closedList));

    int i, j;

    // tem como otimizar isso aqui fazendo uma classe com um construtor
    // pre definindo esses valores! já tira um for gigante
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second; 
	cellDetails[i][j].f = 0.0; 
	cellDetails[i][j].g = 0.0; 
	cellDetails[i][j].h = 0.0; 
	cellDetails[i][j].parent_i = i; 
	cellDetails[i][j].parent_j = j; 


    set<pdp> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));
    bool foundDest = false;

    while(!openList.empty()){
        pdp p = *openList.begin();
        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;
        if(isValid(i-1, j)){
            if(isDestination(i-1, j, dest)){
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                printf("Caminho encontrado: \n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return ;
            }else if(closedList[i-1][j] == false && isUnblocked(grid, i-1, j) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i-1, j, dest);
                fNew = gNew + hNew;

                if(cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i-1, j)));

                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }

        if(isValid(i+1, j)){
            if(isDestination(i+1, j, dest)){
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                printf("Caminho encontrado: \n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return ;
            }else if(closedList[i+1][j] == false && isUnblocked(grid, i+1, j) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                if(cellDetails[i+1][j].f == FLT_MAX || cellDetails[i+1][j].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i+1, j)));

                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }

        if(isValid(i, j+1)){
            if(isDestination(i, j+1, dest)){
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                printf("Caminho encontrado: \n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return ;
            }else if(closedList[i][j+1] == false && isUnblocked(grid, i, j+1) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j+1, dest);
                fNew = gNew + hNew;

                if(cellDetails[i][j+1].f == FLT_MAX || cellDetails[i][j+1].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i, j+1)));

                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }

        if(isValid(i, j-1)){
            if(isDestination(i, j-1, dest)){
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                printf("Caminho encontrado: \n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return ;
            }else if(closedList[i][j-1] == false && isUnblocked(grid, i, j-1) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;

                if(cellDetails[i][j-1].f == FLT_MAX || cellDetails[i][j-1].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i, j-1)));

                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }

        if(isValid(i-1, j+1)){
            if(isDestination(i-1, j+1, dest)){
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;
                printf("Caminho encontrado: \n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return ;
            }else if(closedList[i-1][j+1] == false && isUnblocked(grid, i-1, j+1) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i-1, j+1, dest);
                fNew = gNew + hNew;

                if(cellDetails[i-1][j+1].f == FLT_MAX || cellDetails[i-1][j+1].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i-1, j+1)));

                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                }
            }
        }

        if(isValid(i-1, j-1)){
            if(isDestination(i-1, j-1, dest)){
                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;
                printf("Caminho encontrado: \n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return ;
            }else if(closedList[i-1][j-1] == false && isUnblocked(grid, i-1, j-1) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i-1, j-1, dest);
                fNew = gNew + hNew;

                if(cellDetails[i-1][j-1].f == FLT_MAX || cellDetails[i-1][j-1].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i-1, j-1)));

                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                }
            }
        }

        if(isValid(i+1, j+1)){
            if(isDestination(i+1, j+1, dest)){
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                printf("Caminho encontrado: \n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return ;
            }else if(closedList[i+1][j+1] == false && isUnblocked(grid, i+1, j+1) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j+1, dest);
                fNew = gNew + hNew;

                if(cellDetails[i+1][j+1].f == FLT_MAX || cellDetails[i+1][j+1].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i+1, j+1)));

                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                }
            }
        }

        if(isValid(i+1, j-1)){
            if(isDestination(i+1, j-1, dest)){
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                printf("Caminho encontrado: \n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return ;
            }else if(closedList[i+1][j-1] == false && isUnblocked(grid, i+1, j-1) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j-1, dest);
                fNew = gNew + hNew;

                if(cellDetails[i+1][j-1].f == FLT_MAX || cellDetails[i+1][j-1].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i+1, j-1)));

                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                }
            }
        }
    }
    if(!foundDest) printf("Failed to find the Destination Cell\n");

    return;
}

bool grid[ROW][COL];

int main(){
    for(int x = 0; x < ROW; x++){
        for(int y = 0; y < COL; y++){
            grid[x][y] = true;
        }
    }

    pii src = make_pair(0, 0);
    pii dest = make_pair(8999, 5999);
    aStarSearch(grid, src, dest);
}
