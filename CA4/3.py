#https://chatgpt.com/share/676d9f44-7604-800e-a442-848b2f491c24
#Sayyed Mohammad Hossein Mazhari
#CA4 Q3
from collections import defaultdict

def find_parent(node, parent):
    if node == parent[node]:
        return node
    parent[node] = find_parent(parent[node], parent)
    return parent[node]

def depth_first_search(node, caller_index, time, is_visited, discovery_time, lowest_time, adj_list, edge_answer):
    is_visited[node] = True
    discovery_time[node] = time
    lowest_time[node] = time
    for adj in adj_list[node]:
        index = adj['index']
        adjacent_node = adj['node']
        if not is_visited[adjacent_node]:
            depth_first_search(adjacent_node, index, time + 1, is_visited, discovery_time, lowest_time, adj_list, edge_answer)
            lowest_time[node] = min(lowest_time[node], lowest_time[adjacent_node])
            if lowest_time[adjacent_node] > discovery_time[node]:
                edge_answer[index] = "any"
        elif index != caller_index:
            lowest_time[node] = min(lowest_time[node], discovery_time[adjacent_node])

def main():

    num_nodes, num_edges = map(int, input().split())

    weight_edges = defaultdict(list)
    adj_list = defaultdict(list)
    parent = list(range(num_nodes + 1))
    is_visited = [False] * (num_nodes + 1)
    discovery_time = [0] * (num_nodes + 1)
    lowest_time = [0] * (num_nodes + 1)
    edge_answer = ["none"] * (num_edges + 1)

    max_weight = 0
    for i in range(1, num_edges + 1):
        u, v, w = map(int, input().split())
        weight_edges[w].append({'node1': u, 'node2': v, 'index': i})
        max_weight = max(max_weight, w)

    for w in range(1, max_weight + 1):
        if not weight_edges[w]:
            continue

        for e in weight_edges[w]:
            u, v, i = e['node1'], e['node2'], e['index']
            parent_u = find_parent(u, parent)
            parent_v = find_parent(v, parent)
            if parent_u != parent_v:
                adj_list[parent_u].append({'node': parent_v, 'index': i})
                adj_list[parent_v].append({'node': parent_u, 'index': i})
                is_visited[parent_u] = is_visited[parent_v] = False
                edge_answer[i] = "at least one"

        for e in weight_edges[w]:
            u, v = e['node1'], e['node2']
            parent_u = find_parent(u, parent)
            if not is_visited[parent_u]:
                depth_first_search(parent_u, -1, 0, is_visited, discovery_time, lowest_time, adj_list, edge_answer)

            adj_list[parent_u].clear()
            adj_list[find_parent(v, parent)].clear()
            parent[parent_u] = find_parent(v, parent)

    for i in range(1, num_edges + 1):
        print(edge_answer[i])

if __name__ == "__main__":
    main()
