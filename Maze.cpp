/**
 * Author: Guido Tagliavini Ponce
 *
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <utility>
#include <cstdlib>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ios_base;
using std::pair;
using std::make_pair;

vector<vector<pair<int, int> > > parent;
vector<vector<int> > rank;
vector<vector<vector<bool> > > square;
int n, m;
int di[4], dj[4];

void makeSet(int i, int j){
	parent[i][j] = make_pair(i, j);
	rank[i][j] = 0;
}

pair<int, int> find(int i, int j){
	if(parent[i][j] != make_pair(i, j)){
		parent[i][j] = find(parent[i][j].first, parent[i][j].second);
	}
	
	return parent[i][j];
}

void merge(int i1, int j1, int i2, int j2){
	pair<int, int> p1 = find(i1, j1);
	pair<int, int> p2 = find(i2, j2);
	
	i1 = p1.first;
	j1 = p1.second;
	i2 = p2.first;
	j2 = p2.second;
	
	if(rank[i1][j1] < rank[i2][j2]){
		parent[i1][j1] = make_pair(i2, j2);
	}else{
		parent[i2][j2] = make_pair(i1, j1);
		if(rank[i1][j1] == rank[i2][j2]){
			rank[i1][j1]++;
		}
	}
}

void init(){
	parent.resize(n, vector<pair<int, int> >(m));
	rank.resize(n, vector<int>(m));
	square.resize(n, vector<vector<bool> >(m, vector<bool>(4, true)));
		
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			makeSet(i, j);
		}
	}
	
	di[UP] = -1; dj[UP] = 0;
	di[RIGHT] = 0; dj[RIGHT] = 1;
	di[DOWN] = 1; dj[DOWN] = 0;
	di[LEFT] = 0; dj[LEFT] = -1;
}

int random(int a, int b){
	double u = rand() / (double) RAND_MAX;
	return (int)((b - a + 1) * u) + a;
}

int convert(int d){
	if(d == UP) return DOWN;
	if(d == RIGHT) return LEFT;
	if(d == DOWN) return UP;
	return RIGHT;
}

int main(){
	ios_base::sync_with_stdio(0);
	
	srand(time(NULL));
	cout << "n = ";
	cin >> n;
	cout << "m = ";
	cin >> m;
		
	init();
	
	/* Maze generation. */
	
	while(find(0, 0) != find(n - 1, m - 1)){
		int i = random(0, n - 1);
		int j = random(0, m - 1);
		int d = random(0, 3);
		
		if(i + di[d] >= 0 && i + di[d] < n && j + dj[d] >= 0 && j + dj[d] < m){
			if(find(i, j) != find(i + di[d], j + dj[d])){
				merge(i, j, i + di[d], j + dj[d]);
				square[i][j][d] = false;
				square[i + di[d]][j + dj[d]][convert(d)] = false;
			}
		}
	}

	/* Print the maze. */
		
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(i == 0){
				if(j == 0){
					cout << "╔═";
				}else{
					if(square[i][j][LEFT]){
						cout << "╦═";
					}else{
						cout << "══";
					}
				}
			}else{
				if(j == 0){
					if(square[i][j][UP]){
						cout << "╠═";
					}else{
						cout << "║ ";
					}
				}else{
					/* Link:    
					 *                  up
					 * (i - 1, j - 1)   ║
					 *                  ║
					 *          left ═══╬═══ right
					 *                  ║
					 *                  ║   (i, j)
					 *                 down
					 */		   
					
					bool right = square[i][j][UP];
					bool down = square[i][j][LEFT];
					bool left = square[i - 1][j - 1][DOWN];
					bool up = square[i - 1][j - 1][RIGHT];	
					
					if(right && down && up && left){
						cout << "╬═";
					}
					
					if(right && down && up && not left){
						cout << "╠═";
					}
					
					if(right && down && not up && left){
						cout << "╦═";
					}
					
					if(right && down && not up && not left){
						cout << "╔═";
					}
					
					if(right && not down && up && left){
						cout << "╩═";
					}
					
					if(right && not down && up && not left){
						cout << "╚═";
					}
										
					if(right && not down && not up && left){
						cout << "══";
					}
					
					if(right && not down && not up && not left){
						cout << " ═";
					}
					
					if(not right && down && up && left){
						cout << "╣ ";
					}
					
					if(not right && down && up && not left){
						cout << "║ ";
					}
					
					if(not right && down && not up && left){
						cout << "╗ ";
					}
					
					if(not right && down && not up && not left){
						cout << "║ ";
					}
					
					if(not right && not down && up && left){
						cout << "╝ ";
					}
					
					if(not right && not down && up && not left){
						cout << "║ ";
					}
					
					if(not right && not down && not up && left){
						cout << "  ";
					}
					
					if(not right && not down && not up && not left){
						cout << "  ";
					}
				}
			}
		}
		
		if(i == 0){
			cout << "╗";
		}else{
			if(square[i - 1][m - 1][DOWN]){
				cout << "╣";
			}else{
				cout << "║";
			}
		}
		
		cout << endl;
		
		for(int j = 0; j < m; j++){
			if(not(i == 0 && j == 0) && square[i][j][LEFT]){
				cout << "║ ";
			}else{
				cout << "  ";
			}
		}
		
		if(i < n - 1){
			cout << "║";
		}
		
		cout << endl;
	}
	
	for(int j = 0; j < m; j++){
		if(j == 0){
			cout << "╚═";
		}else{
			if(square[n - 1][j - 1][RIGHT]){
				cout << "╩═";
			}else{
				cout << "══";
			}
		}
	}
	
	cout << "╝" << endl;
	
	return 0;
}
