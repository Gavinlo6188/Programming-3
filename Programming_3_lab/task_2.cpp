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
    
    float i_last = 0.0;
    float j_last = 0.0;
    float i_now = 0.0;
    float j_now = 0.0;
    float i_change_sum = 0.0;
    float j_change_sum = 0.0;

    // y = mx + c
    float m = 2.0;
    float c = 0.0;

    if (outFile.is_open()) {
        outFile << "Random numbers between n(0.95 and 1.05):\n";
        int i = 0;
        int j = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 99 && i == 0; j++) {
                j_now = m * (j + 1) * dis(gen) + c;
                i_now = (j + 1) * dis(gen);
                i_change_sum += i_now - i_last;
                j_change_sum += j_now - j_last;

                map[i][j] = i_now;
                map[i+1][j] = j_now;
                i_last = i_now;
                j_last = j_now;
                outFile << map[i][j] << " " ;
                outFile << map[i+1][j] << "\n";
            }
        }
    }
    

    cout<<"hello"<<endl;
    outFile.close();
}