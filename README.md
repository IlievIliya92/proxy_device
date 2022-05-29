# TCP Proxy Service

Example implementation of a Proxy Service based on the [TCP preforked server](https://github.com/IlievIliya92/tcp_server) and ZMQ sub/pub proxy
and producer server.

## Getting Started

1. Build the project

```console
mkdir build
cd build
cmake ..
make
```

2. Start the server

```console
$ cd build/server
$ ./server
```

3. Start the proxy

```console
$ cd build/proxy
$ ./proxy
```

4. Start the service

```console
$ cd build/service
$ ./tcp_proxy_service
```

5. Run the client

```console
$ cd client
$ python3
```

## What is what

* ``client`` -- Just a test client sending some requests to our service.
* ``service`` -- TCP Proxy service. Bridge connection between TCP and proxy.
Redirects connections to proxy's public endpoint for subscribers (back end).
* ``proxy`` -- Proxy connecting front end (subscribers) and back end (publisher)
* ``server`` -- Constanty produces random data (samples) and sends
                 (publishes) them via PUB socket.
