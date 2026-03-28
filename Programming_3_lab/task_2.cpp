#include "iostream"
#include "random"
#include "vector"
#include "fstream"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::ofstream outFile("output.txt");
    
    using namespace std;
    uniform_real_distribution<> dis(0.95, 1.05);
    vector<vector<float>> map(3, vector<float>(99, 1));
    

    if (outFile.is_open()) {
        outFile << "Random numbers between n(0.95 and 1.05):\n";
        int i = 0;
        int j = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 99 && i == 0; j++) {
                map[i][j] = 2 * (j + 1) * dis(gen);
                map[i+1][j] = (j + 1) * dis(gen);
                outFile << map[i][j] << " " ;
                outFile << map[i+1][j] << "\n";
            }
        }
    }
    

    cout<<"hello"<<endl;
    outFile.close();
}