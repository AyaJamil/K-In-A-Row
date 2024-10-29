#include <stdio.h>
#include <stdbool.h>

#define MAX_COLS 7


// function declarations

void print_board(char board[][MAX_COLS], int rows, int cols);

void print_get_row();

void print_get_column();

void print_error_number_of_rows();

void print_error_number_of_cols();

void print_get_k();

void print_error_k(int correct_k);

void print_player_enter_col(char player_symbol);

void print_invalid_input();

void print_column_full();

void print_draw_msg();

void print_win_msg(char player_symbol, int turn_num);

int check_if_row_valid();

int check_if_column_valid();

int check_if_k1_valid(int numofrows, int numofcolumns);

int start_game(char board[][MAX_COLS],int numrows,int numofcol,int k,bool END);

bool y_to_play(char board[][MAX_COLS],int numofrows,int numofcol,int k,int ap);

int num_of_column();

bool input(char board[][MAX_COLS],int col,char symbol,int numrows,int numcol);

bool x_to_play(char board[][MAX_COLS],int numofrows,int numofcol,int k,int ap);

int is_index_valid(int column, int numofcolumns, char sym);

bool is_board_full(char board[][MAX_COLS],int numofrows, int numofcolumns);

int col_full(char board[][MAX_COLS],int col,int numrows,int numofcol,char sym);

char win(char board[][MAX_COLS],int numrows,int numcol,int k,char sym,int ap);

bool dia_right(char board[][MAX_COLS],int numrows,int numcol,int k,char sym);

bool is_vertical(char board[][MAX_COLS],int numrows,int numcol,int k, char sym);

bool horizontal(char board[][MAX_COLS],int numrows,int numcol,int k,char sym);

bool dia_left(char board[][MAX_COLS],int numrows,int numcol,int k,char sym);

int main() {
    int numberofrows, numberofcolumns, numberofk;
    char board[MAX_COLS][MAX_COLS];
    print_get_row(); numberofrows = check_if_row_valid();
    if(numberofrows == 0){
        return 1;
    }
    print_get_column(); numberofcolumns = check_if_column_valid();
    if(numberofcolumns == 0){
        return 1;
    }
    for (int i = 0; i < numberofrows; i++) {
        for (int j = 0; j < numberofcolumns; j++) {
            board[i][j] = ' ';
        }
    }
    print_get_k();
    numberofk = check_if_k1_valid(numberofrows, numberofcolumns);
    print_board(board, numberofrows, numberofcolumns);
    start_game(board, numberofrows, numberofcolumns, numberofk, false);
}

// function implementations
//checks if the input of rows is valid
int check_if_row_valid(){
    int num_of_rows;
    scanf("%d", &num_of_rows);
    if(num_of_rows > MAX_COLS || num_of_rows < 1){
        print_error_number_of_rows();
        return 0;
    }else {
        return num_of_rows;
    }
}
//checks if the input of columns is valid
int check_if_column_valid(){
    int num_of_columns;
    scanf("%d", &num_of_columns);
    if(num_of_columns > MAX_COLS || num_of_columns < 1){
        print_error_number_of_cols();
        return 0;
    }else {
        return num_of_columns;
    }
}
//checks if k is valid
int check_if_k1_valid(int numofrows, int numofcolumns){
    int k, min;
    scanf("%d", &k);
    if(numofrows > numofcolumns){
        min = numofcolumns;
    }else{
        min = numofrows;
    }
    if(k <= 0 || k > min){
        print_error_k(min);
        return min;
    }
    return k;
}

int start_game(char board[][MAX_COLS],int numrows,int numofcol,int k,bool END){
    if(END){
        return 0;
    }
    y_to_play(board, numrows, numofcol, k, 0);
    return 0;
}

bool y_to_play(char board[][MAX_COLS],int numofrows,int numofcol,int k,int ap){
    ap++;
    print_player_enter_col('Y');
    char symbol = 'Y';  bool END; int column = num_of_column();
    column = is_index_valid(column, numofcol, symbol);
    column = col_full( board,column,numofrows, numofcol, symbol);
    input(board,column,symbol ,numofrows, numofcol);
    END = win(board,numofrows,numofcol,k,symbol,ap);
    if(END == 1) return END;
    x_to_play(board,numofrows, numofcol, k, ap);
    return 0;
}

bool x_to_play(char board[][MAX_COLS],int numofrows,int numofcol,int k,int ap){
    ap++;
    print_player_enter_col('X');
    char symbol = 'X';  int column = num_of_column();
    column = is_index_valid(column, numofcol, symbol);
    column = col_full( board,column,numofrows,numofcol, symbol);
    input(board,column,symbol ,numofrows, numofcol);
    bool END = win(board,numofrows,numofcol, k, symbol, ap);
    if(END == 1) return END;
    y_to_play(board,numofrows, numofcol, k, ap);
    return 0;
}

char win(char board[][MAX_COLS],int numrows,int numcol,int k,char sym,int ap){
    bool diaright,dialeft, vertical, ishorizontal;
    diaright = dia_right(board,numrows, numcol, k, sym);
    dialeft = dia_left(board,numrows, numcol, k, sym);
    vertical = is_vertical(board,numrows, numcol, k, sym);
    ishorizontal = horizontal(board,numrows, numcol, k, sym);
    if(diaright == 1 || vertical == 1 || ishorizontal == 1 || dialeft == 1){
        print_win_msg(sym, ap);
        return 1;
    }
    bool full = is_board_full(board,numrows, numcol);
    if(full == 1){
        print_draw_msg(); return 1;
    }
    return 0;
}

