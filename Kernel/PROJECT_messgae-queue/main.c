#include <linux/init.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "messageQ.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ramy Lerner");
MODULE_DESCRIPTION("Message Queue");
MODULE_VERSION("0.1.2");

const int QUEUE_COUNT = 8;
const int MESSAGE_COUNT = 8;
const size_t MESSAGE_SIZE = 4096;

static int first_minor; //automaticaly initiallized to 0
static dev_t first_dev;
static struct class* my_class;
static struct cdev my_cdev;

struct message_link_t{
	struct message_t msg;
	struct list_head node;
};

struct mq_t{
	size_t numOfMessages;
	struct device* mq_dev;
	struct list_head head;
};

static struct mq_t* buffer;

static void queue_ctor(struct mq_t* mq){
	mq -> numOfMessages = 0;	
	mq -> node = INIT_LIST_HEAD(mq -> head);
}
static void queue_dtor(struct mq_t* mq){}


/*static int open_messageQ( struct inode *inode, struct file *file){
	pr_info("at open\n");
	return 0;
}*/

/*static ssize_t write_myNull(struct file *file, const char __user *buf, size_t count,
		loff_t *ppos)
{
	pr_info("at read!\n");	
	return count;
}*/

/*static int release_messageQ( struct inode *inode, struct file *file){
	pr_info("at release\n");
	return 0;
}*/


static const struct file_operations messageQ_fops = {
	.owner = THIS_MODULE,
	//.open = open_messageQ,
	.ioctl = messageQ_ioctl,
	//.release = release_messageQ,
};




static int messageQ_ioctl (struct inode *this_inode, struct file *this_file, unsigned int op, unsigned long user_msg){
	int err;	
	int queue_number = iminor(this_inode)-MINOR(first_dev);
	struct mq_t *mq = buffer+queue_number;
	struct message_t __user *umsgp = (message_t __user *)user_msg; 

	switch (op){
		case WRITE_MSG: /*write_msg*/
			err = write_message(umsgp, mq);		
			break;
		case GET_MSG: /*read_msg*/
			read_message
	}

	return 0;

	err_return:
	return err;
}


int write_message(message_t __user *umsgp, struct mq_t* mq){
	int err;
	message_t* buff;
	struct  message_link_t *mesLink;

	buff = kmalloc(MESSAGE_SIZE, GFP_KERNEL);
	if (IS_ERR(buff)) {
		pr_err("Error on kernek buffer allocation\n");
		err = PTR_ERR(buff);
		goto err_return;
	}

	err = copy_from_user(buff, umsgp, sizof(message_t);
	if (err == 0) {
		pr_debug("Added message\n");
		newMes = kalloc(sizeof(struct  message_link_t), GFP_KERNEL);
		if (IS_ERR(newMes)) {
			pr_err("Error on newMessage allocation\n");
			err = PTR_ERR(newMes);
			goto err_dealloc_buff;
		}
		mesLink -> msg = buff;
		list_add(mesLink, mq -> head);
		mq -> numOffMessages++;
	} else {
		pr_err("Error on copy_from_user, return is %d\n",count, ret);
		goto err_dealloc_buff;
	}

	return 0;

	err_dealloc_buff:
	kfree(buff);

	err_return:
	return err;
}


static int __init init_messageQ(void){
	
	int err =0, i=0;	

	/*allocate buffer*/	
	buffer = kmalloc(sizeof(struct mq_t)*QUEUE_COUNT, GFP_KERNEL);
	if (IS_ERR(buffer)) {
		pr_err("kmalloc\n");
		err = PTR_ERR(buffer);
		goto err_return;
	}
	//list_add_tail(&buffer->node, &message_list);

	//initiallize all queues	
	for (i=0; i<QUEUE_COUNT; i++)
		queue_ctor(buffer+i);

	err = alloc_chrdev_region(&first_dev, first_minor, QUEUE_COUNT, "messageQ");
	if (err) {
		pr_err("cannot alloc_chrdev_region\n");
		goto err_final;
	}


	cdev_init(&my_cdev, &messageQ_fops);
	err = cdev_add(&my_cdev, first_dev, QUEUE_COUNT);
	if (err) {
		pr_err("Cannot cdev_add\n");
		goto err_unregister;
	}
	pr_debug("Added the cdev\n");


	my_class = class_create(THIS_MODULE, THIS_MODULE->name);
	if (IS_ERR(my_class)) {
		pr_err("failed in class_create\n");
		err = PTR_ERR(my_class);
		goto err_cdev_del;
	}
	pr_info("Created the class\n");	


	for (i = 0; i < QUEUE_COUNT; i++) {
		/* and now lets auto-create a /dev/ node */
		buffer[i].mq_dev = device_create(my_class, NULL,
			MKDEV(MAJOR(first_dev), MINOR(first_dev)+i),
			NULL, "%s%d", THIS_MODULE->name, i);
		if (IS_ERR(buffer[i].mq_dev)) {
			pr_err("device_create\n");
			err = PTR_ERR(buffer[i].mq_dev);
			goto err_class;
		}
	}
	pr_info("created the devices\n");

	
	pr_info("finished loading device driver\n");
	return 0;


	err_class:
	class_destroy(my_class);

	err_cdev_del:
	cdev_del(&my_cdev);	

	err_unregister:
	unregister_chrdev_region(first_dev, QUEUE_COUNT);

	err_final:
	for (i = 0; i < QUEUE_COUNT; i++)
		queue_dtor(buffer + i); // TO DO: queue_dtor
	kfree(buffer);

	err_return:
	return err;
}

static void __exit exit_messageQ(void){
	int i;
	for (i = 0; i < QUEUE_COUNT; i++)
		device_destroy(my_class, MKDEV (MAJOR(first_dev), MINOR(first_dev)+i));
	class_destroy(my_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(first_dev, QUEUE_COUNT);
	for (i = 0; i < QUEUE_COUNT; i++)
		queue_dtor(buffer+i);
	kfree(buffer);
	pr_info(KBUILD_MODNAME " unloaded successfully\n");
}

module_init(init_messageQ);
module_exit(exit_messageQ);
