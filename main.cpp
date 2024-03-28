#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib> 
#include <ctime>
int size_;
int** path;
char snake_body[] = "\u25A3";
bool gameOver;
int snake_line;
int snake_col;
int length;
int food_pos[2];
char movement; 
int frame_delay;



void generate_random_food_pos() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    food_pos[0] = rand() % (size_-2) + 1;
    food_pos[1] = rand() % (size_*2-2) + 1;
}


void setup() {
    gameOver = false; // condition for the game loop
    size_ = 15; // size of the map
    length = 1; // length of the snake
    movement = 'd'; // set the auto movement to right 
    frame_delay = 50; // delay after every loop (milliseconds)
    
    // creating the rows
    path = new int*[size_];


    // creating the cols
    for(int i = 0; i < size_; i++) {
        path[i] = new int[size_*2];
    }
    // creating the path for the snake. 
    // if the path[i][j] = 1 (true) => body of the snake
    // if the path[i][j] = 0 (false) empty space
    for(int i = 0; i < size_; i++)
        for(int j = 0; j < size_*2; j++) 
            path[i][j] = false;
    // initiate pos for the snake
    snake_line = 2;
    snake_col = 2;

    path[snake_line][snake_col] = true;

    generate_random_food_pos();
}


void update_path() {
    char input_key;
    if (_kbhit()) {
        input_key = _getch();

        switch(input_key) {
            case 'd':
                movement = input_key;
                break;
            case 'a':
                movement = input_key;
                break;
            case 's':
                movement = input_key;
                break;
            case 'w':
                movement = input_key;
                break;
        }
    }

    switch(movement) {
        // CASES for key input 
        // 'd' - for right
        // 'a' - for left
        // 'w' - for up
        // 's' - for down
        case 'd':
            if (!path[snake_line][snake_col+1] && !(snake_col == size_*2-2)) { // Check if the path is free, and the snake doesn't go outsite map
                path[snake_line][snake_col] = false; // Let the space free 
                snake_col += 1; // Move the snake
                path[snake_line][snake_col] = true; // Update the snake path
            }
            break;
            // All the cases below works the same for every input.
        
        case 'a':
            if (!path[snake_line][snake_col+1] && !(snake_col == 1)) {
                path[snake_line][snake_col] = false;
                snake_col -= 1;
                path[snake_line][snake_col] = true;
            }
            break;
        
        case 'w':
            if (!path[snake_line-1][snake_col] && !(snake_line == 1)) {
                path[snake_line][snake_col] = false;
                snake_line -= 1;
                path[snake_line][snake_col] = true;
            }
            break;
        
        case 's':
            if (!path[snake_line+1][snake_col] && !(snake_line == size_-2)) {
                path[snake_line][snake_col] = false;
                snake_line += 1;
                path[snake_line][snake_col] = true;
            }
            break;
    }
    
}

void move() {

}

void draw() {
    char ch;

    while(!gameOver) {
        update_path();
        for(int i = 0; i < size_; i++){
                for(int j = 0; j < size_*2; j++) 
                {
                    if(snake_line == i && snake_col == j) std::cout << "\u25C9" ;
                        //else if (j == 4 && i != 0 && i != size_-1) 
                            //std::cout << snake_body;
                            else if(i == 0 || i == size_-1) 
                                std::cout << "#";
                                else if(j == 0 || j == size_*2-1) 
                                    std::cout << "|";
                                    else if (i == food_pos[0] && j == food_pos[1])
                                        std::cout << "\u25A0";
                                        else 
                                            std::cout << " ";
                }
                std::cout << std::endl;
            }
            if ((food_pos[0] == snake_line) && (food_pos[1] == snake_col)) {
                generate_random_food_pos();
                length++;
            }
            std::cout << "D - right, A - left, S - down, W - up" << std::endl;
            std::cout << "Points - " << length << std::endl; 
            std::cout << food_pos[0] << " " << food_pos[1] << std::endl; 
            std::cout << "Player pos: " << snake_line << " " << snake_col << std::endl;
            std::cout << "Movement: " << movement << std::endl;
            Sleep(frame_delay);
            system("cls");
    } 
}
int main() {
    setup();
    draw();
}