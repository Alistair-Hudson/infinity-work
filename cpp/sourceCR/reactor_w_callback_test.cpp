#include <sys/socket.h> 
#include <sys/types.h>
#include <netdb.h> 
#include <netinet/in.h> 

#include "reactor_w_callback.hpp"

#define PORT (8080)

/****GLOBAL VARIABLES****/
static struct timeval TIMEOUT = {7, 0};
Reactor reactor(new TestListen);

/****FUNCTORS*****/

/****ClASSES*****/
class TestListen: public IListener
{
public:
    TestListen(){}
    ~TestListen(){}
    void Listen(const std::vector<Handle>& read,
                const std::vector<Handle>& write,
                const std::vector<Handle>& exception)
    {
        int read_count = read.size();
        int write_count = write.size();
        int excep_count = exception.size();
        
        //set file descriptors into each of the fd sets
        fd_set* read_set = new fd_set[read_count];
        for (int i = 0; i < read_count; ++i)
        {
            FD_SET(i, read_set)
        }
        fd_set* write_set = new fd_set[write_count];
        for (int i = 0; i < write_count; ++i)
        {
            FD_SET(i, write_set)
        }
        fd_set* excep_set = new fd_set[excep_count];
        for (int i = 0; i < excep_count; ++i)
        {
            FD_SET(i, excep_set)
        }
        int max_fd = read_count > write_count ? read_count : write_count;
        max_fd = max_fd > excep_count ? max_fd : excep_count;

        //see which fds are active
        int activeEvents = select(max_fd + 1,
                                read_set, write_set, excep_set, &TIMEOUT);

        if(0 > activeEvents)
        {
            std::cout << "Select Error" << std::endl;
        }
        else if(0 == activeEvents)
        {
            std::cout << "Listening Time out" << std::endl;
        }
        else
        {
            //add read to output
            for (int fd = 0; fd < read_count; ++fd)
            {
                if(!FD_ISSET(fd, read_set))
                {
                    read.at(fd) = NULL;
                }
            }
            //add write to output
            for (int fd = 0; fd < write_count; ++fd)
            {
                if(!FD_ISSET(fd, write_set))
                {
                    write.at(fd) = NULL;
                }
            }
            //add exception to output
            for (int fd = 0; fd < excep_count; ++fd)
            {
                if(!FD_ISSET(fd, excep_set))
                {
                    exception.at(fd) = NULL;
                }
            }

        }
        delete[] read_set;
        delete[] write_set;
        delete[] excep_set;
        TIMEOUT.tv_sec = 7;
    }
private:
};

/******FUNCTIONS****/
void TestFoo(int);
void TestBar(int);

void TestFoo(int fd)
{
    std::cout << "Foo activated" << std::endl;
    int connection_id = accept(fd, NULL, 0); 
    if (connection_id < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    }
    reactor.Add(std::make_pair(READ, connection_id), TestBar);
}

void TestBar(int fd)
{
    std::cout << "Bar activated" << std::endl;
}

int main()
{
    //TestListen listen();
    

    int socket_id;
    int connection_id;
    unsigned int length; 
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr; 
  
    socket_id = socket(AF_INET, SOCK_STREAM, 0); 
    if (socket_id == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    
    bzero(&server_addr, sizeof(server_addr)); 

    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_addr.sin_port = htons(PORT); 
  
    if ((bind(socket_id, (struct sockaddr*)&server_addr, sizeof(server_addr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 

    if ((listen(socket_id, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 

    length = sizeof(client_addr); 
   


    reactor.Add(std::make_pair(READ, socket_id), TestFoo);
    

    reactor.Run();

    return 0;
}