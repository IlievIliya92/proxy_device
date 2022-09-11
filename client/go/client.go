package main

import (
    "math/rand"
    "strconv"
    "bufio"
    "sync"
    "flag"
    "time"
    "fmt"
    "net"
    "os"
)

// Flag definitions
var help = flag.Bool("help", false, "Show help")
var ipv4 = "127.0.0.1"
var port int = 9080
var n_threads int = 1

// WaitGroup is used to wait for the program to finish goroutines.
var wg sync.WaitGroup

func client_routine(name int, server_endpoint string) {
    // Schedule the call to WaitGroup's Done to tell goroutine is completed.
    defer wg.Done()

    con, err := net.Dial("tcp", server_endpoint)
    if err != nil {
        fmt.Println(err)
        return
    }

    var stream_id int = rand.Intn(10000 - 1) + 1
    fmt.Printf("__client_%d__ Sending request for %d ...\n", name, stream_id)
    fmt.Fprintf(con, strconv.FormatInt(int64(stream_id), 10))
    message, _ := bufio.NewReader(con).ReadString('\n')
    fmt.Printf("__client_%d__ Received: %s\n", name, message)
}

func main() {
    // Bind the flag
    flag.StringVar(&ipv4, "ipv4", "127.0.0.1", "Server IPv4 address")
    flag.IntVar(&port, "port", 9080, "Server port number")
    flag.IntVar(&n_threads, "n_threads", 1, "Number of client threads")

    // Parse cmd arguments
    flag.Parse()

    if *help {
        flag.Usage()
        os.Exit(0)
    }

    server_endpoint := fmt.Sprintf("%s:%d", ipv4, port)
    fmt.Printf("Server address: %s\n", server_endpoint)
    fmt.Printf("Client Threads: %d\n", n_threads)

    rand.Seed(time.Now().UnixNano())

    wg.Add(n_threads)
    for i := 0; i < n_threads; i++ {
        fmt.Printf("Starting client thread: %d\n", i)
        go client_routine(i, server_endpoint)
    }

    wg.Wait()
}
