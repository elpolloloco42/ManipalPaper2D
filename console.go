package main

import (
	"fmt"
	"bufio"
	"os"
	"strings"
	"net"
)

func scanEntry(l net.Listener) {
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan(){
		fmt.Println("--> '" + scanner.Text() + "'")
		if (strings.Compare(scanner.Text(), "QUIT") == 0) {
			closeServer(l)
			os.Exit(1)
		}
	}
}