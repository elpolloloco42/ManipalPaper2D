package main

import (
	"fmt"
	"bufio"
	"os"
	"strings"
	"net"
	"container/list"
)

func scanEntry(listener net.Listener, clientList *list.List, lobbyList *list.List) {
	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan(){
		fmt.Println("--> '" + scanner.Text() + "'")
		if strings.Compare(scanner.Text(), "QUIT") == 0 {
			closeServer(listener)
		}
	}
}

func closeServer (l net.Listener) {
	fmt.Print("Closing server...\n")
	l.Close()
	os.Exit(1)
}