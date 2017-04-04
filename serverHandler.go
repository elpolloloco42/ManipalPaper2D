package main

import (
	"net"
	"fmt"
	"container/list"
)

func 	handleServer(listener net.Listener, clientList *list.List, lobbyList *list.List) {
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Printf("Error accepting: %s\n", err.Error())
		} else {
		newClient := addClientInList(conn, clientList)
		go handleClient(newClient, clientList, lobbyList)
		}
	}
}

func	handleClient(client *ClientData, clientList *list.List, lobbyList *list.List){
	lobbyList = lobbyList
	fmt.Println("New connection from " + client.socket.RemoteAddr().String() + ", starting listening on a thread")
	for {
		buf := make([]byte, 512)
		length, err := client.socket.Read(buf)
		length -= 1
		fmt.Printf("length = %d\n", length)
		if err != nil || length == 0 {
			deleteClientFromList(client, clientList, lobbyList)
			return
		}
		buf[length] = '\x00'
		fmt.Printf("Received '%s'\n", buf)
		handleRequest(client, clientList, lobbyList, buf, length)
	}
}