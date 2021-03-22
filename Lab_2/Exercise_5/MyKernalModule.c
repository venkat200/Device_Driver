#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>


MODULE_LICENSE("My Module");
MODULE_AUTHOR("Venkat");

// declaration of static variable
static short int short_type_variable = 1;
static int int_type_variable = 100;
static long int long_type_variable = 10000;
static char *string_type_variable = "Hi, How are you !!";
static int int_type_array[2] = {-100, 100};
static int array_argument = 2;


// module_param(name, datatype, permission_bits) used for exposing parameters in sysfs
module_param(short_type_variable, short, S_IRUSR | S_IWUSR| S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(short_type_variable, "A short interger");

module_param(int_type_variable, int, S_IRUSR | S_IWUSR| S_IRGRP | S_IROTH);
MODULE_PARM_DESC(int_type_variable, "An integer");

module_param(long_type_variable, long, S_IRUSR);
MODULE_PARM_DESC(long_type_variable, "A long interger");

module_param(string_type_variable, charp, 0000);
MODULE_PARM_DESC(string_type_variable, "A character string");

// module_param_array(name, datatype, pointer_to_variable_to_store_array_size_initialized, permission_bits)
module_param_array(int_type_array, int, &array_argument, 0000);
MODULE_PARM_DESC(int_type_array, "An integer arrayr");

// init function
static int __init MyKernalModule_init(void)
{
    printk(KERN_INFO "Hello Kernal, This is my kernal module :) \n");
    printk(KERN_INFO "short_type_variable is a short integer = %hd \n", short_type_variable);
    printk(KERN_INFO "int_type_variable is a integer         = %d \n", int_type_variable);
    printk(KERN_INFO "long_type_variable is a long integer   = %ld \n", long_type_variable);
    printk(KERN_INFO "string_type_variable is a string       = %s \n", string_type_variable);

    int index;
    for(index=0; index<( sizeof(int_type_array) / sizeof(int) ); index++)
    {
        printk(KERN_INFO "int_type_array[%d] = %d \n", index, int_type_array[index]);
    }
    
    printk(KERN_INFO "int_type_array array got %d arguments\n", array_argument);
    return 0;  
}

// exit function
static void __exit MyKernalModule_exit(void)
{
    printk(KERN_INFO "Goodbye Kernal, will meet you again !! \n");
}

module_init(MyKernalModule_init);
module_exit(MyKernalModule_exit);