#include <linux/init.h>    /* for __init, __exit*/
#include <linux/printk.h>  /* for pr_* */
#include <linux/module.h>  /* for MODULE_*, module_* */
#include <linux/device.h>  /* for class_create */
#include <linux/fs.h>      /* for fops */
#include <linux/cdev.h>    /* for cdev_* */
#include <linux/slab.h>    /* for kmalloc, kfree */
#include <linux/list.h>    /* for linked list ops*/
#include <linux/uaccess.h> /* for copy_to_user, copy_from_user access_ok */
#include <linux/mutex.h>   /* for mutex ops*/
#include "messageQ.h"

#define DO_WAITING
#define DO_LOCK

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ramy Lerner");
MODULE_DESCRIPTION("Message Queue");
MODULE_VERSION("0.1.2");

const int QUEUE_COUNT = 8;
const int MESSAGE_COUNT = 8;
const int MAX_MESSAGE_SIZE = 4096;

static int first_minor; //automaticaly initiallized to 0
static dev_t first_dev;
static struct class* my_class;
static struct cdev my_cdev;

struct message_link_t{
	int size;
	char* data;	
	struct list_head node;
};

struct mq_t{
	int numOfMessages;
	struct device* mq_dev;
	struct list_head head;
#ifdef DO_WAITING	
	wait_queue_head_t sleeping_queue;
#endif /*DO_WATING*/
#ifdef DO_LOCK
	struct mutex lock;
#endif /*DO_LOCK*/
};

static struct mq_t* buffer;


static void queue_ctor(struct mq_t* mq){
	mq -> numOfMessages = 0;	
	INIT_LIST_HEAD(&mq -> head);
#ifdef DO_WAITING	
	init_waitqueue_head (&mq -> sleeping_queue);
#endif
#ifdef DO_LOCK
	mutex_init (&mq -> lock);
#endif
}

static void queue_dtor(struct mq_t* mq){
	struct message_link_t* current_msg;
	list_for_each_entry(current_msg, &mq -> head, node){
		kfree(current_msg -> data);
		kfree(current_msg);
		//list_del(); TODO: check how to destroy a list in the kernel
	}
}

static void message_link_dtor (struct message_link_t* link){
	kfree(link -> data);
	kfree (link);
}

static int messageQ_open( struct inode *this_inode, struct file *this_file){
	int queue_number = iminor(this_inode)-MINOR(first_dev);
	struct mq_t *mq = buffer+queue_number;	
	this_file->private_data = mq;
	pr_info("%s: Finished open()\n", THIS_MODULE->name);
	return 0;
}

/*static int release_messageQ( struct inode *inode, struct file *file){
	pr_info("at release\n");
	return 0;
}*/

static int my_list_empty (struct mutex* mut, struct list_head* head){
	int ret;
#ifdef DO_LOCK	
	mutex_lock_interruptible(mut);
#endif
	ret = list_empty(head);
#ifdef DO_LOCK		
	if (ret)
		mutex_unlock(mut);
#endif
	return ret;
}

static int write_message(unsigned long user_msg, struct mq_t* mq){
	int ret;
	char* msgBuff;
	struct message_t local_msg;
	struct message_link_t *mesLink;
	
	struct message_t __user *umsgp = (struct message_t __user *)user_msg; 
	
	//copy struct message from user to local
	ret = copy_from_user(&local_msg, umsgp, sizeof(struct message_t));
	if (ret != 0) {
		pr_err("%s: Error on copy_from_user(struct message), return is %d\n", THIS_MODULE->name, ret);
		goto err_return;
	}
	pr_info("%s: local struct message created\n", THIS_MODULE->name);	
	
	//allocate message buffer
	msgBuff = (char*)kmalloc(local_msg.size, GFP_KERNEL);
	if (IS_ERR(msgBuff)) {
		pr_err("%s: Error on message buffer allocation\n", THIS_MODULE->name);
		ret = PTR_ERR(msgBuff);
		goto err_return;
	}
	pr_info("%s: Message buffer allocated in address: %p\n", THIS_MODULE->name, msgBuff);

	//copy message data to message buffer
	ret = copy_from_user(msgBuff, local_msg.data, local_msg.size);
	if (ret !=0) {
		pr_err("%s: Error on copying message data from user\n", THIS_MODULE->name);
		goto err_dealloc_buff;
	}
	pr_info("%s: Message buffer coppied from user\n", THIS_MODULE->name);

	//allocate new link for linked list	
	mesLink = (struct message_link_t*)kmalloc(sizeof(struct message_link_t), GFP_KERNEL);
	mesLink -> data = msgBuff;
	mesLink -> size = local_msg.size;+
#ifdef DO_LOCK
	mutex_lock_interruptible(&mq -> lock);
#endif
	list_add(&mesLink -> node, &mq -> head);
	mq -> numOfMessages++;
#ifdef DO_LOCK
	mutex_unlock(&mq -> lock);
#endif
	pr_info("%s: Message added succefylly\n", THIS_MODULE->name);

#ifdef DO_WAITING
	wake_up_interruptible(&mq -> sleeping_queue);
#endif
	
	return 0;

	err_dealloc_buff:
	kfree(msgBuff);

	err_return:
	return ret;
}


