#include "iostream"
#include "random"
#include "vector"
#include "fstream"

int main() {

    float x_last = 0.0;
    float y_last = 0.0;
    float x_now = 0.0;
    float y_clean = 0.0;
    float y_noise = 0.0;
    float x_change_sum = 0.0;
    float y_change_sum = 0.0;
    float x_sum = 0.0;
    float y_sum = 0.0;
    float x_sum_squared = 0.0;
    float xy_sum = 0.0;
    float x_squared = 0.0;
    //y = wx + b
    float w = 2.0;
    float b = 0.0;
    int N_loop = 100; // loop number


    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::ofstream outFile("Output_For_TASK_2.txt");
    
    using namespace std;
    uniform_real_distribution<> dis(-6.7, 6.7);
    vector<vector<float>> map(2, vector<float>(N_loop, 1));
    




  // generating data with noise (for single-variable linear regression, and for two-variable linear regression)  
    if (outFile.is_open()) {
        outFile << "Random numbers between n(-6.7 and 6.7):\n";
        for (int x = 0; x < N_loop; x++) {
                y_clean = w*(x+1) + b;     // Create the linear function "where x is a feature AND  y is the noisy output"
                y_noise = y_clean + dis(gen); // Add the additive noise to the linear function
                x_now = (x + 1) + dis(gen);   // Add not multiply
                x_change_sum += x_now - x_last;
                y_change_sum += y_clean - y_last;

                x_sum += x_now;
                y_sum += y_noise;
                x_squared = x_now * x_now;
                x_sum_squared += x_squared;
                xy_sum += x_now * y_noise;
                    
                map[0][x] = x_now;
                map[1][x] = y_noise;     // Store the noisy linear function in the dataset "since the goal is to train  a model to handle noise"
                outFile << map[0][x] << " " ;  // Store x values in a row alone
                outFile << map[1][x] << "\n";  // Store y values in a row alone
        }
    }
    
    // for implementating the normal equation

    // Assign Normal Equations 
    w = (N_loop*xy_sum -  x_sum*y_sum) / ((N_loop*x_sum_squared) - (x_sum * x_sum));
    b = (y_sum - w*x_sum) / N_loop;

    cout<<"hello"<<endl;
    outFile.close();

    cout << "Normal Equation (w 'slope'): " << w << endl;
    cout << "Normal Equation (b 'intercept'): " << b << endl;



    //For implementing the gradient descent method for simple linear regression problem (single variable linear regression).
// The aim is minimising the cost function J with respect to theta using iterative correction using gradient descent method.
float theta_old = 0.0, theta_new = 0.0; // the parameters we are trting to optimise
float J = 0.0;  // The cost function
//float Delta_J = 0.0;  // The derivative of the cost function with respect to theta
float Delta_w = 0.0; //  cost function derivative with respect to w
float Delta_b = 0.0; // cost function derivative with respect to b
// Note: Delta_J tells us the slope of cost function at out current posisiton and also how much we need to adjust theta to mninimise the cost function 
float Learning_rate = 0.0001; // determines step size at each iteration
float w_new = 0.0; // the value of w after update using gradient descent method
float b_new = 0.0; // the value of b after update using gradient descent method
int Iterations = 0; // The number of iterationns for the Gradient descent method to run (or until convergence)

// Note the minus sign is important because we want to move in the opposite direction as in DOWNHILL rather UPHILL with the gradient
//theta_new = theta_old - Learning_rate * Delta_J; // The Update Rule that repeats until value of Delta_J is close to zero or oes not change much anymore (convergence)

// sum 
float w_by_x_i = 0.0; // the sum of w*x_i for all i
float b_sum = 0.0; // the sum of b*1 for all i
float y_i_sum = 0.0; // the sum of y_i for all i
float x_i_sum = 0.0; // the sum of x_i for all i
float Delta_w_sum = 0.0;
float Delta_b_sum = 0.0;

float w_inital = 0.0; // initial value of w
float b_inital = 0.0; // initial value of b

for (int Iterations = 0; Iterations < 167000; Iterations++) {
    for (int i = 0; i < N_loop; i++) {
       float x_i = map[0][i]; // the i-th x value in dataset
       float y_i = map[1][i]; // the i-th y value in dataset
        float Error = 0.0; // error for the i-th point of data
//        b_sum += b_inital;
     //   y_i_sum += y_i;
       // x_i_sum += x_i;
        w_by_x_i = w_inital * x_i;
                
        // derivative of the loss/cost function with respect to w and b respectively
       // Delta_w = (1.0/N_loop) * ((w_inital*x_i_sum + b_inital - y_i_sum)*x_i_sum); // The derivative of the cost function with respect to w
        Error = ((w_inital *  x_i) + b_inital - y_i);  // ERROR OF CURRENT POINT
        
       ////// IGNORE Error = Delta_w - Delta_b; // Error if the i-th point of data which is the difference between the predicted and acrual value for the i-th point of data which is the difference between the predicted value and the actual value
        Delta_w = Error * x_i;
        Delta_b = Error * 1;
        Delta_w_sum += Delta_w; //  sum of  derivatives of  cost function with respect to w for all i
        Delta_b_sum += Delta_b; // sum of  derivatives of  cost function with respect to b for all i
        


    }
        w_new = w_inital - Learning_rate * (Delta_w_sum/N_loop); // same rule but for our case
        b_new = b_inital - Learning_rate * (Delta_b_sum/N_loop); // same rule but for our case
    Delta_w_sum = 0.0; // RESET SUM OF DERIVATIVES FOR NEXT INTERATION
    Delta_b_sum = 0.0; // reset the sum of derivatives of cost function
    w_inital = w_new; // update the position for next iteration
    b_inital = b_new; // update the POSITION    for next iteration

}
    cout << "Gradient Descent (w 'slope'): " << w_new << endl;
    cout << "Gradient Descent (b 'intercept'): " << b_new << endl;
 

    // See how close they are!
cout << "Difference in w: " << abs(w - w_inital) << endl;
cout << "Difference in b: " << abs(b - b_inital) << endl;


//for extending the gradent descent method to multiple linear regression problem.
    


// LAST PUSH! SHINZOU SASAGEYOOOOO! WE LOVE U KHEIM SENSEI !!


}

