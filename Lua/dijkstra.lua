require "graph"

function Graph.Dijkstra(Graph, start)
    local distances = {}
    local paths = {} -- P
    for _, node in next, Graph.Nodes do
        distances[node.name] = math.huge
        paths[node.name] = {} -- P
    end
    distances[start] = 0
    local visited = {}
    local queue = {}
    table.insert(queue, start)
    while #queue > 0 do
        local current = Graph.Nodes[table.remove(queue, 1)]
        if not visited[current.name] then
            visited[current.name] = true
            for _, neighbor in next, current.edges do
                local alt = distances[current.name] + neighbor.weight
                if alt < distances[neighbor.to] then
                    distances[neighbor.to] = alt
                    paths[neighbor.to] = {} -- P
                    for _, v in next, paths[current.name] do -- P
                        table.insert(paths[neighbor.to], v) -- P
                    end -- P
                    table.insert(paths[neighbor.to], current.name) -- P
                    table.insert(queue, neighbor.to)
                end
            end
        end
    end
    return distances, paths
end

function CreateGraph()
    local graph = Graph()
    graph:AddNode("Hygge")
    graph:AddNode("Stallgården")
    graph:AddNode("Heim")
    graph:AddNode("Nellie")
    graph:AddNode("Gullkorn")
    graph:AddNode("Siesta")
    graph:AddNode("Festiviteten")
    graph:AddNode("Matkvartalet")

    graph:AddEdge("Hygge", "Stallgården", 1)
    graph:AddEdge("Hygge", "Nellie", 2)

    graph:AddEdge("Stallgården", "Heim", 2)

    graph:AddEdge("Heim", "Nellie", 3)
    graph:AddEdge("Heim", "Gullkorn", 2)
    graph:AddEdge("Heim", "Siesta", 3)

    graph:AddEdge("Nellie", "Gullkorn", 4)

    graph:AddEdge("Gullkorn", "Siesta", 3)
    graph:AddEdge("Gullkorn", "Festiviteten", 5)

    graph:AddEdge("Siesta", "Festiviteten", 8)
    graph:AddEdge("Siesta", "Matkvartalet", 3)

    graph:AddEdge("Festiviteten", "Matkvartalet", 6)

    return graph
end

local barcrawl = CreateGraph()

local distances, paths = barcrawl:Dijkstra("Hygge")
for k, v in next, distances do
    table.insert(paths[k], k) -- P
    print(v, table.concat(paths[k], " -> "))
end
local NewEdges = {}
for _, path in next, paths do
    for n, to in next, path do
        if n > 1 then
            local from = path[n - 1]
            if not NewEdges[from] then
                NewEdges[from] = {}
            end
            NewEdges[from][to] = true
        end
    end
end
for from, tos in next, NewEdges do
    for to, _ in next, tos do
        print(("%s,%s"):format(from, to))
    end
end
