package main

import (
	"net"
	"fmt"
	"os"
	"container/list"
)

type Client struct {
	socket net.Conn
}

func handleServer (l net.Listener) {
	clients := list.New()
	for {
		fmt.Printf("List length : %d\n",clients.Len())
		conn, err := l.Accept()
		if err != nil {
			fmt.Printf("Error accepting: %s\n", err.Error())
			os.Exit(1)
		}
		clients.PushBack(conn)
		go receiveConnection(conn, clients)
	}
}

func receiveConnection(conn net.Conn, clients *list.List){
	fmt.Println("New connection from " + conn.RemoteAddr().String() + ", starting listening on a thread")
	// Make a buffer to hold incoming data.
	// Read the incoming connection into the buffer.
	for {
		buf := make([]byte, 512)
		length, err := conn.Read(buf)
		if err != nil {
			fmt.Printf("Client %s disconnected\n", conn.RemoteAddr().String())
			conn.Close()
			fmt.Printf("List length : %d\n", clients.Len())
			for e := clients.Front(); e != nil; e = e.Next() {
				if conn == e.Value {
					fmt.Printf("Je l'ai trouvé, je delete\n")
					clients.Remove(e)
					break
				}
				fmt.Printf("Pas trouvé\n")
			}
			return
		}
		buf[length - 1] = '\x00'
		fmt.Printf("Received '%s'\n", buf)
		// Send a response back to person contacting us.
		conn.Write([]byte("Message received.\n"))
		// Close the connection when you're done with it.
	}
}