// 41409914 MABOTE KGAUGELO PERTUNIA

/* CREATING A TWO PLAYER TIC TAC TOE GAME WHERE THE FIRST PLAYER WHO FILLS THE GAME WITH 3Xs OR 3Os IN A HORIZONTAL, VERTICAL,
OR DIAGONAL WILL WIN THE GAME. IN SOME CASES THE GAME IS CONSIDERED A DRAW BECAUSE NONE OF THE PLAYERS SUCCEEDS. THE WINNER GOES HOME WITH A CAR.*/

// Directive headers (importing the inbuilt libraries)
#include <iostream>
#include <string>
#include <fstream> // For file handling
#include <limits>  // For input validation
#include <memory>// for smart pointers

using namespace std;

// Struct to represent a player
struct Player {
    string name;
    char symbol;  // ('X' or 'O')
};

class TicTacToe {
private:
    char board[3][3]; // 3x3 game board
    string player1, player2; // Player names
    char currentPlayer; // Current player (X or O)
    int gamesPlayed; // Counter for games played

public:
    TicTacToe(string p1, string p2) : player1(p1), player2(p2), currentPlayer('X'), gamesPlayed(0) {
        resetBoard(); // Initialize the board
    }

    // Function to reset the board
    void resetBoard() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = ' '; // Fill the board with empty spaces
    }

    // Function to display the board
    void displayBoard() {
        cout << "\nPlayer - 1 [" << player1 << " (X)]          Player - 2 [" << player2 << " (O)]\n\n";
        for (int i = 0; i < 3; ++i) {
            cout << "                     |     |\n";
            cout << "                " << board[i][0] << "    |  " << board[i][1] << "  |  " << board[i][2] << "\n";
            cout << "                _____|_____|_____\n";
        }
    }

    // Function to check if the game is over
    bool isGameOver() {
        return checkWinner() != ' ' || isBoardFull(); // Game over if there's a winner or the board is full
    }

    // Function to check for a winner
    char checkWinner() {
        // Check rows, columns, and diagonals for a winner
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
                return board[i][0]; // Return the winner's symbol
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
                return board[0][i]; // Return the winner's symbol
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
            return board[0][0]; // Return the winner's symbol
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
            return board[0][2]; // Return the winner's symbol
        return ' '; // No winner
    }

    // Function to check if the board is full
    bool isBoardFull() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == ' ')
                    return false; // Board is not full
        return true; // Board is full
    }

    // Function for player turn
    void playerTurn() {
        int move;
        while (true) {
            cout << (currentPlayer == 'X' ? player1 : player2) << "'s turn (" << currentPlayer << "): ";
            cin >> move; // Get player input

            // Input validation for move
            while (cin.fail() || move < 1 || move > 9) {
                cout << "Invalid input! Please enter a number between 1 and 9: ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cin >> move; // Get the input again
            }
            move--; // Convert to zero-based index

            // Check if the move is valid
            if (move >= 0 && move < 9 && board[move / 3][move % 3] == ' ') {
                board[move / 3][move % 3] = currentPlayer; // Make the move
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch players
                break; // Valid move made
            } else {
                cout << "Invalid move! Try again.\n"; // Invalid input handling
            }
        }
    }

    // Function to save game results to a file
    void saveGameResult(const string& winner) {
        ifstream infile("gameResults.txt"); // Open the file to check existing results
        string line;
        bool resultExists = false; // Flag to check for duplicate results

        // Check if the result already exists in the file
        while (getline(infile, line)) {
            if (line.find("Winner: " + winner) != string::npos &&
                line.find(player1) != string::npos &&
                line.find(player2) != string::npos) {
                resultExists = true; // Duplicate result found
                break; // Exit the loop if found
            }
        }
        infile.close(); // Close the file after reading

        // If the result does not exist, save it to the file
        if (!resultExists) {
            ofstream outfile("gameResults.txt", ios::app); // Open file in append mode
            if (outfile.is_open()) {
                outfile << "Game Result: " << player1 << " vs " << player2 << " - Winner: " << winner << endl; // Save result
                outfile.close(); // Close the file
            } else {
                cout << "Unable to open file to save results.\n"; // Error handling
            }
        } else {
            cout << "This game result has already been recorded.\n"; // Inform the user of duplicate
        }
    }

    // Function to read and display past game results
    void readGameResults() {
        ifstream infile("gameResults.txt"); // Open the file to read results
        if (infile.is_open()) {
            string line;
            cout << "\n--- Past Game Results ---\n";
            while (getline(infile, line)) {
                cout << line << endl; // Output each line of results
            }
            infile.close(); // Close the file
        } else {
            cout << "No past results found.\n"; // Error handling
        }
    }

    // Function to increment the games played counter
    void incrementGamesPlayed() {
        gamesPlayed++; // Increment the count
    }

    // Function to get the number of games played
    int getGamesPlayed() {
        return gamesPlayed; // Return the count
    }
};

