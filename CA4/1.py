#https://aistudio.google.com/app/prompts?state=%7B%22ids%22%3A%5B%221xvAYeJY7V4tiai-bUaCl4xQptk5xy7cd%22%5D%2C%22action%22%3A%22open%22%2C%22userId%22%3A%22109127705709246180048%22%2C%22resourceKeys%22%3A%7B%7D%7D&usp=drive_link
# Sayyed Mohammad Hossein Mazhari
# CA4 Q1
from collections import defaultdict

def explore(node, visited, sky_paths):
    visited[node] = True
    for neighbor in sky_paths[node]:
        if not visited[neighbor]:
            explore(neighbor, visited, sky_paths)

def initialize_graphs(node_count):
    ground_paths = defaultdict(list)
    sky_paths = defaultdict(list)
    visited = [False] * (node_count + 1)
    return ground_paths, sky_paths, visited

def read_ground_paths(edge_count):
    ground_paths = defaultdict(list)
    for _ in range(edge_count):
        u, v = map(int, input().split())
        ground_paths[u].append(v)
        ground_paths[v].append(u)
    return ground_paths

def check_empty_ground_paths(node_count, ground_paths):
    for i in range(1, node_count + 1):
        if not ground_paths[i]:
            print(0)
            return True
    return False

def build_sky_paths(node_count, ground_paths):
    sky_paths = defaultdict(list)
    for i in range(1, node_count + 1):
        ground_paths[i].sort()

    for i in range(1, node_count + 1):
        pointer = 0
        for j in range(1, node_count + 1):
            if i == j:
                continue

            if pointer == len(ground_paths[i]):
                sky_paths[i].append(j)
                continue

            if ground_paths[i][pointer] == j:
                pointer += 1
            else:
                sky_paths[i].append(j)

    return sky_paths

def count_components(node_count, visited, sky_paths):
    components_count = 0
    for i in range(1, node_count + 1):
        if not visited[i]:
            explore(i, visited, sky_paths)
            components_count += 1
    return components_count

def main():
    node_count, edge_count = map(int, input().split())

    ground_paths, sky_paths, visited = initialize_graphs(node_count)
    ground_paths = read_ground_paths(edge_count)

    if check_empty_ground_paths(node_count, ground_paths):
        return

    sky_paths = build_sky_paths(node_count, ground_paths)
    components_count = count_components(node_count, visited, sky_paths)

    print(components_count - 1)

if __name__ == "__main__":
    main()
