n, m = map(int, input().split())
low=-1
high=-1
tempnum=n
tempsum=m

if m > 0:
    l=0
    h=0
    count=10
    while tempnum > 0:
        u = min(tempsum, 9)
        h *= count
        h += u
        tempsum -= u
        tempnum -= 1
    high = h

tempnum = n
tempsum = m
if m > 0:
    l = 0
    count = 1
    while tempnum > 0:
        u = min(tempsum, 9)
        tempsum -= u
        if tempsum == 0 and tempnum > 1:
            u -= 1
            tempsum += 1
        l += u * count
        count *= 10
        tempnum -= 1
    low = l

if m == 0 and n > 1 or m > 9 * n:
    print(-1, -1)
elif n == 1 and m == 0:
    print(0, 0)
else:
    print(low, high)