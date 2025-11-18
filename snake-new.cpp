#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <ncurses.h>

class SnakeGame
{
public:
    struct AppleCoordinates
    {
        int x;
        int y;
    };
    struct SnakePiece
    {
        int x;
        int y;
    };

    AppleCoordinates GenerateApple(WINDOW *win)
    {
        AppleCoordinates apple;
        srand(static_cast<unsigned>(time(0))); // seed the random number generator with the current time
        int min = 1;
        int xmax = 59;
        int ymax = 29;
        apple.x = min + rand() % (xmax - min + 1);
        apple.y = min + rand() % (ymax - min + 1);
        return apple;
    }

    void DrawInitialField(AppleCoordinates a, std::vector<SnakePiece> snake, WINDOW *win, int lx, int ly)
    {
        box(win, 0, 0);
        mvwprintw(win, a.y, a.y, "ò"); // mv the cursor to the apple position and draw it
        wrefresh(win);                 // refresh to show the apple
        for (int i = 0; i < snake.size(); i++)
        {
            mvwprintw(win, snake[i].y, snake[i].x, "#"); // draw each piece of the snake
            wrefresh(win);                               // refresh to show the snake piece
        }
    }

    void UpdateApplePosition(WINDOW *win)
    {
        // the previous apple will be erased by the head of the snake
        // so we just need to draw the new one in an updated position
        AppleCoordinates newApple = GenerateApple(win);
        mvwprintw(win, newApple.y, newApple.x, "ò");
        wrefresh(win);
    }

    void UpdateSnakePosition(WINDOW *win, std::vector<SnakePiece> snake, int addx, int addy)
    {
        for (int i = 0; i < snake.size() - 1; i++)
        {
            int prev_x = snake[i].x;
            int prev_y = snake[i].y;
            snake[i + 1].x = prev_x;
            snake[i + 1].y = prev_y;
            snake[i].x += addx;
            snake[i].y += addy;
        }
        for (int i = 0; i < snake.size(); i++)
        {
            mvwprintw(win, snake[i].y, snake[i].x, "#"); // draw each piece of the snake
            wrefresh(win);                               // refresh to show the snake piece
        }
    }

    void AppleEaten(std::vector<SnakePiece> snake, AppleCoordinates a)
    {
        if (snake[0].x == a.x && snake[0].y == a.y)
        {
            SnakePiece newPiece = {snake.back().x, snake.back().y};
            snake.push_back(newPiece);
        }
    }

private:
    std::vector<SnakePiece> snake; // TODO: initialize the snake

}

int
main()
{
    SnakeGame game;
    game.run();
    return 0;
}