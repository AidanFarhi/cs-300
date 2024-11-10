package main

import "fmt"

func SelectionSort(nums []int) {
	for i := 0; i < len(nums); i++ {
		smallestIndex := i
		for j := i + 1; j < len(nums); j++ {
			if nums[j] < nums[smallestIndex] {
				smallestIndex = j
			}
		}
		temp := nums[i]
		nums[i] = nums[smallestIndex]
		nums[smallestIndex] = temp
	}
}

func InsertionSort(nums []int) {
	i, j, tmp := 0, 0, 0
	for i = 1; i < len(nums); i++ {
		j = i
		for j > 0 && nums[j] < nums[j-1] {
			tmp = nums[j]
			nums[j] = nums[j-1]
			nums[j-1] = tmp
			j--
		}
	}
}

func BinarySearch(nums []int, x int) int {
	lo := 0
	hi := len(nums) - 1
	mid := 0
	for lo <= hi {
		mid = (hi + lo) / 2
		if nums[mid] < x {
			lo = mid + 1
		} else if nums[mid] > x {
			hi = mid - 1
		} else {
			return mid
		}
	}
	return -1
}

func main() {
	data := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	x := 3
	fmt.Println("BinarySearch")
	fmt.Println(BinarySearch(data, x))

	data = []int{5, 4, 53, -232, 6, 99, 351, 3}
	fmt.Println("InsertionSort")
	InsertionSort(data)
	fmt.Println(data)

	data = []int{5, 4, 53, -232, 6, 99, 351, 3}
	fmt.Println("SelectionSort")
	SelectionSort(data)
	fmt.Println(data)
}
