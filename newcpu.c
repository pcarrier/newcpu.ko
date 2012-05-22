/*
 * Inspired by 
 * http://thedailywtf.com/Articles/Confessions-The-Soft-CPU-Upgrade.aspx
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/smp.h>

#define NEWCPU_MODEL_ID_LENGTH 48
#define NEWCPU_DEFAULT_NAME "HyperScale"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Change the CPU name");
MODULE_AUTHOR("Pierre Carrier <pierre@spotify.com>");

static char oldname[NEWCPU_MODEL_ID_LENGTH];
static char *newname = NEWCPU_DEFAULT_NAME;

module_param_named(name, newname, charp, S_IRUGO);
MODULE_PARM_DESC(name, "New CPU name (defaults to " NEWCPU_DEFAULT_NAME ")");

int init_module()
{
    size_t i;

    if (strlen(newname) >= NEWCPU_MODEL_ID_LENGTH)
        return (-1);

    strcpy(oldname, (&cpu_data(0))->x86_model_id);

    for (i = 0; i < nr_cpu_ids; i++)
        strcpy((&cpu_data(i))->x86_model_id, newname);

    printk("%s gone, giving room to %s!\n", oldname, newname);

    return 0;
}

void cleanup_module()
{
    size_t i;

    for (i = 0; i < nr_cpu_ids; i++)
        strcpy((&cpu_data(i))->x86_model_id, oldname);

    printk("%s gone, %s back.\n", newname, oldname);
}