// Function to display instructions
void displayInstructions() {
    cout << "Welcome to the Tic Tac Toe game! I hope you are ready to relive your childhood memories...\n\n";
    cout << "Instructions:\n";
    cout << "1. Enter your moves as a number corresponding to the cell (1-9).\n";
    cout << "2. Ensure the cell is empty and within bounds.\n";
    cout << "3. The first player to get three in a row, column, or diagonal wins.\n";
    cout << "4. Enjoy the game and may the best player win!\n";
}

int main() {
    string name1, name2; // Player names

    // Get Player 1 name with validation
    cout << "Enter Player 1 name: ";
    cin >> name1;
    while (name1.empty()) {
        cout << "Player 1 name cannot be empty. Please enter a valid name: ";
        cin >> name1;
    }

    // Get Player 2 name with validation
    cout << "Enter Player 2 name: ";
    cin >> name2;
    while (name2.empty()) {
        cout << "Player 2 name cannot be empty. Please enter a valid name: ";
        cin >> name2;
    }

    TicTacToe game(name1, name2); // Create a new TicTacToe game instance

    int choice; // Variable to hold menu choice

    // Main menu loop
    while (true) {
        cout << "\n--- Tic Tac Toe Menu ---\n";
        cout << "1. Play Game\n";
        cout << "2. Instructions\n";
        cout << "3. View Past Results\n";
        cout << "4. View Number of Games Played\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        unique_ptr<int>unPtr1 = make_unique<int>(choice); //Smart pointer to store the players choice
        cin >> *unPtr1; // Player input


        // Input validation for menu choice
        while (cin.fail() || *unPtr1 < 1 || *unPtr1 > 9) {
            cout << "Invalid input! Please enter a number between 1 and 9: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cin >> *unPtr1; // Get the input again
        }

        // Switch block for menu choices
        switch (*unPtr1) {
            case 1: // Play Game
            {
                game.resetBoard(); // Reset the game board
                while (!game.isGameOver()) {
                    game.displayBoard(); // Display the board
                    game.playerTurn(); // Player makes a move
                }

                // Check the winner and display results
                char winner = game.checkWinner();
                game.displayBoard(); // Display final board
                if (winner != ' ') {
                    cout << "Congratulations! The winner is " << (winner == 'X' ? name1 : name2) << "!\n"; // Winner announcement
                    game.saveGameResult((winner == 'X' ? name1 : name2)); // Save the game result
                } else {
                    cout << "It's a draw!\n"; // Draw announcement
                }
                game.incrementGamesPlayed(); // Increment the games played counter
                break;
            }
            case 2: // Instructions
            {
                displayInstructions(); // Display instructions
                break;
            }
            case 3: // View Past Results
            {
                game.readGameResults(); // Read and display game results
                break;
            }
            case 4: // View Number of Games Played
            {
                cout << "Total games played: " << game.getGamesPlayed() << endl; // Display games played
                break;
            }
            case 5: // Exit
            {
                cout << "Thank you for playing!\n"; // Exit message
                return 0; // Exit the program
            }
        } // End of switch block
    } // End of while loop
} // End of main function
