#include <linux/init.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ramy Lerner");
MODULE_DESCRIPTION("My own null/dev");
MODULE_VERSION("0.1.2");

const int MINOR_COUNT = 1;

static dev_t first_dev;
static struct class* my_class;
static struct device* my_device;
static struct cdev my_cdev;


static int open_myNull( struct inode *inode, struct file *file){
	pr_info("at open\n");
	return 0;
}

static ssize_t write_myNull(struct file *file, const char __user *buf, size_t count,
		loff_t *ppos)
{
	pr_info("at read!\n");	
	return count;
}

static int release_myNull( struct inode *inode, struct file *file){
	pr_info("at release\n");
	return 0;
}

static const struct file_operations myNull_fops = {
	.owner = THIS_MODULE,
	.open = open_myNull,
	.write = write_myNull,
	.release = release_myNull,
};

static int __init init_myNULL(void){
	
	int err =0 ;
	pr_info("at init_myNull()\n");
	err = alloc_chrdev_region(&first_dev, 0, MINOR_COUNT, "myNull");
	if (err) {
		pr_err("cannot alloc_chrdev_region\n");
		goto err_final;
	}

	my_class = class_create(THIS_MODULE, THIS_MODULE->name);
	if (IS_ERR(my_class)) {
		pr_err("failed in class_create\n");
		err = PTR_ERR(my_class);
		goto err_dealloc;
	}
	pr_info("created the class\n");	

	my_device = device_create(my_class,
				  /*parent*/ NULL,
				  /*dev_t major+minor*/ first_dev,
				  NULL, "%s",
				  THIS_MODULE->name);
	if (IS_ERR(my_device)) {
		pr_err("failed in device_create\n");
		err = PTR_ERR(my_device);
		goto err_class;
	}
	pr_info("created the device\n");

	cdev_init(&my_cdev, &myNull_fops);
	err = cdev_add(&my_cdev, first_dev, MINOR_COUNT);
	if (err) {
		pr_err("cannot cdev_add\n");
		goto err_device;
	}

	pr_info("finished loading device driver\n");
	return 0;

	err_device:
	device_destroy(my_class, first_dev);	

	err_class:
	class_destroy(my_class);

	err_dealloc:
	unregister_chrdev_region(first_dev, MINOR_COUNT);

	err_final:
	return err;
}

static void __exit exit_myNull(void){
	device_destroy(my_class, first_dev);
	class_destroy(my_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(first_dev, MINOR_COUNT);
	pr_info("exit completed\n");
}

module_init(init_myNULL);
module_exit(exit_myNull);
