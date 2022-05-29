/******************************** INCLUDE FILES *******************************/
#include "zhelpers.h"


/******************************** LOCAL DEFINES *******************************/
#define BE_SOCKET_PATH "ipc:///tmp/be.sock"
#define STREAM_ID      "10001"

/************************************* MAIN ***********************************/
int main (int argc, char *argv [])
{
    int stream_id = 0;
    int data0 = 0;
    int data1 = 0;

    void *context = NULL;
    void *subscriber = NULL;
    int rc = -1;

    //  Socket to talk to server
    printf ("Collecting updates from weather server...\n");
    context = zmq_ctx_new ();
    subscriber = zmq_socket (context, ZMQ_SUB);
    rc = zmq_connect (subscriber, BE_SOCKET_PATH);
    assert (rc == 0);

    //  Subscribe to stream_id
    const char *stream_filter = STREAM_ID;
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,
                         stream_filter, strlen (stream_filter));
    assert (rc == 0);

    //  Process update
    char *string = s_recv (subscriber);

    sscanf (string, "%d %d %d", &stream_id, &data0, &data1);
    free (string);

    printf ("stream_id '%s', Data0 %d, Data1 %d\n",
             stream_filter, data0, data1);

    zmq_close (subscriber);
    zmq_ctx_destroy (context);

    return 0;
}
