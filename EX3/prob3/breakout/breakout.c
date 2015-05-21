//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle
#define P_HEIGHT 10
#define P_WIDTH 100

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

    // the Edges of the bricks x and y
    #define EDG_B 6
    #define EDG_Y 75
    #define B_HEIGHT 15

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// Velocity.
#define VEL 2.0

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
char* colorChanger(int row);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    
    // initial velocity for x and y
    double YVel = VEL;
    double XVel = drand48();
    if(XVel >= .5) 
        XVel = XVel * VEL;
    else 
        XVel = XVel * -VEL;
    
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {   
        
        // Get Y Position of the paddle
        double yPadMove = getY(paddle);
               
        // get next mouse event
        GEvent mouseMoved = getNextEvent(MOUSE_EVENT);
        
        // if mouse moved
        if (mouseMoved != NULL)
        {
            // if event is movement
            if (getEventType(mouseMoved) == MOUSE_MOVED)
            {
                double xPadMove = getX(mouseMoved) - getWidth(paddle) / 2;
                setLocation(paddle, xPadMove, yPadMove);
            }
        }
        
        //detect collsion with object
        GObject object = detectCollision(window, ball);
        
        // If the ball touched an object
        if (object != NULL)
        {
            // if we hit paddle change velocity
            if ( object == paddle )
            {
                YVel = -YVel;
            }
        
            // if hit breick, disapear brick
            else if (strcmp(getType(object), "GRect") == 0)
            {
                YVel = -YVel;
                removeGWindow(window, object);   
            }
            
        }
        
        // disapear ball from bottom edge of windw and make new
        if (getY(ball) + getHeight(ball) >= HEIGHT)
        {
            removeGWindow(window, ball);
            ball = initBall(window);
            XVel = drand48();
            if(XVel >= .5) 
                XVel = XVel * VEL;
            else 
                XVel = XVel * -VEL;
            
        }

        // bounce off top edge of window
        else if (getY(ball) <= 0)
        {
            YVel = -YVel;
        }
        
         // bounce off right edge of window
        else if (getX(ball) + getWidth(ball) >= WIDTH)
        {
            XVel = -XVel;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            XVel = -XVel;
        }
        
        // move circle along the Vels
        move(ball, XVel, YVel);
        
        // linger before moving again
        pause(5);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{   
    // Make sure brick position right
    int xPos = 0;
    int yPos = EDG_Y;
    int BWidth = (WIDTH -(EDG_B * (COLS + 1)))/COLS;    
    
    //the loops that will make the actal rectangles
    // change row when you got a line with all columns
    for(int rows = 0; rows < ROWS; rows++)
    {
        //change color of each row
        char* color = colorChanger(rows);
        
        // change column every time a rectangle is generated
        for(int cols = 0; cols < COLS; cols++)
        {
            // move x position so edges don't touch
            xPos+=EDG_B;
            
            // initialize blocks
            GRect* brick = newGRect(xPos, yPos, BWidth, B_HEIGHT);
            setColor(brick, color);
            setFilled(brick, true);
            
            // add blocks to window
            add(window, brick);
            
            // add a width of the block to x position
            xPos += BWidth;
        }
        
        // set x position to initial value
        xPos = 0;
        
        // set y position 1 block height + edge
        
        yPos += EDG_B + B_HEIGHT;
        
        
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    int xBall = WIDTH/2 - RADIUS;
    int yBall = HEIGHT/2 - RADIUS;
    GOval* ball = newGOval(xBall, yBall, RADIUS * 2, RADIUS * 2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // paddle Position Coordinates
    int xPaddle = (WIDTH/2) - (P_WIDTH/2);
    int yPaddle = (HEIGHT * 7) / 8;
    GRect* paddle = newGRect(xPaddle, yPaddle, P_WIDTH, P_HEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

// Changes colors of bricks depending on the row
    char* colorChanger(int row)
    {
        // check the Modus of each row divided by six, assign value
        if(row % 6 == 0) return "RED";
        if(row % 6 == 1) return "BLUE";
        if(row % 6 == 2) return "YELLOW";
        if(row % 6 == 3) return "MAGENTA";
        if(row % 6 == 4) return "GREEN";
        if(row % 6 == 5) return "ORANGE";
        else return NULL;
    
    }