static int read_message(unsigned long user_msg, struct mq_t* mq){
	int  msg_size = 0;
	int ret;
	struct message_link_t* first_msg;
	void* userp = (void*)user_msg;
	
	pr_info("%s: starting read\n", THIS_MODULE->name);	
#ifdef DO_WAITING	
	ret = wait_event_interruptible (mq -> sleeping_queue, !my_list_empty (&mq -> lock, &mq -> head));
#endif
	//read first message from list
	first_msg = list_entry((&mq -> head) -> prev, struct message_link_t, node);
#ifdef DO_LOCK
	mutex_unlock(&mq -> lock);
#endif
	pr_info("%s: got first_msg\n", THIS_MODULE->name);
	//copying message to user
	pr_info("%s: willing to copy_to_user from address: %p\n", THIS_MODULE->name, first_msg->data);
	msg_size = first_msg -> size;
	ret = copy_to_user(userp, first_msg->data, first_msg->size);
	if (ret != 0){
		pr_err("%s: Failed copying to user\n", THIS_MODULE->name);
		return ret;
	}
	pr_info("%s: copied to user\n", THIS_MODULE->name);
	
#ifdef DO_LOCK
	mutex_lock_interruptible(&mq -> lock);
#endif	
	list_del((&mq -> head) -> prev);
	pr_info("%s: deleted from list\n", THIS_MODULE->name);

	message_link_dtor(first_msg);
	pr_info("%s: message link was destroyed\n", THIS_MODULE->name);
	
	mq -> numOfMessages--;
#ifdef DO_LOCK
	mutex_unlock(&mq -> lock);
#endif
	pr_info("%s: back to user space with value %d\n", THIS_MODULE->name, msg_size);
	return msg_size;
}


static long messageQ_ioctl (struct file *this_file, unsigned int op, unsigned long user_msg){
	int ret = 0;	
	struct mq_t* mq = this_file->private_data;
	pr_info("%s: in ioctl with op %u\n", THIS_MODULE->name, op);
	switch (op){
		case WRITE_MSG: /*write_msg*/
			ret = write_message(user_msg, mq);		
			break;
		case GET_MSG: /*read_msg*/
			ret = read_message(user_msg,mq);
			break;
		default:
			return -ENOTTY;
	}
	return ret;
}


static const struct file_operations messageQ_fops = {
	.owner = THIS_MODULE,
	.open = messageQ_open,
	.unlocked_ioctl = messageQ_ioctl, //ask Mark
	//.release = release_messageQ,
};


static int __init init_messageQ(void){
	
	int err =0, i=0;	

	/*allocate buffer*/	
	buffer = kmalloc(sizeof(struct mq_t)*QUEUE_COUNT, GFP_KERNEL);
	if (IS_ERR(buffer)) {
		pr_err("%s: init: failed allocating main buffer\n", THIS_MODULE->name);
		err = PTR_ERR(buffer);
		goto err_return;
	}
	

	//initiallize all queues	
	for (i=0; i<QUEUE_COUNT; i++)
		queue_ctor(buffer+i);

	err = alloc_chrdev_region(&first_dev, first_minor, QUEUE_COUNT, "messageQ");
	if (err) {
		pr_err("%s: cannot alloc_chrdev_region\n", THIS_MODULE->name);
		goto err_final;
	}


	cdev_init(&my_cdev, &messageQ_fops);
	err = cdev_add(&my_cdev, first_dev, QUEUE_COUNT);
	if (err) {
		pr_err("%s: Cannot cdev_add\n", THIS_MODULE->name);
		goto err_unregister;
	}
	pr_info("%s: Added the cdev\n", THIS_MODULE->name);


	my_class = class_create(THIS_MODULE, THIS_MODULE->name);
	if (IS_ERR(my_class)) {
		pr_err("%s: failed in class_create\n", THIS_MODULE->name);
		err = PTR_ERR(my_class);
		goto err_cdev_del;
	}
	pr_info("%s: Created the class\n", THIS_MODULE->name);	


	for (i = 0; i < QUEUE_COUNT; i++) {
		/* and now lets auto-create a /dev/ node */
		buffer[i].mq_dev = device_create(my_class, NULL,
			MKDEV(MAJOR(first_dev), MINOR(first_dev)+i),
			NULL, "%s%d", THIS_MODULE->name, i);
		if (IS_ERR(buffer[i].mq_dev)) {
			pr_err("%s: failed creating device\n", THIS_MODULE->name);
			err = PTR_ERR(buffer[i].mq_dev);
			goto err_class;
		}
	}
	pr_info("%s: created the devices\n", THIS_MODULE->name);

	
	pr_info("%s: finished loading device driver\n", THIS_MODULE->name);
	return 0;


	err_class:
	class_destroy(my_class);

	err_cdev_del:
	cdev_del(&my_cdev);	

	err_unregister:
	unregister_chrdev_region(first_dev, QUEUE_COUNT);

	err_final:
	for (i = 0; i < QUEUE_COUNT; i++)
		queue_dtor(buffer + i);
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
	pr_info(KBUILD_MODNAME "%s: exit: unloaded successfully\n", THIS_MODULE->name);
}

module_init(init_messageQ);
module_exit(exit_messageQ);
