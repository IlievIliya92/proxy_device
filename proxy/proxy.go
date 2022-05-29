/*
 *  Proxy front/back end XSUB/XPUB pattern.
 */
package main

import (
	zmq "github.com/pebbe/zmq4"
	"log"
)

func main() {
	/* This is where our server sits */
	frontend, _ := zmq.NewSocket(zmq.XSUB)
	defer frontend.Close()
	frontend.Connect("ipc:///tmp/fe.sock")

	/* This is our public endpoint for subscribers */
	backend, _ := zmq.NewSocket(zmq.XPUB)
	defer backend.Close()
	backend.Bind("ipc:///tmp/be.sock")

	/* Run the proxy until the user interrupts us */
	err := zmq.Proxy(frontend, backend, nil)

	log.Fatalln("Proxy interrupted:", err)
}
