# # # # class Node:
# # # #     def __init__(self, name):
# # # #         self.name = name
# # # #         self.edges = []

# # # # class Edge:
# # # #     def __init__(self, to, capacity):
# # # #         self.to = to
# # # #         self.capacity = capacity
# # # #         self.flow = 0
# # # #         self.rev = None  

# # # # def add_edge(u, v, capacity):
# # # #     forward_edge = Edge(v, capacity)
# # # #     backward_edge = Edge(u, 0)
# # # #     forward_edge.rev = backward_edge
# # # #     backward_edge.rev = forward_edge
# # # #     u.edges.append(forward_edge)
# # # #     v.edges.append(backward_edge)
# # # #     return forward_edge

# # # # def int_value(s):
# # # #     """
# # # #     Converts a string representation of a number with 3 decimal digits into an integer.
# # # #     Handles negative numbers and removes the decimal point.
# # # #     """
# # # #     n = len(s)
# # # #     sum = 0
# # # #     is_negative = s[0] == '-'
    
# # # #     for i in range(n):
# # # #         if s[i] != '.' and s[i] != '-':
# # # #             sum = sum * 10 + (ord(s[i]) - ord('0'))
    
# # # #     if is_negative and sum != 0:
# # # #         sum *= -1

# # # #     return sum

# # # # def custom_floor(x):
# # # #     """
# # # #     Returns the floor of the number, where `x` is an integer representation
# # # #     of a floating-point number with 3 decimal places (scaled by 1000).
# # # #     """
# # # #     if x >= 0:
# # # #         return x // 1000
# # # #     else:
# # # #         return -((-x + 999) // 1000)

# # # # def custom_ceil(x):
# # # #     """
# # # #     Returns the ceil of the number, where `x` is an integer representation
# # # #     of a floating-point number with 3 decimal places (scaled by 1000).
# # # #     """
# # # #     return custom_floor(x) if x % 1000 == 0 else custom_floor(x) + 1

# # # # def solve_netflow(nodes, source, sink):
# # # #     from collections import deque

# # # #     def bfs_build_level_graph(level):
# # # #         for node in nodes:
# # # #             level[node] = -1
# # # #         queue = deque()
# # # #         queue.append(source)
# # # #         level[source] = 0

# # # #         while queue:
# # # #             u = queue.popleft()
# # # #             for e in u.edges:
# # # #                 if level[e.to] < 0 and e.flow < e.capacity:
# # # #                     level[e.to] = level[u] + 1
# # # #                     queue.append(e.to)

# # # #         return level[sink] != -1

# # # #     def send_flow_dfs(u, flow, sink, level, start):
# # # #         if u == sink:
# # # #             return flow

# # # #         while start[u] < len(u.edges):
# # # #             e = u.edges[start[u]]
# # # #             if level[e.to] == level[u] + 1 and e.flow < e.capacity:
# # # #                 current_flow = e.capacity - e.flow
# # # #                 min_flow = min(flow, current_flow)
# # # #                 flow_sent = send_flow_dfs(e.to, min_flow, sink, level, start)
# # # #                 if flow_sent > 0:
# # # #                     e.flow += flow_sent
# # # #                     e.rev.flow -= flow_sent
# # # #                     return flow_sent
# # # #             start[u] += 1

# # # #         return 0

# # # #     def dinic_max_flow():
# # # #         max_flow = 0
# # # #         level = {}

# # # #         while bfs_build_level_graph(level):
# # # #             start = {node: 0 for node in nodes}
# # # #             while True:
# # # #                 flow_sent = send_flow_dfs(source, float('inf'), sink, level, start)
# # # #                 if flow_sent <= 0:
# # # #                     break
# # # #                 max_flow += flow_sent

# # # #         return max_flow

# # # #     return dinic_max_flow()

# # # # def solve():
# # # #     n, m = map(int, input().split())
# # # #     matrix = []
# # # #     nodes = [Node(f'row{i}') if i < n else Node(f'col{i-n}') for i in range(n + m)]
# # # #     source = Node('source')
# # # #     sink = Node('sink')

# # # #     for _ in range(n):
# # # #         row = input().split()
# # # #         matrix.append([int_value(x) for x in row])

# # # #     floor_matrix = [[custom_floor(x) for x in row] for row in matrix]
# # # #     ceil_matrix = [[custom_ceil(x) for x in row] for row in matrix]

