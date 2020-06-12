def insert_sort(A):
	""" sort list A by inserts """
	pass

def choice_sort(A):
	""" sort list A by choosing """
	pass

def bubble_sort(A):
	""" sort list A with bubble """
	pass

def test_sort(sort_algorithm):
	print("testcase #1: ", end="")
	A = [4, 2, 5, 1, 3]
	A_sorted = [1, 2, 3, 4, 5]
	sort_algorithm(A)
	print("Ok" if A == A_sorted else "Fail")

	print("testcase #2: ", end="")
	A = list(range(10, 20)) + list(range(0, 10))
	A_sorted = list(range(20))
	sort_algorithm(A)
	print("Ok" if A == A_sorted else "Fail")

	print("testcase #3: ", end="")
	A = [4, 2, 4, 2, 1]
	A_sorted = [1, 2, 2, 4, 4]
	sort_algorithm(A)
	print("Ok" if A == A_sorted else "Fail")