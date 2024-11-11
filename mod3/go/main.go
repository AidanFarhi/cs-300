package main

import (
	"dsalgos/collection"
	"fmt"
)

func main() {
	ll := collection.NewLinkedList()
	for _, n := range []int{1, 2, 3, 4, 5} {
		ll.Prepend(n)
	}
	ll.Display()
	for _, n := range []int{1, 2, 3, 4, 5} {
		ll.Append(n)
	}
	ll.Display()
	fmt.Println(ll.Size())
}
