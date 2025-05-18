#Sayyed Mohammad Hossein Mazhari 
#CA3 Q2 
##https://chatgpt.com/share/6745e59a-a570-800e-af00-b95d4e061f7f
def solve():
    a, b, c, d = map(int, input().split())
    s = input()

    h_count = s.count('H')
    p_count = s.count('P')

    if h_count == a + c + d and p_count == b + c + d:
        return "YES"
    else:
        return "NO"

t = int(input())
for _ in range(t):
    print(solve())