# # # #     row_diff = [sum(matrix[i]) // 1000 - sum(floor_matrix[i]) for i in range(n)]
# # # #     col_diff = [sum(matrix[i][j] for i in range(n)) // 1000 - sum(floor_matrix[i][j] for i in range(n)) for j in range(m)]

# # # #     # Check if row_diff or col_diff contains invalid values
# # # #     for diff in row_diff + col_diff:
# # # #         # print ("diff:",diff)
# # # #         if not (0 <= diff <= 1):
# # # #             print("NO")
# # # #             return

# # # #     if sum(row_diff) != sum(col_diff):
# # # #         print("NO")
# # # #         return

# # # #     for i in range(n):
# # # #         add_edge(source, nodes[i], row_diff[i])

# # # #     for j in range(m):
# # # #         add_edge(nodes[j + n], sink, col_diff[j])

# # # #     edges = []
# # # #     for i in range(n):
# # # #         row_edges = []
# # # #         for j in range(m):
# # # #             e = add_edge(nodes[i], nodes[j + n], 1 if floor_matrix[i][j] < ceil_matrix[i][j] else 0)
# # # #             row_edges.append(e)
# # # #         edges.append(row_edges)

# # # #     max_flow = solve_netflow(nodes + [source, sink], source, sink)

# # # #     if max_flow != sum(row_diff):
# # # #         print("NO")
# # # #         return

# # # #     print("YES")
# # # #     for i in range(n):
# # # #         print(" ".join("1" if edges[i][j].flow > 0 else "0" for j in range(m)))

# # # # t = int(input())
# # # # for _ in range(t):
# # # #     solve()
# # # # class Node:
# # # #     def __init__(self, name):
# # # #         self.name = name
# # # #         self.edges = []

# # # # class Edge:
# # # #     def __init__(self, to, capacity):
# # # #         self.to = to
# # # #         self.capacity = capacity
# # # #         self.flow = 0
# # # #         self.rev = None  

# # # # def add_edge(u, v, capacity):
# # # #     forward_edge = Edge(v, capacity)
# # # #     backward_edge = Edge(u, 0)
# # # #     forward_edge.rev = backward_edge
# # # #     backward_edge.rev = forward_edge
# # # #     u.edges.append(forward_edge)
# # # #     v.edges.append(backward_edge)
# # # #     return forward_edge

# # # # def int_value(s):
# # # #     """
# # # #     Converts a string representation of a number with 3 decimal digits into an integer.
# # # #     Handles negative numbers and removes the decimal point.
# # # #     """
# # # #     n = len(s)
# # # #     sum = 0
# # # #     is_negative = s[0] == '-'
    
# # # #     for i in range(n):
# # # #         if s[i] != '.' and s[i] != '-':
# # # #             sum = sum * 10 + (ord(s[i]) - ord('0'))
    
# # # #     if is_negative and sum != 0:
# # # #         sum *= -1

# # # #     return sum

# # # # def custom_floor(x):
# # # #     """
# # # #     Returns the floor of the number, where `x` is an integer representation
# # # #     of a floating-point number with 3 decimal places (scaled by 1000).
# # # #     """
# # # #     if x >= 0:
# # # #         return x // 1000
# # # #     else:
# # # #         return -((-x + 999) // 1000)

# # # # def custom_ceil(x):
# # # #     """
# # # #     Returns the ceil of the number, where `x` is an integer representation
# # # #     of a floating-point number with 3 decimal places (scaled by 1000).
# # # #     """
# # # #     return custom_floor(x) if x % 1000 == 0 else custom_floor(x) + 1

# # # # def solve_netflow(nodes, source, sink):
# # # #     from collections import deque

# # # #     def bfs_build_level_graph(level):
# # # #         for node in nodes:
# # # #             level[node] = -1
# # # #         queue = deque()
# # # #         queue.append(source)
# # # #         level[source] = 0

# # # #         while queue:
# # # #             u = queue.popleft()
# # # #             for e in u.edges:
# # # #                 if level[e.to] < 0 and e.flow < e.capacity:
# # # #                     level[e.to] = level[u] + 1
# # # #                     queue.append(e.to)

# # # #         return level[sink] != -1

# # # #     def send_flow_dfs(u, flow, sink, level, start):
# # # #         if u == sink:
# # # #             return flow

