#include "iostream"
#include "random"
#include "vector"
#include "fstream"

using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    vector<vector<char>> map(3, vector<char>(100, 1));
    ofstream outFile("output.txt");
    if (outFile.is_open()) {
        outFile << "Random numbers between 1 and 100:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 100; j++) {
                outFile << dis(gen) << " ";
            }
            outFile << "\n";
        }
    }
    outFile.close();

}