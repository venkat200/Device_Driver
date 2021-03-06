#include <sys/utsname.h>
#include <stdio.h>

void main()
{
    struct utsname uname_pointer;
    
    uname(&uname_pointer);

    printf("System Name : %s \n", uname_pointer.sysname);
    printf("Node Name   : %s \n", uname_pointer.nodename);
    printf("Release     : %s \n", uname_pointer.release);
    printf("Version     : %s \n", uname_pointer.version);
    printf("Machine     : %s \n", uname_pointer.machine);
}