# # # #         while start[u] < len(u.edges):
# # # #             e = u.edges[start[u]]
# # # #             if level[e.to] == level[u] + 1 and e.flow < e.capacity:
# # # #                 current_flow = e.capacity - e.flow
# # # #                 min_flow = min(flow, current_flow)
# # # #                 flow_sent = send_flow_dfs(e.to, min_flow, sink, level, start)
# # # #                 if flow_sent > 0:
# # # #                     e.flow += flow_sent
# # # #                     e.rev.flow -= flow_sent
# # # #                     return flow_sent
# # # #             start[u] += 1

# # # #         return 0

# # # #     def dinic_max_flow():
# # # #         max_flow = 0
# # # #         level = {}

# # # #         while bfs_build_level_graph(level):
# # # #             start = {node: 0 for node in nodes}
# # # #             while True:
# # # #                 flow_sent = send_flow_dfs(source, float('inf'), sink, level, start)
# # # #                 if flow_sent <= 0:
# # # #                     break
# # # #                 max_flow += flow_sent

# # # #         return max_flow

# # # #     return dinic_max_flow()

# # # # def solve():
# # # #     n, m = map(int, input().split())
# # # #     matrix = []
# # # #     nodes = [Node(f'row{i}') if i < n else Node(f'col{i-n}') for i in range(n + m)]
# # # #     source = Node('source')
# # # #     sink = Node('sink')

# # # #     for _ in range(n):
# # # #         row = input().split()
# # # #         matrix.append([int_value(x) for x in row])

# # # #     floor_matrix = [[custom_floor(x) for x in row] for row in matrix]
# # # #     ceil_matrix = [[custom_ceil(x) for x in row] for row in matrix]

# # # #     row_diff = [sum(matrix[i]) // 1000 - sum(floor_matrix[i]) for i in range(n)]
# # # #     col_diff = [sum(matrix[i][j] for i in range(n)) // 1000 - sum(floor_matrix[i][j] for i in range(n)) for j in range(m)]

# # # #     # Check if any row or column diff is not an integer
# # # #     for diff in row_diff + col_diff:
# # # #         if not (0 <= diff <= 1):
# # # #             print("NO")
# # # #             return

# # # #     # Check if total diff matches
# # # #     if sum(row_diff) != sum(col_diff):
# # # #         print("NO")
# # # #         return

# # # #     for i in range(n):
# # # #         add_edge(source, nodes[i], row_diff[i])

# # # #     for j in range(m):
# # # #         add_edge(nodes[j + n], sink, col_diff[j])

# # # #     edges = []
# # # #     for i in range(n):
# # # #         row_edges = []
# # # #         for j in range(m):
# # # #             e = add_edge(nodes[i], nodes[j + n], 1 if floor_matrix[i][j] < ceil_matrix[i][j] else 0)
# # # #             row_edges.append(e)
# # # #         edges.append(row_edges)

# # # #     max_flow = solve_netflow(nodes + [source, sink], source, sink)

# # # #     if max_flow != sum(row_diff):
# # # #         print("NO")
# # # #         return

# # # #     print("YES")
# # # #     for i in range(n):
# # # #         print(" ".join("1" if edges[i][j].flow > 0 else "0" for j in range(m)))

# # # # t = int(input())
# # # # for _ in range(t):
# # # #     solve()
# # # class Node:
# # #     def __init__(self, name):
# # #         self.name = name
# # #         self.edges = []

# # # class Edge:
# # #     def __init__(self, to, capacity):
# # #         self.to = to
# # #         self.capacity = capacity
# # #         self.flow = 0
# # #         self.rev = None  

# # # def add_edge(u, v, capacity):
# # #     forward_edge = Edge(v, capacity)
# # #     backward_edge = Edge(u, 0)
# # #     forward_edge.rev = backward_edge
# # #     backward_edge.rev = forward_edge
# # #     u.edges.append(forward_edge)
# # #     v.edges.append(backward_edge)
# # #     return forward_edge

# # # def int_value(s):
# # #     n = len(s)
# # #     sum = 0
# # #     is_negative = s[0] == '-'
    
# # #     for i in range(n):
# # #         if s[i] != '.' and s[i] != '-':
# # #             sum = sum * 10 + (ord(s[i]) - ord('0'))
    
# # #     if is_negative and sum != 0:
# # #         sum *= -1

# # #     return sum

# # # def custom_floor(x):
# # #     if x >= 0:
# # #         return x // 1000
# # #     else:
# # #         return -((-x + 999) // 1000)

