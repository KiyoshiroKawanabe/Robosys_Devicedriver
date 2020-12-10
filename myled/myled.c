#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

#define num 3

MODULE_AUTHOR("Ryuichi Ueda and Kiyoshiro Kawanabe");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;
static int list[num] = {25, 22, 23};  //{赤LED,青LED,スピーカ}

static ssize_t led_write (struct file* filp, const char* buf, size_t count, loff_t* pos)
{
    char c;
    int t = 0, k = 0, s = 0;

    if(copy_from_user(&c,buf,sizeof(char)))
        return -EFAULT;

    if(c == 'a'){
        while(s<3){
            k = 0;
            while(k<4){
                gpio_base[10] = 1 << list[0];
                gpio_base[7] = 1 << list[1];
                gpio_base[7] = 1 << list[2];
                msleep(200);
                gpio_base[10] = 1 << list[0];
                gpio_base[7] = 1 << list[1];
                gpio_base[10] = 1 << list[2];
                msleep(200);
                gpio_base[10] = 1 << list[0];
                gpio_base[7] = 1 << list[1];
                gpio_base[7] = 1 << list[2];
                msleep(200);
                gpio_base[10] = 1 << list[0];
                gpio_base[7] = 1 << list[1];
                gpio_base[10] = 1 << list[2];
                ssleep(1);
                k++;
            }
            gpio_base[10] = 1 << list[0];
            gpio_base[7] = 1 << list[1];
            gpio_base[7] = 1 << list[2];
            msleep(200);
            gpio_base[10] = 1 << list[1];
            gpio_base[10] = 1 << list[2];
            t = 0;
            while(t < 9){
                gpio_base[7] = 1 << list[1];
                msleep(300);
                gpio_base[10] = 1 << list[1];
                msleep(300);
                t++;
            }
            gpio_base[7] = 1 << list[0];
            gpio_base[10] = 1 << list[1];
            ssleep(10);
            s++;
        }
        gpio_base[10] = 1 << list[0];
    }
    return 1;
}

static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos)
{
    int size = 0;
    char sushi[] = {0xF0, 0x9F, 0x8D, 0xA3, 0x0A};
    if(copy_to_user(buf+size,(const char *)sushi, sizeof(sushi))){
        printk( KERN_INFO "sushi : copy_to_user failed\n");
    return -EFAULT;
    }
    size += sizeof(sushi);
    return size;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write,
    .read = sushi_read
};

static int __init init_mod(void)
{
    int retval, i;
    retval = alloc_chrdev_region(&dev, 0, 1, "myled");
    if(retval < 0){
        printk(KERN_ERR "alloc_chrdev_region failed.\n");
        return retval;
    }
    printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

    cdev_init(&cdv, &led_fops);
    retval = cdev_add(&cdv, dev, 1);
    if(retval < 0){
        printk(KERN_ERR "cdev_add faild. major:%d, minor:%d\n",MAJOR(dev),MINOR(dev));
        return retval;
    }

    cls = class_create(THIS_MODULE,"myled");
    if(IS_ERR(cls)){
        printk(KERN_ERR "class_create failed.");
        return PTR_ERR(cls);
    }

    device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));

    gpio_base = ioremap_nocache(0xfe200000, 0xA0);

    for(i = 0; i < num; i++){
        const u32 led = list[i];
        const u32 index = led/10;
        const u32 shift = (led%10) * 3;
        const u32 mask = ~(0x7 << shift);
        gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
    }

    return 0;
}

static void __exit cleanup_mod(void)
{
    cdev_del(&cdv);
    device_destroy(cls, dev);
    class_destroy(cls);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
