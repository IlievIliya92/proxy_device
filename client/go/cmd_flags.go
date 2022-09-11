package main

import (
  "flag"
  "fmt"
  "os"
)

// Define the flag
var help = flag.Bool("help", false, "Show help")
var ipv4 = "127.0.0.1"
var port int = 9080
var n_threads int = 1

func main() {
  // Bind the flag
	flag.StringVar(&ipv4, "ipv4", "127.0.0.1", "Server IPv4 address")
	flag.IntVar(&port, "port", 9080, "Server port number")
	flag.IntVar(&n_threads, "n_threads", 1, "Number of client threads")

  // Parse the flag
  flag.Parse()

  // Usage Demo
  if *help {
		flag.Usage()
		os.Exit(0)
	}

	fmt.Println("Server address:", ipv4, ":", port)
	fmt.Println("Client Threads:", n_threads)
}
