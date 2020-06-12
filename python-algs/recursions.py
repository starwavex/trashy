def f(n:int):
    assert n>=0, "Factorial of a negative number is undefined."
    if n==0:
        return 1
    return f(n-1)*n

def gcd(a,b):
    return (a if b==0 else gcd(b, a%b))

def poww(a:float, n:int):
    if n == 0:
        return 1
    elif n%2 == 1: #odd
        return poww(a,n-1)*a
    else: #even
        return poww(a**2, n//2)

print(poww(2.0, 10))