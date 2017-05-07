/* 
 * author: hoi0714@163.com 
 * date  : 2011-10-29 
 */  
#include <linux/module.h>  
#include <linux/netlink.h>  
#include <linux/sched.h>  
#include <net/sock.h>  
#include <linux/proc_fs.h>  
#include <linux/netfilter.h>  
#include <linux/netfilter_ipv4.h>  
#include <linux/ip.h>  
#include <linux/tcp.h>  
#include <linux/icmp.h>  
#include <linux/udp.h>  
  
#define NETLINK_TEST 30  
  
/* 调试信息 */  
#define LOGMSG(fmt, arg...) \  
do{ \  
    printk("[func:%s,line:%d]: "fmt, __FUNCTION__, __LINE__, ##arg); \  
}while(0)  
/* 错误信息 */  
#define LOGERR(fmt, arg...) \  
do{ \  
    printk("[func:%s,line:%d]: "fmt, __FUNCTION__, __LINE__, ##arg); \  
}while(0)  
/* 断言 */  
#define ASSERT(expr) \  
if (unlikely(!(expr))) { \  
    printk("Assertion failed! %s,%s,%s,line=%d\n", \  
    #expr, __FILE__, __func__, __LINE__); \  
}  
/* 消息最大值 */  
#define MAX_MSG_LEN 1024  
enum{  
    NLMSG_TYPE_NONE = 0,  
    NLMSG_TYPE_SETPID,  /* 设置PID */  
    NLMSG_TYPE_KERNEL,  /* 消息来自内核 */  
    NLMSG_TYPE_APP,     /* 消息来自应用层 */  
};  
struct nlmsg{  
    int type;               /* 消息类型 */  
    int len;                /* 消息长度，包括头部 */  
    char msg[MAX_MSG_LEN];  /* 消息正文 */  
};  
/* netlink socket */  
static struct sock *g_nl_sk = NULL;  
static int g_nlpid = -1;    /* 应用层接收程序PID */  
  
/* 
 * 发送整个从ip头开始的skb数据到应用层 
 *  
 * param[in]: sk, skb发送目的socket 
 * param[in]: skb, 待发送的skb 
 * return -1, 失败; 0, 成功 
 * */  
int nl_sendskb(struct sock *sk, struct sk_buff *skb)  
{  
    struct iphdr *iph = NULL;  
    struct nlmsghdr *nlh = NULL;  
    struct sk_buff *nl_skb = NULL;  
  
    int skb_len = 0;  
  
    ASSERT(skb != NULL);  
    ASSERT(sk != NULL);  
    if(g_nlpid < 0)  
        return 0;  
  
    iph = ip_hdr(skb);  
    skb_len = iph->tot_len;  
    /* NLMSG_SPACE: sizeof(struct nlmsghdr) + len按4字节对齐 */  
    nl_skb = alloc_skb(NLMSG_SPACE(skb_len), GFP_ATOMIC);  
    if(!nl_skb)  
    {  
        LOGERR("nl_skb == NULL, failed!\n");  
        return -1;  
    }  
    /* 
     * static inline struct nlmsghdr *nlmsg_put(struct sk_buff *skb, u32 pid, u32 seq, 
     *               int type, int payload, int flags); 
     * 设置skb->tail指针指向skb->data + sizeof(struct nlmsghdr) + payload 
     * skb->len = sizeof(struct nlmsghdr) + payload  
     */  
    nlh = nlmsg_put(nl_skb, 0, 0, 0, NLMSG_SPACE(skb_len) - sizeof(struct nlmsghdr), 0);   
    NETLINK_CB(nl_skb).pid = 0; /* 0代表数据来自内核 */  
    memcpy(NLMSG_DATA(nlh), (char *)iph, htons(iph->tot_len));  
    /* 将数据发送给进程号22345的进程 */  
    return netlink_unicast(sk, nl_skb, g_nlpid , MSG_DONTWAIT);  
}  
/* 
 * 发送字符串到应用层 
 * 
 * param[in]: sk, 数据发往的socket 
 * param[in]: pmsg, 待发送字符串 
 * param[in]: msglen, 待发送字符串长度 
 *  
 * return: -1, 失败; 0, 成功 
 * */  
int nl_sendmsg(struct sock *sk, struct nlmsg *pmsg)  
{  
    struct nlmsghdr *nlh = NULL;  
    struct sk_buff *nl_skb = NULL;  
    int msglen = pmsg->len;  
  
    ASSERT(pmsg != NULL);  
    ASSERT(sk != NULL);  
  
    if(g_nlpid < 0)  
        return 0;  
    nl_skb = alloc_skb(NLMSG_SPACE(msglen), GFP_ATOMIC);  
    if(!nl_skb)  
    {  
        LOGERR("nl_skb == NULL, msglen = %d, failed!\n", msglen);  
        return -1;  
    }  
  
    nlh = nlmsg_put(nl_skb, 0, 0, 0,   
                    NLMSG_SPACE(msglen) - NLMSG_HDRLEN, 0);   
    NETLINK_CB(nl_skb).pid = 0;  
    memcpy(NLMSG_DATA(nlh), pmsg, msglen);  
  
    return netlink_unicast(sk, nl_skb, g_nlpid , MSG_DONTWAIT);  
}  
/*  
 * 从应用层接收数据, netlink_kernel_create注册的回调 
 * param[in]: skb, 包含netlink数据的skb 
 * 
 * skb常用操作函数 
 * skb_put : skb->tail += len, skb->len += len 
 * skb_pull: skb->data += len, skb->len -= len 
 * skb_push: skb->data -= len, skb->len += len 
 */  
static void nl_recvmsg(struct sk_buff *skb)  
{  
    struct nlmsg *pmsg = NULL;  
    struct nlmsghdr *nlh = NULL;  
    uint32_t rlen = 0;  
      
    while(skb->len >= NLMSG_SPACE(0))  
    {  
        nlh = nlmsg_hdr(skb);  
        if(nlh->nlmsg_len < sizeof(*nlh) || skb->len < nlh->nlmsg_len)  
            return;  
        rlen = NLMSG_ALIGN(nlh->nlmsg_len);  
        if(rlen > skb->len)  
            rlen = skb->len;  
        pmsg = (struct nlmsg*)NLMSG_DATA(nlh);  
        switch(pmsg->type)  
        {  
        case NLMSG_TYPE_SETPID:  
            g_nlpid = nlh->nlmsg_pid;  
            LOGMSG("pid: %d\n", g_nlpid);  
            LOGMSG("msg: %s\n", pmsg->msg);  
            break;  
        case NLMSG_TYPE_KERNEL:  
            break;  
        case NLMSG_TYPE_APP:  
            break;  
        }  
        /* 获取下一条netlink消息 */  
        skb_pull(skb, rlen);  
    }  
}  
  
/*  
 * netfilter PRE_ROUTING钩子 
 * */  
unsigned int pre_routing_hook(unsigned int hooknum,   
                           struct sk_buff *skb,   
                           const struct net_device *in,  
                           const struct net_device *out,  
                           int (*okfn)(struct sk_buff *))  
{  
    char *psend = "msg for kernel";  
    struct nlmsg msg;  
    int ret = 0;  
  
    msg.type = NLMSG_TYPE_KERNEL;  
    msg.len = strlen(psend) + offsetof(struct nlmsg, msg) + 1;  
    memcpy(msg.msg, psend, msg.len);  
    //ret = nl_sendskb(g_nl_sk, skb);  
    ret = nl_sendmsg(g_nl_sk, &msg);  
    //LOGMSG("ok\n");  
    return NF_ACCEPT;  
}  
  
static struct nf_hook_ops local_in_ops __read_mostly = {  
    .hook = pre_routing_hook,  
    .owner = THIS_MODULE,  
    .pf = PF_INET,  
    .hooknum = NF_INET_PRE_ROUTING,  
    .priority = NF_IP_PRI_FIRST  
};  
  
static int __init nl_init(void)  
{  
    int ret = 0;  
    /*  
     * struct sock *netlink_kernel_create(struct net *net, int unit, unsigned int groups, 
     *                                    void (*input)(struct sk_buff *skb), 
     *                                    struct mutex *cb_mutex, struct module *module) 
     */  
    g_nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST, 0, nl_recvmsg, NULL, THIS_MODULE);  
    if (!g_nl_sk) {  
        LOGERR("Fail to create netlink socket.\n");  
        return -1;  
    }  
  
    ret = nf_register_hook(&local_in_ops);  
    if(ret < 0)  
    {  
        LOGMSG("nf_register_hook failed!\n");  
        goto sock_release;  
    }  
    LOGMSG("ok!\n");  
    return 0;  
  
sock_release:  
    if(g_nl_sk)  
        sock_release(g_nl_sk->sk_socket);  
    return -1;  
}  
  
static void __exit nl_exit(void)  
{  
    synchronize_sched();  
    if(g_nl_sk)  
        sock_release(g_nl_sk->sk_socket);  
    nf_unregister_hook(&local_in_ops);  
    LOGMSG("ok!\n");  
}  
  
module_init(nl_init);  
module_exit(nl_exit);  
MODULE_LICENSE("GPL");  
MODULE_AUTHOR("hoi0714@163.com");  
