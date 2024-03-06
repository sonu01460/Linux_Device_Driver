/*****************************************/
/* file : driver.c
/* Author : Sonu Prajapat
/* Details : simple driver to print hello
/*****************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
    printk(KERN_INFO "wellcome to device driver\n");
    printk(KERN_INFO "this device driver will print the hello\n");
    printk(KERN_INFO "kernel module inserted successfully....\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "kernel module Removed successfully...\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_VERSION("2:1.0");
MODULE_AUTHOR("Sonu Prajapat");
MODULE_DESCRIPTION("hello print driver");