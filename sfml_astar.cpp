#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define ROW 900
#define COL 600

// g++ -c tester.cpp
// g++ tester.o -o test -lsfml-graphics -lsfml-window -lsfml-system

typedef pair<int, int> pii;
typedef pair<double, pair<int, int>> pdp;

bool mat[ROW][COL];
vector<pii> vec;

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
        vec.push_back(make_pair(p.first, p.second));
    }
    
}

bool closedList[ROW][COL];
cell cellDetails[ROW][COL];

int aStarSearch(bool grid[][COL], pii src, pii dest){
    if(!isValid(src.first, src.second)) return 0;
    if(!isValid(dest.first, dest.second)) return 0;
    if(!isUnblocked(grid, src.first, src.second)) return 0;
    if(!isUnblocked(grid, dest.first, dest.second)) return 0;
    if(isDestination(src.first, src.second, dest)) return 0;

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
                return 1;
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
                return 1;
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
                return 1;
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
                return 1;
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
                return 1;
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
                return 1;
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
                return 1;
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
                return 1;
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

    return 0;
}

void zoomViewAt(Vector2i pixel, RenderWindow& window, float zoom){
	const Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	View view{ window.getView() };
	view.zoom(zoom);
	window.setView(view);
	const Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
	window.setView(view);
}

int main(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    const float zoomAmount{ 1.1f };

    for(int x = 0; x < ROW; x++){
        for(int y = 0; y < COL; y++){
            mat[x][y] = rng() % 2;
        }
    }

    int a = rng()%ROW;
    int b = rng()%COL;
    pii src = make_pair(a, b);
    cout << "I've started search in: " << a << " " << b << endl;
    pii dest = make_pair(ROW-1, COL-1);

    while(!aStarSearch(mat, src, dest)){
        a = rng()%ROW;
        b = rng()%COL;
        src = make_pair(a, b);
        int c = rng()%ROW;
        int d = rng()%COL;
        dest = make_pair(c, d);
        cout << "Failed! Trying with: " << a << " " << b << " trying to reach " << c << " " << d << endl;
        aStarSearch(mat, src, dest);
    }

    RenderWindow window(VideoMode(ROW, COL), "A* Tester");
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
            if (event.type == Event::MouseWheelScrolled){
                if (event.mouseWheelScroll.delta > 0)
                    zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / zoomAmount));
                else if (event.mouseWheelScroll.delta < 0)
                    zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, zoomAmount);
            }
        }
        window.clear();
        int sz = vec.size();
        for(int x = 0; x < sz - 1; x++){
            Vertex line[] =
            {
                Vertex(Vector2f((float) vec[x].first, (float) vec[x].second)),
                Vertex(Vector2f((float) vec[x+1].first, (float) vec[x+1].second)),
            };
            line[0].color = Color::Red;
            line[1].color = Color::Red;
            window.draw(line, 2, Lines);
        }

        for(int x = 0; x < ROW; x++){
            for(int y = 0; y < COL; y++){
                if(mat[x][y]){
                    Vertex dot[] =
                    {
                        Vertex(Vector2f((float) x, (float) y))
                    };
                    window.draw(dot, 1, Points);
                }
            }
        }

        window.display();
    }
}
