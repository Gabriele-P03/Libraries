/**
 * A MainServerSocket is an extention of MainSocket specialized as Server.
 * 
 * MainSocket constructor, for the server one, takes care only about setting and binding socket.
 * The listen and accept parts are done by this extended class  
 * 
 * Once you have created a new object of this class, the first function that you should call is setMaxQueue() in order to make the call to listen(),
 * the parameter given to setMaxQueue() is the max number of request connection that can stay in queue.
 * This function, even if it can call at all time, will modify the value of max_queue filed only one time; then you will have to take care to delete
 * and create a new one instance of it...
 * 
 * Then, you should set the flagLoop, used by the accept loop as flag, via setLoopFlag(). A true value given, is not enough to start the accept loop 
 * as a separated thread. For that, you must call startLoopAcceptThread().
 * If you wanna stop the thread, but waiting a last request connection, you can call setLoopFlag() with a false parameter; when the last request is done, 
 * the function will end up and the thread will be over (read next paragraph).
 * In order to start again it, you must set the loopFlag as true via setLoopFlag().
 * 
 * A setter has been done for clientListController to let you instance an extended class, too. Check setClientListController()
 * 
 * @date 2023-01-24
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef MAIN_SERVER_SOCKET_JPL
#define MAIN_SERVER_SOCKET_JPL



#include "../MainSocket.hpp"

#include <vector> //Vector storing client instance
#include <mutex>
#include <pthread.h>

#include <iostream>

#include "ClientListController.hpp"

#ifdef __WIN32
    /**
     * @brief 
     * 
     */
    typedef short sa_family_t;
#endif


namespace jpl{

    namespace _network{

        namespace _socket{

            extern std::string getClientIp(Client* client);

            class MainServerSocket : public MainSocket{

                private:

                    bool flagLoop;

                protected:

                    unsigned int max_queue;

                    /**
                     * It starts the accept loop.
                     * For every client which tries to enstabilish a connection with the server
                     * 
                     */
                    virtual void loopAccept();

                    /**
                     * Reading documentation of pthread, you can get that it works only with non-member function.
                     * In order to by-pass this problem, a static function with an instance of the object as parameter must be called
                     * by pthread_create. 
                     */
                    static void* startThread(void* instance);

                    pthread_t loopAccept_pthread_id;

                    ClientListController* clientListController;


                public:

                    MainServerSocket(unsigned int port);

                    MainServerSocket(unsigned int port, int domain, int type, int protocol);

                    /**
                     * Set the max connection available in queue, waiting to be accepted.
                     * It makes the call to listen().
                     *
                     * @param max_queue 
                     */
                    virtual inline void setListenQueue(unsigned int max_queue){

                        if(!this->error_occurred && this->max_queue == 0){
                            this->max_queue = max_queue;
                            int res = listen(this->socket_fd, this->max_queue);
                            if(res != 0){
                                this->overrideNewError();
                            }
                        }
                        
                    }

                    /**
                     * This is the function which make start the separated loop accept thread 
                     * 
                     * @return pthread_create returned value
                     */
                    virtual int startLoopAcceptThread();

                    bool isLoopRunning();

                    /**
                     * Change the accept loop's state
                     * 
                     * @param flag 
                     */
                    virtual void setLoopState(bool flagLoop);

                    /**
                     * 
                     * 
                     * @param clientListController 
                     */
                    void setClientListController(ClientListController* clientListController);

                    ~MainServerSocket();
            };
        }
    }
}

#endif