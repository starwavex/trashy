def gcdExtended(a, b):
	if a == 0:
		return b, 0, 1
	
	gcd, x1, y1 = gcdExtended(b%a, a)

	x = y1 - (b//a) * x1
	y = x1

	return gcd, x, y

def modExp(m:int, e:int, n:int):
	m1 = m%n
	if m1 == 0:
		return 0
	while e > 1:
		m1 *= m
		m1 %= n
		#print(m1, e, end='\n')
		e -= 1
	return m1

def getE(l:int):
	t = 3
	gcd, tr1, tr2 = gcdExtended(l, t)
	while (gcd != 1 and t < l):
		t += 1
		gcd, tr1, tr2 = gcdExtended(l, t)
	return t

def main():
	p = int(input('Enter p: '))
	q = int(input('Enter q: '))

	n = p * q #public
	gcd, tr1, tr2 = gcdExtended(p-1,q-1)
	l = ((p-1) * (q-1)) // gcd
	print(gcd, n ,l)
	t = getE(l) #public, t = 17
	tr1, d, tr2 = gcdExtended(t, -l)
	#private
	mes = int(input('Enter mes: '))
	c = modExp(mes, t, n)
	mes = modExp(c, d, n)
	print('Ciphered: ', c)
	print('Deciphered: ', mes)
	pass

main()
