package main

import (
	"net"
	"container/list"
)

type	ClientData struct {
	socket		net.Conn
	nickname	string
	ready		bool
}

type	Lobby struct {
	clientList	*list.List
}

func	main() {
	var listener	net.Listener
	var clientList	*list.List
	var lobbyList	*list.List

	listener = serverInit()
	clientList = list.New()
	lobbyList = list.New()

	go scanEntry(listener, clientList, lobbyList)
	handleServer(listener, clientList, lobbyList)
}