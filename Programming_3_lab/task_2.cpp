#include "iostream"
#include "random"
#include "vector"
#include "fstream"

//Input from user
float error_bound = 0.05;
int number_of_data = 100;
int number_of_data_into_vector = 0;
// y = mx + c
float gradient = 2.0;
float intercept = 0.0;

//Calculation variables
float i_now = 0.0;
float j_now = 0.0;
float i_sum = 0.0;
float j_sum = 0.0;
float i_now_x_j_now_sum = 0.0;
float i_average = 0.0;
float j_average = 0.0;
float normal_equation_gradient = 0.0;
float normal_equation_intercept = 0.0;
float i_squared_sum = 0.0;
float i_average_squared = 0.0;


int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::ofstream outFile("output.txt");
    
    using namespace std;


    if (outFile.is_open()) {
        outFile << "Random numbers between n(" << 1 - error_bound << " and " << 1.0 + error_bound << "):\n";
        int i = 0;
        int j = 0;
        number_of_data_into_vector = number_of_data - 1;
        cout<<"number_of_data_into_vector: ";
        cin >> number_of_data_into_vector;
        cout<<"gradient: ";
        cin >> gradient;
        cout<<"intercept: ";
        cin >> intercept;
        cout<<"Error Bound for house price: ";
        cin >> error_bound;

        uniform_real_distribution<> dis(1 - error_bound, 1.0 + error_bound);
        vector<vector<float>> map(3, vector<float>(number_of_data, 1));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < number_of_data_into_vector && i == 0; j++) {
                //generate data //i_now = x, j_now = y
                i_now = (j + 1) * dis(gen);
                j_now = (gradient * (i_now) + intercept) * dis(gen);
                
                //normal calculation
                i_sum += i_now;
                j_sum += j_now;
                i_now_x_j_now_sum += i_now * j_now;
                i_squared_sum += i_now * i_now;

                map[i][j] = i_now;
                map[i+1][j] = j_now;

                outFile << map[i][j] << " " ;
                outFile << map[i+1][j] << "\n";
            }
        }
        i_average = i_sum / number_of_data;
        j_average = j_sum / number_of_data;
        i_average_squared = i_average * i_average;
        normal_equation_gradient = (i_now_x_j_now_sum + i_average * j_average - i_average * j_sum - j_average * i_sum) / (i_squared_sum - 2 * i_sum * i_average + i_average_squared);
        normal_equation_intercept = j_average - normal_equation_gradient * i_average;
        outFile << "Normal Equation Gradient: " << normal_equation_gradient << "\n";
        outFile << "Normal Equation Intercept: " << normal_equation_intercept << "\n";
        outFile << "Normal Equation Line: House Price = " << normal_equation_gradient << " * Size + " << normal_equation_intercept << "\n";
        outFile.close();
    }
}