# # # def custom_ceil(x):
# # #     return custom_floor(x) if x % 1000 == 0 else custom_floor(x) + 1

# # # def solve_netflow(nodes, source, sink):
# # #     from collections import deque

# # #     def bfs_build_level_graph(level):
# # #         for node in nodes:
# # #             level[node] = -1
# # #         queue = deque()
# # #         queue.append(source)
# # #         level[source] = 0

# # #         while queue:
# # #             u = queue.popleft()
# # #             for e in u.edges:
# # #                 if level[e.to] < 0 and e.flow < e.capacity:
# # #                     level[e.to] = level[u] + 1
# # #                     queue.append(e.to)

# # #         return level[sink] != -1

# # #     def send_flow_dfs(u, flow, sink, level, start):
# # #         if u == sink:
# # #             return flow

# # #         while start[u] < len(u.edges):
# # #             e = u.edges[start[u]]
# # #             if level[e.to] == level[u] + 1 and e.flow < e.capacity:
# # #                 current_flow = e.capacity - e.flow
# # #                 min_flow = min(flow, current_flow)
# # #                 flow_sent = send_flow_dfs(e.to, min_flow, sink, level, start)
# # #                 if flow_sent > 0:
# # #                     e.flow += flow_sent
# # #                     e.rev.flow -= flow_sent
# # #                     return flow_sent
# # #             start[u] += 1

# # #         return 0

# # #     def dinic_max_flow():
# # #         max_flow = 0
# # #         level = {}

# # #         while bfs_build_level_graph(level):
# # #             start = {node: 0 for node in nodes}
# # #             while True:
# # #                 flow_sent = send_flow_dfs(source, float('inf'), sink, level, start)
# # #                 if flow_sent <= 0:
# # #                     break
# # #                 max_flow += flow_sent

# # #         return max_flow

# # #     return dinic_max_flow()

# # # def solve():
# # #     n, m = map(int, input().split())
# # #     matrix = []
# # #     nodes = [Node(f'row{i}') if i < n else Node(f'col{i-n}') for i in range(n + m)]
# # #     source = Node('source')
# # #     sink = Node('sink')

# # #     for _ in range(n):
# # #         row = input().split()
# # #         matrix.append([int_value(x) for x in row])

# # #     # Check if the sum of all rows and columns is an integer
# # #     for row in matrix:
# # #         row_sum = sum(float(x) for x in row)#/1000
# # #         # print(" sum",row_sum)   
# # #         if  (row_sum >= 1000 and row_sum/1000 % 1 != 0 ) or (row_sum % 1 != 0):
# # #             print("NO")
# # #             return

# # #     # for j in range(m):
# # #     #     col_sum = sum(float(matrix[i][j])/1000 for i in range(n))

# # #     #     if col_sum % 1 != 0:
# # #     #         print("NO")
# # #     #         return

# # #     floor_matrix = [[custom_floor(x) for x in row] for row in matrix]
# # #     ceil_matrix = [[custom_ceil(x) for x in row] for row in matrix]

# # #     row_diff = [sum(matrix[i]) // 1000 - sum(floor_matrix[i]) for i in range(n)]
# # #     col_diff = [sum(matrix[i][j] for i in range(n)) // 1000 - sum(floor_matrix[i][j] for i in range(n)) for j in range(m)]

# # #     for diff in row_diff + col_diff:
# # #         if not (0 <= diff <= 1):
# # #             print("NO")
# # #             return

# # #     if sum(row_diff) != sum(col_diff):
# # #         print("NO")
# # #         return

# # #     for i in range(n):
# # #         add_edge(source, nodes[i], row_diff[i])

# # #     for j in range(m):
# # #         add_edge(nodes[j + n], sink, col_diff[j])

# # #     edges = []
# # #     for i in range(n):
# # #         row_edges = []
# # #         for j in range(m):
# # #             e = add_edge(nodes[i], nodes[j + n], 1 if floor_matrix[i][j] < ceil_matrix[i][j] else 0)
# # #             row_edges.append(e)
# # #         edges.append(row_edges)

# # #     max_flow = solve_netflow(nodes + [source, sink], source, sink)

# # #     if max_flow != sum(row_diff):
# # #         print("NO")
# # #         return

# # #     print("YES")
# # #     for i in range(n):
# # #         print(" ".join("1" if edges[i][j].flow > 0 else "0" for j in range(m)))

