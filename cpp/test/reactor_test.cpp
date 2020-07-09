#include <sys/socket.h> 
#include <sys/types.h>
#include <netdb.h> 
#include <netinet/in.h> 

#include "reactor.hpp"

#define PORT (8080)

static struct timeval TIMEOUT = {7, 0};

/****FUNCTORS*****/
class Count
{
public:
    Count(int* read, int* write, int* excep):m_read(read), m_write(write), m_excep(excep){}
    void operator() (const HandleAndMode& handle)
    {
        switch(handle.first)
        {
            case(READ):
                ++*m_read;
                break;
            case(WRITE):
                ++*m_write;
                break;
            case(EXCEPTION):
                ++*m_excep;
                break;
            default:
                break;
        }
    }

private:
    int* m_read;
    int* m_write;
    int* m_excep;
};

class SetSet
{
public:
    SetSet(fd_set* read, fd_set* write, fd_set* excep):m_read(read), m_write(write), m_excep(excep){}
    void operator() (const HandleAndMode& handle)
    {

        switch(handle.first)
        {
            case(READ):
                FD_SET(handle.second, m_read);
                break;
            case(WRITE):
                FD_SET(handle.second, m_write);
                break;
            case(EXCEPTION):
                FD_SET(handle.second, m_excep);
                break;
            default:
                break;
        }
    }

private:
    fd_set* m_read;
    fd_set* m_write;
    fd_set* m_excep;
};

/****ClASSES*****/
class TestListen: public IListener
{
public:
    TestListen(){}
    std::vector<HandleAndMode> Listen(const std::vector<HandleAndMode>& handle)
    {
        int read_count = 0;
        int write_count = 0;
        int excep_count = 0;
        //count the number of read, write, and exception file desscriptors
        for_each(handle.begin(), handle.end(), Count(&read_count, &write_count, &excep_count));

        fd_set* read_set = new fd_set[read_count];
        fd_set* write_set = new fd_set[write_count];
        fd_set* excep_set = new fd_set[excep_count];
        //set file descriptors into each of the fd sets
        for_each(handle.begin(), handle.end(), SetSet(read_set, write_set, excep_set));
    
        //see which fds are active
        int activeEvents = select(read_count + write_count + excep_count + 1,
                                read_set, write_set, excep_set, &TIMEOUT);

        std::vector<HandleAndMode> output;
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
                if(FD_ISSET(fd, read_set))
                {
                    output.push_back(std::make_pair(READ, fd));
                }
            }
            //add write to output
            for (int fd = 0; fd < write_count; ++fd)
            {
                if(FD_ISSET(fd, write_set))
                {
                    output.push_back(std::make_pair(WRITE, fd));
                }
            }
            //add exception to output
            for (int fd = 0; fd < excep_count; ++fd)
            {
                if(FD_ISSET(fd, excep_set))
                {
                    output.push_back(std::make_pair(EXCEPTION, fd));
                }
            }

        }
        delete[] read_set;
        delete[] write_set;
        delete[] excep_set;
        TIMEOUT.tv_sec = 7;

        return output;
    }
private:
};

Reactor reactor(new TestListen);

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