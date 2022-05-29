/*
 *  Update server.
 *  Binds PUB socket to ipc socket
 *  Publishes random data updates
 */

package main

import (
	zmq "github.com/pebbe/zmq4"
	"fmt"
	"math/rand"
	"time"
)

func main() {
	/*  Prepare our publisher */
	const fe_socket_path = "ipc:///tmp/fe.sock"
	publisher, _ := zmq.NewSocket(zmq.PUB)
	defer publisher.Close()
	publisher.Bind(fe_socket_path)

	fmt.Printf("Server bind on: %s\n", fe_socket_path)
	fmt.Printf("Starting server ...\n")

	/* Initialize random number generator */
	rand.Seed(time.Now().UnixNano())
	/* loop for a while apparently */
	for {

		// Get values that will fool the boss
		stream_id := rand.Intn(10000)
		Sample0 := rand.Intn(215) - 80
		Sample1 := rand.Intn(50) + 10

		/*  Send message to all subscribers */
		msg := fmt.Sprintf("%d %d %d", stream_id, Sample0, Sample1)

		publisher.Send(msg, 0)
	}
}
