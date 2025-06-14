#include <stdio.h>
#include <windows.h> //for sleep funtion
#include <conio.h> //for _kbhit and _getch 

void displayTime(int h, int m, int s)
 {
    printf("\r %02d: %02d: %02d", h, m, s); // \r brings the cursor to beginning
    fflush(stdout); // flush output to update same line
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
    displayTime(hours, minutes, seconds);

    while (1) {
        if (_kbhit()) //If a key is pressed, get that key and store it in the variable key so we can use
        {
            key = _getch();//(combine meaning of both functions)
            if (key == 's' || key == 'S') 
            {
                running = !running;
            } 
            else if (key == 'r' || key == 'R') 
            {
                hours = minutes = seconds = 0;
                running = 0;
                displayTime(hours, minutes, seconds);
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
            }
            if (minutes == 60) 
            {
                minutes = 0;
                hours++;
            }

            displayTime(hours, minutes, seconds);
        } 
        else
         {
            Sleep(100); // reduce CPU usage when paused....pause the execution for millisecond to update output
        }
    }

    printf("\nStopwatch exited.\n");
    return 0;
}
