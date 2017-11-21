/*accept返回前连接终止
这里，三路握手完成从连接建立以后，客户TCP却发送了一个RST（复位）。在服务器端看来。就在该连接已由TCP排队，等着服务器进程调用accept的时候RST到达。稍后，服务器进程调用accept.
但是，如何处理中这终止的连接依赖于不同的实现。大多数SVR4实现返回一个ERPOTO的errno值，而POSIX指出返回的errno值必须是ECONNABORTED（软件引起的连接终止）
当我们键入another line 时，str)cli调用writen,客户TCP接着把数据发送给服务器。TCP允许这么做，因为客户TCP接收到FIN知识表示服务器进程已关闭了链接的服务器端，从而不再往其中发送任何数据而已。FIN的接收并没有告知客户TCP服务器进程已经终止
当服务器TCP接收到来自客户的数据时，既然先前打开那个套接字的进程已经终止，于是相应一个RST。通过使用tcpdump来观察分组，我们可以验证该RST确实发送了。
然而客户进程看不到这个RST，因为它在调用writen后立即调用readline,并且由于第二步接收的FIN，所调用的readline立即返回0（表示EOF）。我们的客户此时未收到EOF，于是以出错信息退出
当客户终止时，它所有打开着的描述符都被关闭。

SIGPIPE信号
但一个进程向某个已收到RST的套接字执行写操作时，内核向该进程发送一个SIGPIPE信号。该信号的默认行为是终止进程，因此进程必须捕获它一面不情愿地被终止
不论进程是捕获了该信从信号处理函数返回，还是简单第胡略该信号，写操作都将放回EPIPE错误
