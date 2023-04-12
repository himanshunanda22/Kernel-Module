#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/init.h>

#include <linux/fs.h>

#include <linux/uaccess.h>



#define DEVICE_NAME "osproject"

#define BUFFER_SIZE 1024



static int major_number;

static char buffer[BUFFER_SIZE];

static int buffer_size;



static int osproject_open(struct inode *inode, struct file *file)

{

    printk(KERN_INFO "osproject: opened device file\n");

    return 0;

}



static int osproject_release(struct inode *inode, struct file *file)

{

    printk(KERN_INFO "osproject: closed device file\n");

    return 0;

}



static ssize_t osproject_read(struct file *file, char *user_buffer, size_t count, loff_t *offset)

{

    int bytes_read = 0;

    if (*offset >= buffer_size) {

        return 0;

    }

    while (count && *offset < buffer_size) {

        put_user(buffer[(*offset)++], user_buffer++);

        count--;

        bytes_read++;

    }

    return bytes_read;

}



static ssize_t osproject_write(struct file *file, const char *user_buffer, size_t count, loff_t *offset)

{

    int bytes_written = 0;

    while (count && buffer_size < BUFFER_SIZE) {

        get_user(buffer[buffer_size++], user_buffer++);

        count--;

        bytes_written++;

    }

    return bytes_written;

}



static struct file_operations osproject_fops = {

    .owner = THIS_MODULE,

    .open = osproject_open,

    .release = osproject_release,

    .read = osproject_read,

    .write = osproject_write

};



static int __init my_module_init(void)

{

    major_number = register_chrdev(0, DEVICE_NAME, &osproject_fops);

    if (major_number < 0) {

        printk(KERN_ALERT "osproject: failed to register device\n");

        return major_number;

    }

    printk(KERN_INFO "osproject: registered device with major number %d\n", major_number);

    return 0;

}



static void __exit my_module_exit(void)

{

    unregister_chrdev(major_number, DEVICE_NAME);

    printk(KERN_INFO "osproject: unregistered device\n");

}



module_init(my_module_init);

module_exit(my_module_exit);



MODULE_LICENSE("GPL");

MODULE_AUTHOR("Your name");

MODULE_DESCRIPTION("A simple example kernel module with device file");

