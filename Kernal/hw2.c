#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/errno.h>

#define DADDY_IN_THE_SKY 1

asmlinkage long sys_hello(void) {
 printk("Hello, World!\n");
 return 0;
}

asmlinkage long sys_set_weight(int weight){
    if(weight < 0){
        return -EINVAL;
    }
    current->weight = weight;
    return 0;
}

asmlinkage int sys_get_weight(void){
    return current->weight;
}

asmlinkage int sys_get_ancestor_sum(void){
    int weight_sum = 0;
    struct task_struct* current_parent = current;
    do{
        weight_sum += current_parent->weight;
        current_parent = current_parent->parent;
    }while(current_parent->pid != DADDY_IN_THE_SKY);
    return weight_sum;
}

asmlinkage void find_heaviest_descendant(struct task_struct *father, int* max_weight, pid_t* max_pid){
    struct task_struct* child;
    list_for_each_entry(child, &father->children, sibling){
        if(child->weight > *max_weight){
            *max_weight = child->weight;
            *max_pid = child->pid;
        }else if (child->weight == *max_weight){
            if(child->pid < *max_pid){
                *max_weight = child->weight;
                *max_pid = child->pid;
            }
        }
        find_heaviest_descendant(child, max_weight, max_pid);
    }
}

asmlinkage long sys_get_heaviest_descendant(void){
    int max_weight = -1;
    pid_t max_pid = -1;
    find_heaviest_descendant(current, &max_weight, &max_pid);
    if(max_pid == -1){
        return -ECHILD; // max pid wasnt changed so there are no children
    }else{
        return max_pid;
    }
}