/*checks every cell in array, if its equal to symbol it checks if the player won
 * and return 1 if yes and 0 if no */
bool dia_right(char board[][MAX_COLS],int numrows,int numcol,int k,char sym){
    int appearance = 0;
    for (int i = 0; i < numrows; i++) {
        for (int j = 0; j < numcol; j++) {
            //if the cell equals to the symbol
            if(board[i][j] == sym){
                appearance = 1;
                int s = 1;
                while( i+s < numrows && j-s >= 0 && board[i+s][j-s] == sym){
                    appearance++;
                    s++;
                }
                s = 1;
                while( i-s >= 0 && j+s < numcol && board[i-s][j+s] == sym){
                    appearance++;
                    s++;
                }
                if(appearance >= k){
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool dia_left(char board[][MAX_COLS],int numrows,int numcol,int k,char sym){
    int appearance = 0;
    for (int i = 0; i < numrows; i++) {
        for (int j = 0; j < numcol; j++) {
            //if the cell equals to the symbol
            if(board[i][j] == sym){
                appearance = 1;
                int s = 1;
                while( i-s >= 0 && j-s >= 0 && board[i-s][j-s] == sym){
                    appearance++;
                    s++;
                }
                s = 1;
                while( i+s < numrows && j+s < numcol && board[i+s][j+s] == sym){
                    appearance++;
                    s++;
                }
                if(appearance >= k){
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool is_vertical(char board[][MAX_COLS],int numrows,int numcol,int k, char sym){
    int appearance = 0;
    for (int i = 0; i < numrows; i++) {
        for (int j = 0; j < numcol; j++) {
            //if the cell equals to the symbol
            if(board[i][j] == sym){
                appearance = 1;
                int s = 1;
                while( i+s < numrows && board[i+s][j] == sym){
                    appearance++;
                    s++;
                }
                s = 1;
                while( i-s >= 0 && board[i-s][j] == sym){
                    appearance++;
                    s++;
                }
                if(appearance >= k){
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool horizontal(char board[][MAX_COLS],int numrows,int numcol,int k,char sym){
    int appearance = 0;
    for (int i = 0; i < numrows; i++) {
        for (int j = 0; j < numcol; j++) {
            //if the cell equals to the symbol
            if(board[i][j] == sym){
                appearance = 1;
                int s = 1;
                while( j+s < numcol && board[i][j+s] == sym){
                    appearance++;
                    s++;
                }
                s = 1;
                while( j-s >= 0 && board[i][j-s] == sym){
                    appearance++;
                    s++;
                }
                if(appearance >= k){
                    return 1;
                }
            }
        }
    }
    return 0;
}

//put input in THE array and print it
bool input(char board[][MAX_COLS],int col,char symbol,int numrows,int numcol){
    int i = numrows - 1;
    while(board[i][col] != ' ' ){
        i--;
    }
    board[i][col] = symbol;
    print_board(board, numrows, numcol);
    return 1;
}

//puts number of column
int num_of_column(){
    int column;
    scanf("%d", &column);
    return column;
}

//checks valid
//checks if column full
int col_full(char board[][MAX_COLS],int col,int numrows,int numofcol, char sym){
    bool full = 1; int newnumofrows = numrows;numrows--;
    while(numrows >= 0){
        if(board[numrows][col] == ' ' ){
            full = 0; break;
        }
        numrows--;
    }
    if(full == 0){
        return col;
    }else{
        print_column_full();
        print_player_enter_col(sym);
        scanf("%d", &col);
        col = is_index_valid(col, numofcol, sym);
        col_full(board,col, newnumofrows, numofcol, sym);
    }
    return 0;
}

//checks if full
bool is_board_full(char board[][MAX_COLS],int numofrows, int numofcolumns) {
    bool isfull = 1;
    for (int i = 0; i < numofrows; i++) {
        for (int j = 0; j < numofcolumns; j++) {
            if (board[i][j] == ' ')
                isfull = 0;
        }
    }
    return isfull;
}

//checks if index valid
int is_index_valid(int column, int numofcolumns, char sym){
    if(column > numofcolumns - 1) {
        print_invalid_input();
        print_player_enter_col(sym);
        scanf("%d", &column);
        is_index_valid(column, numofcolumns, sym);
    }else{
        return column;
    }
    return is_index_valid(column, numofcolumns, sym);
}

void print_get_row(){
    printf("Number of rows:\n");
}

void print_get_column(){
    printf("Number of columns:\n");
}

void print_error_number_of_rows(){
    printf("Error: Number of rows must be smaller than 8\n");
}

void print_error_number_of_cols(){
    printf("Error: Number of columns must be smaller than 8\n");
}

void print_get_k(){
    printf("Please enter k:\n");
}

void print_error_k(int correct_k){
    printf("Error: k must be greater than zero, setting k to %d\n", correct_k);
}

void print_player_enter_col(char player_symbol){
    printf("Player %c, enter col:\n", player_symbol);
}

void print_invalid_input(){
    printf("Invalid input, try again\n");
}

void print_column_full(){
    printf("Column is full, try again\n");
}

void print_board(char board[][MAX_COLS], int rows, int cols) {
    //print the board in the following format:
    printf("\n");
    for (int i = 0; i < rows; i++) {
        printf("|");
        for (int j = 0; j < cols; j++) {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
}


//print if draw
void print_draw_msg() {
    printf("DRAW!\n");
}

void print_win_msg(char player_symbol, int turn_num) {
    printf("Player %c won in %d moves!\n", player_symbol, turn_num);
}




