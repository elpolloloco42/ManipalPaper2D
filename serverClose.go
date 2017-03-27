package main

import (
	"net"
	"fmt"
)

func closeServer (l net.Listener) {
	fmt.Print("Closing server...\n")
	l.Close()
}
