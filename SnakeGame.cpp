#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;   
// x and y are coordinates of the snake head 
//fruitX and fruitY are coordinates of Fruit
int tailX[100], tailY[100];     //store the coordinates of the snake's tail segments.
int nTail;      //length of the snake
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir, originalDir;
//enum defines the possible directions snake can move
//dir stores the current direction of the snake
//originalDir stores the original direction of the snake (for pause/resume)
int delayTime = 200;    //determine speed of the game
bool paused = false;    //game pause
time_t startTime;       //starting time of the game
time_t pauseStartTime;  //starting time of the pause
time_t elapsedPauseTime = 0;    //total time game paused

void Setup()            //initialises the game and var. at start of each round
{
    gameover = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    startTime = 0;
    pauseStartTime = 0;
    elapsedPauseTime = 0;
}

void Draw()     //display game screen, snake, fruit, score, time...
{
    system("cls");      //clear console screen
    for (int i = 0; i < width + 2; i++)
    {
        cout << "_";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "|";
            }
            if (i == y && j == x)
            {
                cout << "O";    //Snake head is represented by 'O'
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "*";    //Fruit is represented by '*'
            }
            else
            {
                bool printTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";    //Snake tails are represented by 'o'
                        printTail = true;
                    }
                }
                if (!printTail)
                {
                    cout << " ";
                }
            }
            if (j == width - 1)
            {
                cout << "|";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "_";
    }
    cout << endl;

    cout << "Score :" << score << endl;

    if (!paused)
    {
        time_t currentTime = time(nullptr);
        int elapsedTime = static_cast<int>(currentTime - startTime - elapsedPauseTime);
        cout << "Time: " << elapsedTime << "s" << endl;
    }
}

void Input()    //Handles input during the game
{
    if (_kbhit())   //check if a key is pressed
    {
        int key = _getch(); // read the key
        if (key == 224) //224 means an arrow key is pressed
        {
            key = _getch();
            switch(key)
            {
                case 75:
                    if (dir != RIGHT)
                        dir = LEFT;
                    break;
                case 77:
                    if (dir != LEFT)
                        dir = RIGHT;
                    break;
                case 72:
                    if (dir != DOWN)
                        dir = UP;
                    break;
                case 80:
                    if (dir != UP)
                        dir = DOWN;
                    break;
            }
        }
        else 
        {
            switch (key)
            {
            case 'a':
                if (dir != RIGHT && dir != LEFT)
                    dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT && dir != RIGHT)
                    dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN && dir != UP)
                    dir = UP;
                break;
            case 's':
                if (dir != UP && dir != DOWN)
                    dir = DOWN;
                break;
            case 'p':   //P or p is used to pause/resume the game
            case 'P':
                if (!paused)
                {
                    paused = true;
                    pauseStartTime = time(nullptr);
                }
                else
                {
                    paused = false;
                    elapsedPauseTime += static_cast<int>(time(nullptr) - pauseStartTime);
                }
                break;
            case 'x':   //Exit the game
                gameover = true;
                break;
            }
        }
    }
}

void Logic()    //updates the game logic
{
    if (paused) //if function returns without performing any updates
        return;

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //if snake head collides with the boundary then game Over
    if (x >= width || x < 0 || y >= height || y < 0)
        gameover = true;

    for (int i = 1; i < nTail; i++)
    {
        //If snake head collides with any tail segment then Game Over
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;
    }

    //If snake head collides with fruit then score increase
    //Fruit is allocated a new position
    //tail segment increased by 1 unit
    //delay time is decreased to increase the speed
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;

        if (delayTime > 50)
            delayTime -= 10;
    }
}

int main()      //Driver Code
{
    originalDir = RIGHT;
    Setup();    //Setup function to initialise game state and enter main game loop

    while (!gameover)
    {
        if (dir != STOP && startTime == 0 && !paused)
            startTime = time(nullptr);

        Draw(); //draw function to display game screen
        Input();    //handle user input
        Logic();    //update the game logic
        Sleep(delayTime);   //intro delay between frames
    }

    system("cls");
    cout << "Game Over!" << endl;
    cout << "Score: " << score << endl;
    cout << "Time: " << static_cast<int>(time(nullptr) - startTime - elapsedPauseTime) << "s" << endl;

    return 0;
}
