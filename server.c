/**************************************************************/
/* This program uses the Select function to control sockets   */
/**************************************************************/
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <errno.h> 
    #include <string.h> 
    #include <sys/types.h> 
    #include <netinet/in.h>  
    #include <arpa/inet.h> 
    #include <sys/socket.h> 
    #include <sys/wait.h> 
    #include <fcntl.h> // for open
    #include <unistd.h> // for close

    #define MYPORT 3456    /* the port users will be connecting to */

    #define BACKLOG 10     /* how many pending connections queue will hold */

    int main()
    {
        int             sockfd, new_fd;  /* listen on sockfd, new connection on new_fd */
        struct          sockaddr_in     my_addr;    /* my address information */
        struct          sockaddr_in     their_addr; /* connector's address information */
        int             sin_size;
        struct          timeval         timeout = {30,0};     /*The time wait for socket to be changed    */
        fd_set          readfds, writefds, exceptfds; /*File descriptors for read, write and exceptions */
        int             connection_count = 0;

        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_ZERO(&exceptfds);
    

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        my_addr.sin_family = AF_INET;         /* host byte order */
        my_addr.sin_port = htons(MYPORT);     /* short, network byte order */
        my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
        bzero(&(my_addr.sin_zero), 8);        /* zero the rest of the struct */

        if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
            perror("bind");
            exit(1);
        }

        if (listen(sockfd, BACKLOG) == -1) {
            perror("listen");
            exit(1);
        }

        while(1) {  /* main accept() loop */
            FD_SET(sockfd, &readfds);       /* Add sockfd to the set of file descriptors to read from */
            // timeout.tv_sec = 30;                 /* Initiate time to wait for fd to change */
            if (select(sockfd + 1, &readfds, 0, 0, &timeout) < 0) {
               perror("select");
               continue;
            }
            sin_size = sizeof(struct sockaddr_in);
            if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
                perror("accept");
                continue;
            }
            printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
            printf("connections served: %d\n", connection_count);
            if (send(new_fd, "Hello, world!\n", 14, 0) == -1){
                perror("send");
            }
            send(new_fd, "FIN coming..?", 13,0); // when does the FIN packet get sent? node is throwing an error
            connection_count++;
            // shutdown(new_fd,0); // is this needed? What flags to set?
            close(new_fd);

        }
    }
