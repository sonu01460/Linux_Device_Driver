/*****************************************/
/* file : driver.c
/* Author : Sonu Prajapat
/* Details : simple driver to print hello
/*****************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/cdev.h>

//creating custome major number
dev_t dev = 0;
static struct class *dev_class; 
static struct cdev ext_cdev;

/*function*/

static int  __init ext_driver_init(void);
static void  __exit ext_driver_exit(void);
static int ext_open(struct inode *inode, struct file *file);
static int ext_close(struct inode *inode, struct file *file);
static ssize_t ext_read(struct file *filp,char __user *buf,size_t len,loff_t *off);
static ssize_t ext_write(struct file *filp,const char *buf,size_t len,loff_t *off);

/***************************************************************************/
static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = ext_read,
    .write = ext_write,
    .open = ext_open,
    .release = ext_close,
};

static int ext_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "driver open function call \n");
    return 0;
}
static int ext_close(struct inode *inode, struct file *file)
{
   printk(KERN_INFO "driver file close function call \n");
    return 0; 
}
static ssize_t ext_read(struct file *filp,char __user *buf,size_t len,loff_t *off)
{
    printk(KERN_INFO "driver read function call \n");
    return 0;
}
static ssize_t ext_write(struct file *filp,const char *buf,size_t len,loff_t *off)
{
    printk(KERN_INFO "driver write function call \n");
    return 0;
}



static int __init hello_init(void)
{
    printk(KERN_INFO "wellcome to device driver\n");
    //allocating major number
    if(alloc_chrdev_region(&dev,0,1,"sonuPrajapatDriver")<0)
    {
        printk(KERN_INFO "can not allocate major number for device 1\n");
        return -1;
    }    
    printk(KERN_INFO "Major= %d, Minor = %d\n",MAJOR(dev),MINOR(dev));

    //creating cdev structure
    cdev_init(&ext_cdev,&fops);
    //adding char device to system
    if(cdev_add(&ext_cdev,dev,1)<0)
    {
        pr_err("can not add the device to system");
        goto r_class;
    }
    //create device

    dev_class = class_create("ext_class");
    if(IS_ERR(dev_class))
    {
        pr_err("device class not created");
        goto r_class;
    }

    if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"ext_device")))
    {
        pr_err("device not created");
        goto r_device;
    }

    printk(KERN_INFO "kernel module inserted successfully....\n");
    return 0;

    r_class:
        class_destroy(dev_class);
    r_device:
        unregister_chrdev_region(dev,1);  
    return -1;  
}

static void __exit hello_exit(void)
{
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
    cdev_del(&ext_cdev);
    unregister_chrdev_region(dev,1);
    printk(KERN_INFO "kernel module Removed successfully...\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_VERSION("2:1.0");
MODULE_AUTHOR("Sonu Prajapat");
MODULE_DESCRIPTION("hello print driver");