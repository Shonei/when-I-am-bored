package main

import (
	"log"
	"net/http"
)

func serve(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "server-client-dev-setup\\text.txt")
}

func main() {
	// fs := http.FileServer(http.Dir("server-client-dev-setup"))
	http.HandleFunc("/", serve)
	// fs := http.FileServer(http.Dir("app\\build"))
	// http.Handle("/", fs)
	log.Println("Listening...")
	http.ListenAndServe(":3000", nil)
}