# # # t = int(input())
# # # for _ in range(t):
# # #     solve()
# # from collections import deque

# # class Node:
# #     def __init__(self, name):
# #         self.name = name
# #         self.edges = []

# # class Edge:
# #     def __init__(self, to, capacity):
# #         self.to = to
# #         self.capacity = capacity
# #         self.flow = 0
# #         self.rev = None

# # def add_edge(u, v, capacity):
# #     forward_edge = Edge(v, capacity)
# #     backward_edge = Edge(u, 0)
# #     forward_edge.rev = backward_edge
# #     backward_edge.rev = forward_edge
# #     u.edges.append(forward_edge)
# #     v.edges.append(backward_edge)
# #     return forward_edge

# # def bfs(graph, source, sink, parent):
# #     visited = {node: False for node in graph}
# #     queue = deque([source])
# #     visited[source] = True

# #     while queue:
# #         u = queue.popleft()
# #         for edge in u.edges:
# #             if visited[edge.to] == False and edge.flow < edge.capacity:
# #                 queue.append(edge.to)
# #                 visited[edge.to] = True
# #                 parent[edge.to] = (u, edge)
# #                 if edge.to == sink:
# #                     return True
# #     return False

# # def edmonds_karp(graph, source, sink):
# #     parent = {}
# #     max_flow = 0

# #     while bfs(graph, source, sink, parent):
# #         path_flow = float('Inf')
# #         s = sink

# #         while s != source:
# #             u, edge = parent[s]
# #             path_flow = min(path_flow, edge.capacity - edge.flow)
# #             s = u

# #         max_flow += path_flow
# #         v = sink
# #         while v != source:
# #             u, edge = parent[v]
# #             edge.flow += path_flow
# #             edge.rev.flow -= path_flow
# #             v = u

# #     return max_flow

# # def solve():
# #     n, m = map(int, input().split())
# #     matrix = []
# #     nodes = [Node(f'row{i}') if i < n else Node(f'col{i-n}') for i in range(n + m)]
# #     source = Node('source')
# #     sink = Node('sink')

# #     for _ in range(n):
# #         row = input().split()
# #         matrix.append([int(float(x) * 1000) for x in row])

# #     # Check if the sum of all rows and columns is an integer
# #     for row in matrix:
# #         row_sum = sum(float(x) / 1000 for x in row)
# #         if row_sum % 1 != 0:
# #             print("NO")
# #             return

# #     for j in range(m):
# #         col_sum = sum(float(matrix[i][j]) / 1000 for i in range(n))
# #         if col_sum % 1 != 0:
# #             print("NO")
# #             return

# #     floor_matrix = [[(x // 1000) for x in row] for row in matrix]
# #     ceil_matrix = [[((x // 1000) if x % 1000 == 0 else (x // 1000) + 1) for x in row] for row in matrix]

# #     row_diff = [sum(matrix[i]) // 1000 - sum(floor_matrix[i]) for i in range(n)]
# #     col_diff = [sum(matrix[i][j] for i in range(n)) // 1000 - sum(floor_matrix[i][j] for i in range(n)) for j in range(m)]

# #     for diff in row_diff + col_diff:
# #         if not (0 <= diff <= 1):
# #             print("NO")
# #             return

# #     if sum(row_diff) != sum(col_diff):
# #         print("NO")
# #         return

# #     for i in range(n):
# #         add_edge(source, nodes[i], row_diff[i])

# #     for j in range(m):
# #         add_edge(nodes[j + n], sink, col_diff[j])

# #     edges = []
# #     for i in range(n):
# #         row_edges = []
# #         for j in range(m):
# #             e = add_edge(nodes[i], nodes[j + n], 1 if floor_matrix[i][j] < ceil_matrix[i][j] else 0)
# #             row_edges.append(e)
# #         edges.append(row_edges)

# #     max_flow = edmonds_karp(nodes + [source, sink], source, sink)

# #     if max_flow != sum(row_diff):
# #         print("NO")
# #         return

# #     print("YES")
# #     for i in range(n):
# #         print(" ".join("1" if edges[i][j].flow > 0 else "0" for j in range(m)))

# # t = int(input())
# # for _ in range(t):
# #     solve()
# class Node:
#     def __init__(self, name):
#         self.name = name
#         self.edge = []

