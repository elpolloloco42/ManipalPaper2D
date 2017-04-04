package main

import (
	"fmt"
	"container/list"
	"strings"
)

func	handleRequest(client *ClientData, clientList *list.List, lobbyList *list.List, request []byte, length int) {
	var code	string
	var message	string

	clientList = clientList
	lobbyList = lobbyList
	if length < 3 {
		response202(client)
		return
	}
	code = string(request[0:3])
	if length > 3 {
		message = string(request[4:length])
	}
	fmt.Printf("code '%s'\nmessage '%s'\n", code, message)
	if strings.Compare(code, "101") == 0 {
		request101(client, message)
	} else {
		response202(client)
		return
	}
}

func	request101(client *ClientData, message string) {
	if len(client.nickname) != 0 || len(message) > 8 {
		response202(client)
		return
	}
	client.nickname = message
	response201(client)
}

func	response201(client *ClientData){ //OK
	client.socket.Write([]byte("201"))
}

func	response202(client *ClientData){ //NOT OK
	client.socket.Write([]byte("202"))
}