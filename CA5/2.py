# Sayyed Mohammad Hosein Mazhari
# CA5 Q2

def read_input():
    n, m = map(int, input().split())
    graph = [[] for _ in range(n + 1)]
    for _ in range(m):
        a, b = map(int, input().split())
        if 1 <= a <= n and 1 <= b <= n:  
            graph[a].append(b)
    return n, m, graph


def find_path(graph, source, sink):
    
    stack = [(source, [source])]
    visited = [False] * len(graph)

    while stack:
        u, path = stack.pop()
        if u == sink:
            return path

        if not visited[u]:
            visited[u] = True
            for v in graph[u]:
                if not visited[v]:
                    stack.append((v, path + [v]))
    return None


def remove_path(graph, path):
    for i in range(len(path) - 1):
        u, v = path[i], path[i + 1]
        if v in graph[u]:  
            graph[u].remove(v)


def main():
    n, m, graph = read_input()
    paths = []

    while True:
        path = find_path(graph, 1, n)
        if path:
            paths.append(path)
            remove_path(graph, path)
        else:
            break

    print(len(paths))
    for path in paths:
        print(len(path))
        print(*path)


if __name__ == "__main__":
    main()
