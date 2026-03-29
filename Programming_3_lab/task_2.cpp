#include "iostream"
#include "random"
#include "vector"
#include "fstream"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::ofstream outFile("Output_For_TASK_2.txt");
    
    using namespace std;
    uniform_real_distribution<> dis(-6.7, 6.7);
    vector<vector<float>> map(99, vector<float>(99, 1));
    
    float x_last = 0.0;
    float y_last = 0.0;
    float x_now = 0.0;
    float y_clean = 0.0;
    float y_noise = 0.0;
    float x_change_sum = 0.0;
    float y_change_sum = 0.0;

    // y = kx + m
    float k = 2.0;
    float m = 0.0;

    if (outFile.is_open()) {
        outFile << "Random numbers between n(-6.7 and 6.7):\n";
        //int x = 0;
        //int y = 0;
        for (int x = 0; x < 99; x++) {
                y_clean = k*(x+1) + m;     // Create the linear function "where x is a feature AND  y is the noisy output"
                y_noise = y_clean + dis(gen) // Add the additive noise to the linear function
                x_now = (y + 1) + dis(gen);   // Add not multiply
                x_change_sum += x_now - x_last;
                y_change_sum += y_clean - y_last;

                map[x][y] = x_now;
                map[x+1][y] = y_noise;  // Store the noisy linear function in the dataset "since the goal is to train  a model to handle noise"
                x_last = x_now;
                y_last = y_clean;
                outFile << map[0][x] << " " ;  // Store x values in a row alone
                outFile << map[1][x] << "\n";  // Store y values in a row alone
        }
    }
    

    cout<<"hello"<<endl;
    outFile.close();
}
