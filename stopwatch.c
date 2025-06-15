#include <stdio.h>
#include <windows.h> //for sleep funtion abd colors and clearing screen
#include <conio.h> //for _kbhit and _getch 

#define MAX_LAPS 10
int lapTimes[MAX_LAPS][3]; //global lap time array
int lapCount = 0; //global lap count

void display (int hours, int minutes, int seconds, int isRunning) 
{
    system("cls");// Clear the console screen

    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);//give the acces to console for changing color 


    SetConsoleTextAttribute(screen, 5);// Set color of the  title
    printf("============================\n");
    printf("      DIGITAL STOPWATCH     \n");
    printf("============================\n");

    SetConsoleTextAttribute(screen, 13); // Set color for the timer
    printf("\n          %02d:%02d:%02d\n", hours, minutes, seconds);

    SetConsoleTextAttribute(screen, 5);// Set color for the status
    if (isRunning) {
        printf("\n      Status: RUNNING\n");
    } else {
        printf("\n      Status: PAUSED\n");
    }

    SetConsoleTextAttribute(screen, 13);// Set color for the controls

    printf("\nControls: [S] Start/Stop\n          [R] Reset \n          [E] Exit\n");

    if (lapCount > 0) 
    {
        SetConsoleTextAttribute(screen, 14);
        printf("\nLap Times:\n");
        for (int i = 0; i < lapCount; i++)
         {
            printf("Lap %d: %02d:%02d:%02d\n", i + 1, lapTimes[i][0], lapTimes[i][1], lapTimes[i][2]); //lap times
        }
    }
}

int main() 
{
    int hours = 0, minutes = 0, seconds = 0;
    int running = 0;
    char key; //stores which key u are using

    printf("Digital Stopwatch\n");
    printf("Press:\n");
    printf("S = Start/Stop\n");
    printf("R = Reset\n");
    printf("E = Exit\n\n");
    display(hours, minutes, seconds, running);

    while (1) {
        if (_kbhit()) //If a key is pressed, get that key and store it in the variable key so we can use
        {
            key = _getch();//(combine meaning of both functions)
            if (key == 's' || key == 'S') 
            {
                running = !running;
                display(hours, minutes, seconds, running);
            } 
            else if (key == 'r' || key == 'R') 
            {
                hours = minutes = seconds = 0;
                running = 0;
                lapCount = 0;
                display(hours, minutes, seconds, running);
            }
            else if (key == 'l' || key == 'L') 
            {
                if (lapCount < MAX_LAPS) {
                    lapTimes[lapCount][0] = hours;
                    lapTimes[lapCount][1] = minutes;
                    lapTimes[lapCount][2] = seconds;
                    lapCount++;
                }
            }
             else if (key == 'e' || key == 'E') 
             {
                break;
            }
        }

        if (running)
         {
            Sleep(1000); // wait for 1 second
            seconds++;

            if (seconds == 60) 
            {
                seconds = 0;
                minutes++;
                Beep(750, 100); //beep every minute
            }
            if (minutes == 60) 
            {
                minutes = 0;
                hours++;
                Beep(1000, 100); //beep every hour 
            }

            display(hours, minutes, seconds, running);
        } 
        else
         {
            Sleep(100); // reduce CPU usage when paused....pause the execution for millisecond to update output
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Reset color

    printf("\nStopwatch exited.\n");
    return 0;
}
