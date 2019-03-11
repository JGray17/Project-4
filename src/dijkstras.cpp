// dijsktras.cpp

// Main Execution
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;

class Node{

public:
	int position;
	int distance;
	char terrain;
	Node *backEdge;
	bool visited;

	Node(char, int);
};

void dijkstras(int, int, int, int, vector<Node*> &, multimap<char, int> &);

int main(int argc, char *argv[]) {

	int numTypes, weight, row, col, src, dst, src_r, src_c, dst_r, dst_c;
	int tmp_pos;
	char type;
	multimap<char, int> edges;
	vector<Node*> map;
	vector<int> path;
	Node *square;

	cin >> numTypes;

	//fill out list of edge weights
	for(int i=0; i<numTypes; i++){
		cin >> type >> weight;
		edges.insert(make_pair(type, weight));
	}

	cin >> row >> col;

	//fill out map
	for(int i=0; i<row*col; i++){
		cin >> type;

		square = new Node(type, i);
		map.push_back(square);
	}

	cin >> src_r >> src_c >> dst_r >> dst_c;

	src = (src_r*col)+src_c;
	dst = (dst_r*col)+dst_c;

	dijkstras(src, dst, row, col, map, edges);

	tmp_pos = dst;
	path.push_back(tmp_pos);

	while(tmp_pos != src){

		path.push_back(map[tmp_pos]->backEdge->position);
		tmp_pos = map[tmp_pos]->backEdge->position;
	}

	cout << map[dst]->distance << endl;

	for(int i=path.size()-1; i>=0; i--){
		cout << path[i]/col << " " << path[i]%col << endl;
	}

	for(unsigned int i=0; i<map.size(); i++){
		delete map[i];
	}


	return 0;
}

Node::Node(char type, int num){

	position = num;
	terrain = type;
	distance = -1;
	backEdge = NULL;
	visited = false;

}

void dijkstras(int src, int dst, int row, int col, vector<Node*> &map, multimap<char, int> &edges){

	multimap<int, int> list;
	multimap<int, int>::iterator cur, mit;

	int tmp_pos, d, e;

	map[src]->distance = 0;

	list.insert(make_pair(map[src]->distance, src));

	while(!list.empty()){

		cur = list.begin();

		tmp_pos = cur->second;

		map[tmp_pos]->visited = true;

		list.erase(cur);


		//check up
		if(tmp_pos/col != 0 && map[tmp_pos-col]->visited == false){

			e = edges.find(map[tmp_pos]->terrain)->second;
			d = map[tmp_pos]->distance + e;

			if(map[tmp_pos-col]->distance == -1 || d < map[tmp_pos-col]->distance){

				for(mit = list.begin(); mit != list.end(); mit++){
					if(mit->second == tmp_pos-col){
						list.erase(mit);
					}
				}

				map[tmp_pos-col]->distance = d;
				map[tmp_pos-col]->backEdge = map[tmp_pos];
				list.insert(make_pair(map[tmp_pos-col]->distance, tmp_pos-col));
			}
		}


		//check right
		if(tmp_pos%col != col-1 && map[tmp_pos+1]->visited == false){

			e = edges.find(map[tmp_pos]->terrain)->second;
			d = map[tmp_pos]->distance + e;

			if(map[tmp_pos+1]->distance == -1 || d < map[tmp_pos+1]->distance){

				for(mit = list.begin(); mit != list.end(); mit++){
					if(mit->second == tmp_pos+1){
						list.erase(mit);
					}
				}

				map[tmp_pos+1]->distance = d;
				map[tmp_pos+1]->backEdge = map[tmp_pos];
				list.insert(make_pair(map[tmp_pos+1]->distance, tmp_pos+1));
			}
		}

		//check down
		if(tmp_pos/col != row-1 && map[tmp_pos+col]->visited == false){

			e = edges.find(map[tmp_pos]->terrain)->second;
			d = map[tmp_pos]->distance + e;

			if(map[tmp_pos+col]->distance == -1 || d < map[tmp_pos+col]->distance){

				for(mit = list.begin(); mit != list.end(); mit++){
					if(mit->second == tmp_pos+col){
						list.erase(mit);
					}
				}

				map[tmp_pos+col]->distance = d;
				map[tmp_pos+col]->backEdge = map[tmp_pos];
				list.insert(make_pair(map[tmp_pos+col]->distance, tmp_pos+col));
			}
		}

		//check left
		if(tmp_pos%col != 0 && map[tmp_pos-1]->visited == false){

			e = edges.find(map[tmp_pos]->terrain)->second;
			d = map[tmp_pos]->distance + e;

			if(map[tmp_pos-1]->distance == -1 || d < map[tmp_pos-1]->distance){

				for(mit = list.begin(); mit != list.end(); mit++){
					if(mit->second == tmp_pos-1){
						list.erase(mit);
					}
				}

				map[tmp_pos-1]->distance = d;
				map[tmp_pos-1]->backEdge = map[tmp_pos];
				list.insert(make_pair(map[tmp_pos-1]->distance, tmp_pos-1));
			}
		}


	}
}
