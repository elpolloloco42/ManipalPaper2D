package main

import (
	"net"
	"container/list"
	"fmt"
)

func	addClientInList(socket net.Conn, clientList *list.List) *ClientData {
	newClient := new(ClientData)
	newClient.socket = socket
	clientList.PushBack(newClient)

	return newClient
}

func	deleteClientFromList(client *ClientData, clientList *list.List, lobbyList *list.List) {
	lobbyList = lobbyList
	fmt.Printf("Client %s disconnected\n", client.socket.RemoteAddr().String())
	client.socket.Close()
	for e := clientList.Front(); e != nil; e = e.Next() {
		if client == e.Value {
			clientList.Remove(e)
			fmt.Printf("Client found and deleted\n")
			fmt.Printf("Players remaining : %d\n", clientList.Len())
			return
		}
	}
	fmt.Printf("ERROR : COULD NOT DELETE CLIENT FROM THE LIST\n")
}
