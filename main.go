package main

import (
	"net"
)

func main() {
	var l net.Listener

	l = serverInit()
	go scanEntry(l)
	handleServer(l)
}