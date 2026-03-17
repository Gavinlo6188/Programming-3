#include "iostream"
#include "random"
#include "vector"
#include "fstream"

using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    vector<vector<char>> map(3, vector<char>(99, 1));
    ofstream outFile("output.txt");

    if (outFile.is_open()) {
        outFile << "Random numbers between 1 and 100:\n";
        int i = 0;
        int j = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 99 && i == 0; j++) {
                map[i][j] = dis(gen);
                outFile << map[i][j] << " " ;
            }
        }
    }
    outFile.close();
}