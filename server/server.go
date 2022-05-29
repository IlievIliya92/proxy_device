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
	publisher, _ := zmq.NewSocket(zmq.PUB)
	defer publisher.Close()
	publisher.Bind("ipc:///tmp/fe.sock")

	/* Initialize random number generator */
	rand.Seed(time.Now().UnixNano())

	/* loop for a while apparently */
	for {

		//  Get values that will fool the boss
		zipcode := rand.Intn(100000)
		data0 := rand.Intn(215) - 80
		data1 := rand.Intn(50) + 10

		/*  Send message to all subscribers */
		msg := fmt.Sprintf("%05d %d %d", zipcode, data0, data1)

		publisher.Send(msg, 0)
	}
}
