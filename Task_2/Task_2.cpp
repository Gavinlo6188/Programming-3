#include "iostream"
#include "random"
#include "vector"
#include "fstream"

int main() {


// 1.0 SIMPLE LINEAR REGRESSION: FIRST PUSH! SHINZOU SASAGEYOOOOO! WE LOVE U KHEIM SENSEI !!
    float x1_last = 0.0;
    float x2_last = 0.0;
    float y_last = 0.0;

    float x1_now = 0.0;
    float x2_now = 0.0;
    float y_clean = 0.0;
    float y_noise = 0.0;
    float x1_change_sum = 0.0;
    float x2_change_sum = 0.0;
    float y_change_sum = 0.0;
    float x1_sum = 0.0;
    float x2_sum = 0.0;
    float y_sum = 0.0;
    float x1_sum_squared = 0.0;
    float x2_sum_squared = 0.0;
    float xy_sum = 0.0;
    float x_squared = 0.0;
    //y = wx + b
    float w = 2.0;
    float b = 0.0;
    int N_loop = 100; // loop number


    float w1_True = 2.0; 
        float w2_True = 3.0; 



    std::random_device rd;
    std::mt19937 gen(rd());    
    std::ofstream outFile("Output_For_TASK_2.txt");
    using namespace std;
    uniform_real_distribution<> dis(-6.7, 6.7);
    vector<vector<float>> map(3, vector<float>(N_loop, 1)); // create a vector with 3 rows "for x1, x2, and y" (we need only 2 for simple linear regression, and 3 for multiple linear regression)

// 1.1: generating data with noise (for single-variable linear regression, and for two-variable linear regression)  
    if (outFile.is_open()) {
        outFile << "Random numbers between n(-6.7 and 6.7):\n";
        for (int x = 0; x < N_loop; x++) {
                         x1_now = (x + 1) + dis(gen);   // Add not multiply: so here we addd additive noise to the regression line to simulate real-life data
                x2_now = (x + 1) + dis(gen);   // Add not multiply    
            y_clean = w1_True*(x1_now) + w2_True*(x2_now) + b;     // Create the linear function "where x is a feature AND  y is the noisy output"
                y_noise = y_clean + dis(gen); // Add the additive noise to the linear function

                x1_change_sum += x1_now - x1_last;
                x2_change_sum += x2_now - x2_last;
                y_change_sum += y_clean - y_last;

                x1_sum += x1_now;
                x2_sum += x2_now;
                y_sum += y_noise;
                x_squared = x1_now * x1_now;
                x1_sum_squared += x_squared;
                xy_sum += x1_now * y_noise;
                    
                map[0][x] = x1_now;
                map[1][x] = x2_now;
                map[2][x] = y_noise;     // Store the noisy linear function in the dataset "since the goal is to train  a model to handle noise"
                outFile << map[0][x] << " " ;  // Store x1 values in a row alone
                outFile << map[1][x] << " " ;  // Store x2 values in a row alone
                outFile << map[2][x] << "\n";  // Store y values in a row alone
        }
    }
    
// 1.2: NORMAL EQUATION IN SIMPLE LINEAR REGRESSION
    // Assign Normal Equations 
    w = (N_loop*xy_sum -  x1_sum*y_sum) / ((N_loop*x1_sum_squared) - (x1_sum * x1_sum));
    b = (y_sum - w*x1_sum) / N_loop;

    cout<<"hello"<<endl;
    outFile.close();

    cout << "Normal Equation (w 'slope'): " << w << endl;
    cout << "Normal Equation (b 'intercept'): " << b << endl;



//1.3: GRADIENT DESCENT METHOD FOR SIMPLE LINEAR REGRESSION
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

    float w_by_x_i = 0.0; // the sum of w*x_i for all i
    float b_sum = 0.0; // the sum of b*1 for all i
    float y_i_sum = 0.0; // the sum of y_i for all i
    float x_i_sum = 0.0; // the sum of x_i for all i
    float Delta_w_sum = 0.0;
    float Delta_b_sum = 0.0;

    float w_initial = 0.0; // initial value of w
    float b_initial = 0.0; // initial value of b

    for (int Iterations = 0; Iterations < 167000; Iterations++) {
        for (int i = 0; i < N_loop; i++) {
        float x_i = map[0][i]; // the i-th x value in dataset
        float y_i = map[2][i]; // the i-th y value in dataset
            float Error = 0.0; // error for the i-th point of data
    //        b_sum += b_initial;  
        //   y_i_sum += y_i;
        // x_i_sum += x_i;
            w_by_x_i = w_initial * x_i;
                    
            // derivative of the loss/cost function with respect to w and b respectively
        // Delta_w = (1.0/N_loop) * ((w_initial*x_i_sum + b_initial - y_i_sum)*x_i_sum); // The derivative of the cost function with respect to w
            Error = ((w_initial *  x_i) + b_initial - y_i);  // ERROR OF CURRENT POINT
            
        ////// IGNORE Error = Delta_w - Delta_b; // Error if the i-th point of data which is the difference between the predicted and acrual value for the i-th point of data which is the difference between the predicted value and the actual value
            Delta_w = Error * x_i;
            Delta_b = Error * 1;
            Delta_w_sum += Delta_w; //  sum of  derivatives of  cost function with respect to w for all i
            Delta_b_sum += Delta_b; // sum of  derivatives of  cost function with respect to b for all i
            


        }
            w_new = w_initial - Learning_rate * (Delta_w_sum/N_loop); // same rule but for our case
            b_new = b_initial - Learning_rate * (Delta_b_sum/N_loop); // same rule but for our case
        Delta_w_sum = 0.0; // RESET SUM OF DERIVATIVES FOR NEXT INTERATION
        Delta_b_sum = 0.0; // reset the sum of derivatives of cost function
        w_initial = w_new; // update the position for next iteration
        b_initial = b_new; // update the POSITION    for next iteration

    }
    cout << "Gradient Descent (w 'slope'): " << w_new << endl;
    cout << "Gradient Descent (b 'intercept'): " << b_new << endl;
    

        // See how close they are!
    cout << "This is Difference between w values to see error "
    cout << "Difference in w: " << abs(w - w_initial) << endl;
    cout << "Difference in b: " << abs(b - b_initial) << endl;






// 1.4: MULTIPLE LINEAR REGRESSION: LAST PUSH! SHINZOU SASAGEYOOOOO! WE LOVE U KHEIM SENSEI !!
    //For extending the gradent descent method to multiple linear regression problem.
        
    float w1_initial = 0.0; 
    float w2_initial = 0.0; 
    float w2_new = 0.0;
    float w1_new = 0.0;
    float b_initial_Multiple = 0.0;  // initial value of b for multiple linear regression
    float b_new_Multiple = 0.0; // new value of b for multiple linear regression
    float Error_Multiple = 0.0; // error for i-th point/position of data in multiple linear regression
    float Delta_w1_sum = 0.0;
    float Delta_w2_sum = 0.0;
    float Delta_b_sum_MULTI = 0.0; 
    float Delta_w1 = 0.0;
    float Delta_w2 = 0.0;

    for (int Iterations = 0; Iterations < 167000; Iterations++) {
        for (int i = 0; i < N_loop; i++) {
            float x1_i = map[0][i]; // i-th x1 value in the dataset
            float x2_i = map[1][i]; // i-th x2 value in the dataset
            float y_i = map[2][i]; // the i-th y value in dataset

            // w_by_x_i = w_initial * x_i;
                    
            // derivative of the loss/cost function with respect to w and b respectively
            // Delta_w = (1.0/N_loop) * ((w_initial*x_i_sum + b_initial - y_i_sum)*x_i_sum); // The derivative of the cost function with respect to w
            Error_Multiple = ((w1_initial *  x1_i) + (w2_initial * x2_i) + b_initial_Multiple - y_i);  // ERROR OF CURRENT POINT
            ////// IGNORE this line.... Error = Delta_w - Delta_b; // Error if the i-th point of data which is the difference between the predicted and acrual value for the i-th point of data which is the difference between the predicted value and the actual value

            Delta_w1 = Error_Multiple * x1_i;
            Delta_w2 = Error_Multiple * x2_i;
            Delta_b = Error_Multiple * 1; // sum of  derivatives of  cost function with respect to b for all i
            
            Delta_w1_sum += Delta_w1; //  sum of  derivatives of  cost function with respect to w1 for all i
            Delta_w2_sum += Delta_w2; //  sum of  derivatives of  cost function with respect to w2 for all i
            Delta_b_sum_MULTI += Delta_b; //  sum of  derivatives of  cost function with respect to b for all i

        }

            w1_new = w1_initial - Learning_rate * (Delta_w1_sum/N_loop); // same rule but for our case
            w2_new = w2_initial - Learning_rate * (Delta_w2_sum/N_loop); // same rule but for our case
            b_new_Multiple = b_initial_Multiple - Learning_rate * (Delta_b_sum_MULTI/N_loop); // same rule but for our case
            
            Delta_w1_sum = 0.0; // RESET SUM OF DERIVATIVES FOR NEXT INTERATION
            Delta_w2_sum = 0.0; // RESET SUM OF DERIVATIVES FOR NEXT INTERATION 
            Delta_b_sum_MULTI = 0.0; // reset the sum of derivatives of cost function
            
            w1_initial = w1_new; // update the position for next iteration
            w2_initial = w2_new; // update the position for next iteration
            b_initial_Multiple = b_new_Multiple; // update the POSITION  for next iteration
    }

    cout << "Multiple Linear Regression : Gradient Descent (w1 'slope'): " << w1_new << endl;
    cout << "Multiple Linear Regression : Gradient Descent (w2 'slope'): " << w2_new << endl;
    cout << "Multiple Linear Regression : Gradient Descent (b_initial_Multiple 'intercept'): " << b_new_Multiple << endl;
    


}
