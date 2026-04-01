#include <iostream>
#include <vector>
using namespace std;


class TicTacToe_Game{
private:
    // Member variables will be defined here
    char Current_Player;
    // The game's internal state is protected now
    vector<vector<char>> map;



public: 
    // Create a constructor to initialize the game
    TicTacToe_Game(){
        // Initialise the game board
        map = vector<vector<char>>(3, vector<char>(3, '.'));
        // Initialise the current player
        Current_Player = 'X';

    }   
    // Functions will be defined here
    // Prints the game board
    void Print_Arena() const {
    cout << "Enter your move (1-9): " << endl; cout << "GO GO GO YOUR TURN! Player: " << Current_Player << endl;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }
    //
    // Check if the player ('X' or 'O') has won the game
    // Just breaks the line in 2 for better readability    
    //function that returns True if all elements in an iterable.
    //The all() function is used to check whether certain conditions all conditions are met


    bool Check_Winner(){
        for (int i = 0; i < 3; i++){
            // Check horizontal lines
            if(map[i][0] == Current_Player && map[i][1] == Current_Player && map[i][2] == Current_Player){
                return true;
            }

            // Check vertical lines
            else if(map[0][i] == Current_Player && map[1][i] == Current_Player && map[2][i] == Current_Player){
                return true;
            }               
        }
        // Check diagonal lines
        if(map[0][0]== Current_Player && map[1][1] == Current_Player && map[2][2] == Current_Player){
            return true;
        }
   
        // Check antidiagonal lines
        if(map[0][2]== Current_Player && map[1][1] == Current_Player && map[2][0] == Current_Player){
            return true;
        }   

        // If no winner is found, return false
        return false;  
    }



    bool Is_Board_Full(){
        // Check if the board is full (no empty spots), which is a Draw
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(map[i][j] == '.'){
                    // If no draw, return false
                    return false; 
                }
            }
        }
        return true;
    }

    void Switch_Player(){
        if (Current_Player == 'X'){
            Current_Player = 'O';
        }
        else if (Current_Player == 'O'){
                Current_Player = 'X';
            }
        }

    void Player_Move(){
        while(true){
            // Get a valid move from the player
            int move; 
            cin >> move; move--;  // Decrement move to convert to indexing format
            int row = move / 3; 
            int col = move % 3;

            // Input validation for move
            if (move < 0 || move > 8 || cin.fail()){
                cout << "Invalid move broski. Please enter a number between 1 and 9." << endl;
                cin.clear(); // Clear the error flag and reset cin, wihtout this cin will always fail
                cin.ignore(420, '\n'); // Ignore the old bad input, or cin will try to read the same input again, we skip 420 charaters and \n tells the compiler to stop skippping once the end of the lines is reached where the user pressed the Enter button
                Print_Arena();
       }
            // Position Check if used
            else if (map[row][col] == '.'){
                map[row][col] = Current_Player;
                return;
            }
            // if position is used, redo the move
            else if (map[row][col] != '.'){
                cout << "This spot is already taken you fool. Try again." << endl;
                Print_Arena();
            }

        } 
    }
};

int main(){
    TicTacToe_Game Kheim_TicTacToe;
    while(true){
        // Print the game board
        Kheim_TicTacToe.Print_Arena();
        // Get Player move, check if he wins
        Kheim_TicTacToe.Player_Move();

        //Winner Congratulations
        if(Kheim_TicTacToe.Check_Winner()){
        Kheim_TicTacToe.Print_Arena();
        cout << "WINNER WINNER CHICKEN DINNER!!! WOHOOOOO!! YOU ARE HIM, EVEN BETTER THAN KHEIM!" << endl;
        break;
        }

        // Check for a draw, if not then switch palyer
        if(Kheim_TicTacToe.Is_Board_Full()){
        Kheim_TicTacToe.Print_Arena();
        cout << "It's a Draw! BORIIING!" << endl;
        break;
        };

        //Next Round
        Kheim_TicTacToe.Switch_Player();

    }
    
    return 0;
}