/*
W pierszym wierszu wejścia znajdują się dwie liczby całkowite n i t, 
oznaczające kolejno długość napisów oraz liczbę przypadków testowych w 
zadaniu. W kolejnych wierszach opisane są przypadki testowe.

Każdy przypadek testowy składa się z dwóch wierszy, każdy wiersz 
zawiera napis długości n składający się ze znaków '0' i '1'. Pierwszy
z nich zostaje wysłany do Algosi, a drugi do Bajtazara.

*/
#include <bits/stdc++.h>
#include "oi.h"

using namespace std;

const int NUM_PROCESSES = 2;
const int MAX_N = 5'000;
const int MAX_T = 5;
const int MAX_K = 20'000;

const int limits[10] = {20000, 16250, 10000, 8750, 6250, 5500, 5250, 5125, 5050, 5000};

void wa(string msg) {
	cout << "WRONG\n" << msg << "\n0\n";
	exit(0);
}
void ok(string msg, int score) {
	cout << "OK\n" << msg << "\n" << score << "\n";
	exit(0);
}

void interactor(vector<FILE*> &from_user_list, vector<FILE*> &to_user_list) {
	oi::Scanner tin(stdin);
	FILE* from_user_a = from_user_list[0];
	FILE* from_user_b = from_user_list[1];    
	FILE* to_user_a = to_user_list[0];
	FILE* to_user_b = to_user_list[1];

	fprintf(to_user_a, "Algosia\n");
	fflush(to_user_a);

	fprintf(to_user_b, "Bajtek\n");
	fflush(to_user_b);


	int n = tin.readInt(1, MAX_N);
	tin.readSpace();
	int t = tin.readInt(1, MAX_T);
	tin.readEoln();

	fprintf(to_user_a, "%d %d\n", n, t);
	fflush(to_user_a);

	fprintf(to_user_b, "%d %d\n", n, t);
	fflush(to_user_b);

	char SA[MAX_N], SB[MAX_N];
	char GSA[MAX_N], GSB[MAX_N];

	int max_passes = 0;

	while(t--) {

		for(int i = 0; i < n; ++i) {
			SA[i] = tin.readChar();
			if(SA[i] != '0' && SA[i] != '1') wa("Format wejscia nie zgadza sie z zalozeniami zadania.");
		}
		tin.readEoln();
		for(int i = 0; i < n; ++i) {
			SB[i] = tin.readChar();
			if(SB[i] != '0' && SB[i] != '1') wa("Format wejscia nie zgadza sie z zalozeniami zadania.");
		}
		tin.readEoln();

		fwrite(SA, 1, n, to_user_a);
		fprintf(to_user_a, "\n");
		fflush(to_user_a);

		fwrite(SB, 1, n, to_user_b);
		fprintf(to_user_b, "\n");
		fflush(to_user_b);

		int cur_passes = 0, cur_score = 0;
		while(true) {
			char cA, cB;
			if(fscanf(from_user_a, " %c", &cA) != 1) wa("Blad wczytywania od procesu Algosi.");
			if(fscanf(from_user_b, " %c", &cB) != 1) wa("Blad wczytywania od procesu Bajtka.");
		
			if(cA == '!' || cB == '!') {
				if(cA != cB) wa("Algosia i Bajtek probuja wykonac rozne operacje.");

				if(fscanf(from_user_a, " %c", &GSA[0]) != 1) wa("Blad wczytywania od procesu Algosi.");
				for(int i = 1; i < n; ++i) {
					if(fscanf(from_user_a, "%c", &GSA[i]) != 1) wa("Blad wczytywania od procesu Algosi.");
				}

				if(fscanf(from_user_b, " %c", &GSB[0]) != 1) wa("Blad wczytywania od procesu Bajtka.");
				for(int i = 1; i < n; ++i) {
					if(fscanf(from_user_b, "%c", &GSB[i]) != 1) wa("Blad wczytywania od procesu Bajtka.");
				}

				for(int i = 0; i < n; ++i) {
					if(GSA[i] != SB[i]) wa("Napis wypisany przez Algosie nie jest rowny napisowi Bajtka.");
					if(GSA[i] != SB[i]) wa("Napis wypisany przez Bajtka nie jest rowny napisowi Algosie.");
				}

				max_passes = max(max_passes, cur_passes);
				break;

			} else {
				++cur_passes;
				if(cur_passes > MAX_K) wa("Przekroczono limit odbytych rund.");

				string game = "PKN";
				int idA=-1, idB=-1;
				for(int i = 0; i < 3; ++i) {
					if(cA == game[i]) idA=i;
					if(cB == game[i]) idB=i;
				}

				if(idA == -1) wa("Znak Algosi nie odpowiada zadnemu z poprawnych gestow.");
				if(idB == -1) wa("Znak Bajtka nie odpowiada zadnemu z poprawnych gestow.");
				
				fprintf(to_user_a, "%c\n", cB);
				fflush(to_user_a);
				fprintf(to_user_b, "%c\n", cA);
				fflush(to_user_b);

				if((idA + 1) % 3 == idB) ++cur_score;

				if((idB + 1) % 3 == idA) --cur_score;

				if(abs(cur_score) > 1) wa("Algosia i Bajtek przegrali gre.");

			}
		}
	}

	// sprawdzamy, czy procesy sie zakonczyly
	char c;
	if(fscanf(from_user_a, " %c", &c) != EOF) wa("proces Algosi sie nie zakonczyl, lub wypisal smieci na koncu pliku");
	if(fscanf(from_user_b, " %c", &c) != EOF) wa("proces Bajtka sie nie zakonczyl, lub wypisal smieci na koncu pliku");
	
	// sprawdzamy czy poprawnie wczytalismy caly input
	tin.readEof();

	int score = 0;
	for(int i = 0; i < 10; ++i) {
		if(max_passes <= limits[i]) score += 10;
	}
	ok("OK, max_passes: " + to_string(max_passes), score);
}

int main(int argc, char *argv[]) {
	assert(argc > 2);
    assert(atoi(argv[1]) == NUM_PROCESSES);
	assert(argc == 2 + NUM_PROCESSES * 2);
	vector<FILE*> in_list(NUM_PROCESSES);
	vector<FILE*> out_list(NUM_PROCESSES);
	for (int i=0; i<NUM_PROCESSES; ++i) {
        FILE *file = fdopen(atoi(argv[2 + i*2]), "r");
		assert(file);
        in_list[i] = file;
		FILE *file2 = fdopen(atoi(argv[3 + i*2]), "w");
		assert(file2);
        out_list[i] = file2;
	}
	interactor(in_list, out_list);
	return 0;
}
