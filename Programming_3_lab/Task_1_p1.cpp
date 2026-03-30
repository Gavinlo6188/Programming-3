#include <iostream>
#include <vector>
using namespace std;
int main() {
    // Crate a 10x10 2D vector to represent the game board, with '.' as empty spaces
    vector<vector<char>> map(10, vector<char>(10, '.'));
    for (int i = 0; i < 10; i++) {
        map[i][0] = '*';
        map[i][9] = '*';
    }
    char cmd;

    for (int j = 0; j < 10; j++) {
        map[0][j] = '*';
        map[9][j] = '*';
    }
    int i_1 = 1;
    int j_1 = 1;
    map[i_1][j_1] = '@';
    int j_2;
    int i_2;

    while (true) {
        // Create the map
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cout << map[i][j] << " ";
            }
        cout << "\n";
        }

        cout << endl;
        cout << "Enter WASD to move '@' (or - to exit): ";
        cin >> cmd; // Get user input
        // Exit function
        if(cmd == '-') {
            exit(0);
        }
        // WASD movement controls
        if ((cmd == 'w' || cmd == 'W') && (i_1 > 1)) {
            map[i_1][j_1] = '.'; // replace the old position with '.'
            i_1--;
            map[i_1][j_1] = '@'; // new position
        } else if ((cmd == 's' || cmd == 'S') && (i_1 < 8)) {
            map[i_1][j_1] = '.';
            i_1++;
            map[i_1][j_1] = '@';
        } else if ((cmd == 'a' || cmd == 'A') && (j_1 > 1)) {
            map[i_1][j_1] = '.';
            j_1--;
            map[i_1][j_1] = '@';
        } else if ((cmd == 'd' || cmd == 'D') && (j_1 < 8)) {
            map[i_1][j_1] = '.';
            j_1++;
            map[i_1][j_1] = '@';
        }else if ((cmd == 'w' || cmd == 'W' || cmd == 'a' || cmd == 'A' || cmd == 's' || cmd == 'S' || cmd == 'd' || cmd == 'D') && (i_1 <= 1 || i_1 >= 8 || j_1 <= 1 || j_1 >= 8)) {
            cout << "khiem ur bad" << endl; // player touches the wall, do not move
        }


        cout << "\n" << i_1 << "\n" << j_1 << endl;

    }

    return 0;
}