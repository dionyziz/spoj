N = input()
for i in range(0, N):
    (a, b) = raw_input().split(' ')
    print(int(str(int(str(a)[::-1]) + int(str(b)[::-1]))[::-1]))
