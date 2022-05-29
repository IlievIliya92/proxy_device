/*
 *  Proxy front/back end XSUB/XPUB pattern.
 */
package main

import (
	zmq "github.com/pebbe/zmq4"
	"fmt"
	"log"
)

func main() {
	/* This is where our server sits */
	const fe_socket_path = "ipc:///tmp/fe.sock"
	const be_socket_path = "ipc:///tmp/be.sock"

	frontend, _ := zmq.NewSocket(zmq.XSUB)
	defer frontend.Close()
	frontend.Connect(fe_socket_path)

	/* This is our public endpoint for subscribers */
	backend, _ := zmq.NewSocket(zmq.XPUB)
	defer backend.Close()
	backend.Bind(be_socket_path)

	fmt.Printf("Proxy sub: %s pub: %s)\n", fe_socket_path, be_socket_path)
	fmt.Printf("Starting proxy ...\n")

	/* Run the proxy until the user interrupts us */
	err := zmq.Proxy(frontend, backend, nil)

	log.Fatalln("Proxy interrupted:", err)
}
