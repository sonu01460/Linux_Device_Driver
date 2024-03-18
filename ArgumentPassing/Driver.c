/*****************************************/
/* file : driver.c
/* Author : Sonu Prajapat
/* Details : simple driver to print hello
/*****************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int valueETX , arr_valueETX[4];
char *nameETX;
int cb_valueETX =0;

module_param(valueETX, int, S_IRUSR | S_IWUSR);
module_param(nameETX, charp, S_IRUSR | S_IWUSR);
module_param_array(arr_valueETX, int, NULL, S_IRUSR | S_IWUSR);

/*********************moduel param cb*************************/
int notify_param(const char *val, const struct kernel_param *kp)
{
    int res = param_set_int(val, kp);
    if(res == 0)
    {
        printk(KERN_INFO "callback function called....\n");
        printk(KERN_INFO "new value of callback...%d\n",cb_valueETX);
        return 0;
    }
    printk(KERN_INFO "callback function called....\n");
    return -1;

}

const struct kernel_param_ops my_param_ops =
{
  .set = &notify_param,
  .get = &param_get_int, 
};

module_param_cb(cb_valueETX, &my_param_ops,&cb_valueETX,S_IRUGO|S_IWUSR );

/*****************************************************************************/

static int __init hello_init(void)
{
    printk(KERN_INFO "wellcome to device driver\n");
    printk(KERN_INFO "valueETX= %d\n",valueETX);
    printk(KERN_INFO "cb_valueETX= %d\n",cb_valueETX);
    printk(KERN_INFO "nameTX= %s\n",nameETX);
    for(int i=0;i<(sizeof(arr_valueETX)/sizeof(int));i++)
    {
        printk(KERN_INFO "arr_valueETX[%d]= %d\n",i,arr_valueETX[i]);

    }
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