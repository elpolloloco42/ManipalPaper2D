package main

import (
	"net"
	"fmt"
	"os"
)

const (
	CONN_HOST = "localhost"
	CONN_PORT = "3333"
	CONN_TYPE = "tcp"
)

func serverInit() net.Listener {
	l, err := net.Listen(CONN_TYPE, CONN_HOST+":"+CONN_PORT)
	if err != nil {
		fmt.Println("Error setting up Listener:", err.Error())
		os.Exit(1)
	}

	fmt.Println("Listening on " + CONN_HOST + ":" + CONN_PORT)
	return l
}