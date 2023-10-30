Graph = {}

setmetatable(Graph, {
    __call = function(self, ...)
        return self.new(...)
    end,
})

function Graph.new()
    local self = setmetatable({}, {__index = Graph})
    self.Nodes = {}
    self.Edges = {}
    return self
end

function Graph.AddNode(graph, name)
    graph.Nodes[name] = {
        name = name,
        edges = {},
        adjacent = {},
    }
end

function Graph.GetEdges(graph)
    return graph.Edges
end

function Graph.GetNodes(graph)
    return graph.Nodes
end

function Graph.AddEdge(graph, from, to, weight)
    local Edge = {from = from, to = to, weight = weight}
    table.insert(graph.Edges, Edge)

    table.insert(graph.Nodes[from].edges, {to = to, edge = Edge, weight = weight})
    table.insert(graph.Nodes[from].adjacent, to)

    table.insert(graph.Nodes[to].edges, {to = from, edge = Edge, weight = weight})
    table.insert(graph.Nodes[to].adjacent, from)
end