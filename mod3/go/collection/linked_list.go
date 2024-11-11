package collection

import "fmt"

type Node struct {
	Data int
	Next *Node
}

func NewNode(data int) Node {
	return Node{
		Data: data,
		Next: nil,
	}
}

type LinkedList struct {
	Head *Node
	Tail *Node
	size int
}

func NewLinkedList() LinkedList {
	return LinkedList{
		Head: nil,
		Tail: nil,
		size: 0,
	}
}

func (ll LinkedList) Size() int {
	return ll.size
}

func (ll LinkedList) Display() {
	n := ll.Head
	for n != nil {
		fmt.Print(n.Data, " ")
		n = n.Next
	}
	fmt.Println()
}

func (ll *LinkedList) Prepend(data int) {
	newNode := NewNode(data)
	if ll.Head == nil {
		ll.Head = &newNode
		ll.Tail = &newNode
	} else {
		newNode.Next = ll.Head
		ll.Head = &newNode
	}
	ll.size++
}

func (ll *LinkedList) Append(data int) {
	newNode := NewNode(data)
	if ll.Tail == nil {
		ll.Head = &newNode
		ll.Tail = &newNode
	} else {
		ll.Tail.Next = &newNode
		ll.Tail = &newNode
	}
	ll.size++
}
