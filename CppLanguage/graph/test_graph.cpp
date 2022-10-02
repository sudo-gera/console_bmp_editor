#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "src/graphs.hpp"

#include <memory>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <queue>

std::set<std::pair<size_t, size_t>> Generate(size_t V, size_t E) noexcept {
  std::set<std::pair<size_t, size_t>> edges{{0, 1}};

  std::random_device rd;
  std::mt19937_64 rng(rd());
  std::uniform_int_distribution<size_t> dist(0, V - 1);

  while (edges.size() < E) {
    size_t from = dist(rng);
    size_t to = dist(rng);
    while (from == to || edges.contains(std::make_pair(from, to))) {
      to = dist(rng);
    }
    edges.emplace(from, to);
  }
  return edges;
}

std::set<std::pair<size_t, size_t>> GetEdgesSet(const std::unique_ptr<IGraph>& graph) {
  std::set<std::pair<size_t, size_t>> result;
  std::vector<bool> visited(graph->VerticesCount());
  std::queue<size_t> q;
  for (size_t i = 0; i < visited.size(); ++i) {
    if (visited[i]) {
      continue;
    }
    q.push(i);
    while (!q.empty()) {
      auto current = q.front();
      visited[current] = true;
      std::vector<size_t> next_vertices;
      graph->GetNextVertices(current, next_vertices);
      for (const auto& next_vertex : next_vertices) {
        result.emplace(current, next_vertex);
        if (!visited[next_vertex]) {
          q.push(next_vertex);
        }
      }
      q.pop();
    }
  }
  return result;
}

TEST_CASE("Stress test") {
  for (size_t v = 2; v <= 256; v *= 2) {
    for (size_t e = 1; e <= (v * v + v) / 2 - v; e *= 2) {
      std::array<std::unique_ptr<IGraph>, 4> graphs = {
          std::make_unique<ArcGraph>(v),
          std::make_unique<ListGraph>(v),
          std::make_unique<MatrixGraph>(v),
          std::make_unique<SetGraph>(v),
      };
      auto edges = Generate(v, e);
      for (auto& graph : graphs) {
        for (const auto& [from, to] : edges) {
          graph->AddEdge(from, to);
        }
      }

      for (auto& graph : graphs) {
        std::unique_ptr<IGraph> ag = std::make_unique<ArcGraph>(graph.get());
        std::unique_ptr<IGraph> lg = std::make_unique<ListGraph>(graph.get());
        std::unique_ptr<IGraph> mg = std::make_unique<MatrixGraph>(graph.get());
        std::unique_ptr<IGraph> sg = std::make_unique<SetGraph>(graph.get());

        const auto ag_set = GetEdgesSet(ag);
        const auto lg_set = GetEdgesSet(lg);
        const auto mg_set = GetEdgesSet(mg);
        const auto sg_set = GetEdgesSet(sg);

        REQUIRE(ag_set == edges);
        REQUIRE(lg_set == edges);
        REQUIRE(mg_set == edges);
        REQUIRE(sg_set == edges);
      }
    }
  }
}