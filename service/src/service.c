/******************************** INCLUDE FILES *******************************/
#include <unistd.h>
#include <assert.h>

#include "zhelpers.h"

#include "service.h"

/******************************** LOCAL DEFINES *******************************/
#define MAX_SOCKET_PATH_SIZE 255
#define MTU 9000

/*********************************** TYPEDEFS *********************************/
//  Structure of our class

struct _service_t {
    void *context;
    char socket_path[MAX_SOCKET_PATH_SIZE];
};

/****************************** LOCAL FUNCTIONS *******************************/


/*********************************** METHODS **********************************/

//  --------------------------------------------------------------------------
// Constructor

service_t *
service_new (const char *socket_path)
{
    int rc = -1;

    service_t *self = (service_t *) malloc (sizeof (service_t));
    assert (self);

    self->context = zmq_ctx_new();
    strcpy(self->socket_path, socket_path);

    return self;
}


//  --------------------------------------------------------------------------
// Destructor

void
service_destroy(service_t **self_p)
{
    assert (self_p);

    if (*self_p) {
        service_t *self = *self_p;

        zmq_ctx_destroy (self->context);
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

void service_connection_cb(int conn, void *args)
{
    int rc = -1;
    int bytes = 0;
    void *subscriber = NULL;
    service_t *_service_ctx = NULL;

    char rx_buff[MTU];
    char tx_buff[MTU];

    _service_ctx = (service_t *)args;

    bytes = read(conn, rx_buff, MTU);
    if (bytes > 0)
    {
        /*
         * We are currently passing just the stream ID
         * A simple application protocol should be
         * implemented.
         */
        fprintf(stdout, "Stream ID: %s\n", rx_buff);

        subscriber = zmq_socket (_service_ctx->context, ZMQ_SUB);
        rc = zmq_connect (subscriber, _service_ctx->socket_path);
        if (rc != 0)
        {
            fprintf(stderr, "Connect to %s failed (%s)", _service_ctx->socket_path,
                                                         zmq_strerror(zmq_errno()));
            return;
        }

        rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,
                             rx_buff, strlen (rx_buff));
        if (rc != 0)
        {
            fprintf(stdout, "setsockopt failed");
            return;
        }
        bytes = zmq_recv(subscriber, tx_buff, MTU - 1, 0);
        zmq_close(subscriber);

        write(conn, tx_buff, bytes);
    }
}

