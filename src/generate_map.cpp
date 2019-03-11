#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
	//Getting the size of the map
	int N;
	cin >> N;

	//Seeding the random
	srand(time(0));

	//Creating an output file
	ofstream fout;
	fout.open("inputmap.txt");

	//Writing the header to the file
	fout << "6\nf 3\ng 1\nG 2\nh 4\nm 7\nr 5\n";
	fout << N << " " << N;

	//Creating a char vector
	vector<char> characters;
	characters.push_back('f');
	characters.push_back('g');
	characters.push_back('G');
	characters.push_back('h');
	characters.push_back('m');
	characters.push_back('r');

	//Generating a random map
	int count = 0;
	for(int i = 0; i < N*N; i++) {
		char random = characters[rand() % characters.size()];
		if(count % N == 0) {
			fout << endl;
		}
		count++;
		fout << random << " ";
	}

	fout << endl;

	//Outputting source and destination
	fout << "0 0" << endl;
	fout << N-1 << " " << N-1 << endl;

	fout.close();
	return 0;
}