# class Edge:
#     def __init__(self, to, capacity):
#         self.to = to
#         self.capacity = capacity
#         self.flow = 0
#         self.rev = None  

# def add_edge(u, v, capacity):
#     forward_edge = Edge(v, capacity)
#     backward_edge = Edge(u, 0)
#     forward_edge.rev = backward_edge
#     backward_edge.rev = forward_edge
#     u.edge.append(forward_edge)
#     v.edge.append(backward_edge)
#     return forward_edge

# def int_value(s):
#     """
#     Converts a string representation of a number with 3 decimal digits into an integer.
#     Handles negative numbers and removes the decimal point.
#     """
#     n = len(s)
#     total = 0
#     is_negative = s[0] == '-'
    
#     for i in range(n):
#         if s[i] != '.' and s[i] != '-':
#             total = total * 10 + (ord(s[i]) - ord('0'))
    
#     if is_negative and total != 0:
#         total *= -1

#     return total

# def solve_netflow(nodes, source, sink):
#     from collections import deque

#     def bfs(level):
#         for node in nodes:
#             level[node] = -1
#         queue = deque([source])
#         level[source] = 0

#         while queue:
#             u = queue.popleft()
#             for e in u.edge:
#                 if level[e.to] < 0 and e.flow < e.capacity:
#                     level[e.to] = level[u] + 1
#                     queue.append(e.to)

#         return level[sink] != -1

#     def dfs(u, flow, sink, level, start):
#         if u == sink:
#             return flow

#         while start[u] < len(u.edge):
#             e = u.edge[start[u]]
#             if level[e.to] == level[u] + 1 and e.flow < e.capacity:
#                 current_flow = e.capacity - e.flow
#                 min_flow = min(flow, current_flow)
#                 flow_sent = dfs(e.to, min_flow, sink, level, start)
#                 if flow_sent > 0:
#                     e.flow += flow_sent
#                     e.rev.flow -= flow_sent
#                     return flow_sent
#             start[u] += 1

#         return 0

#     max_flow = 0
#     level = {}
#     while bfs(level):
#         start = {node: 0 for node in nodes}
#         while True:
#             flow_sent = dfs(source, float('inf'), sink, level, start)
#             if flow_sent == 0:
#                 break
#             max_flow += flow_sent

#     return max_flow

# def solve():
#     n, m = map(int, input().split())
#     matrix = []
#     fractional_sum_row = [0] * n
#     fractional_sum_col = [0] * m

#     for i in range(n):
#         row = input().split()
#         matrix.append([int_value(x) for x in row])
#         for j in range(m):
#             fractional_part = matrix[i][j] % 1000
#             fractional_sum_row[i] += fractional_part
#             fractional_sum_col[j] += fractional_part

#     # Check if rounding is possible
#     for s in fractional_sum_row + fractional_sum_col:
#         if abs(s % 1000) != 0:
#             print("NO")
#             return

#     # Check if total integer sum is possible
#     row_integer_sum = [sum(matrix[i]) for i in range(n)]
#     col_integer_sum = [sum(matrix[i][j] for i in range(n)) for j in range(m)]
#     for s in row_integer_sum + col_integer_sum:
#         if s % 1000 != 0:
#             print("NO")
#             return

#     nodes = [Node(f'row{i}') for i in range(n)] + [Node(f'col{j}') for j in range(m)]
#     source = Node('source')
#     sink = Node('sink')

#     row_diff = [s // 1000 for s in fractional_sum_row]
#     col_diff = [s // 1000 for s in fractional_sum_col]

#     for i in range(n):
#         add_edge(source, nodes[i], row_diff[i])

#     for j in range(m):
#         add_edge(nodes[j + n], sink, col_diff[j])

#     edges = []
#     for i in range(n):
#         row_edges = []
#         for j in range(m):
#             e = add_edge(nodes[i], nodes[j + n], 1)
#             row_edges.append(e)
#         edges.append(row_edges)

#     max_flow = solve_netflow(nodes + [source, sink], source, sink)

#     if max_flow != sum(row_diff):
#         print("NO")
#         return

#     print("YES")
#     result = [[0] * m for _ in range(n)]
#     for i in range(n):
#         for j in range(m):
#             if edges[i][j].flow > 0:
#                 result[i][j] = 1

#     for row in result:
#         print(" ".join(map(str, row)))

# t = int(input())
# for _ in range(t):
#     solve()


