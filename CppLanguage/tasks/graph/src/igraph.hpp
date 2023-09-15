#include <vector>
#include <stdexcept>

struct IGraph {
  virtual ~IGraph() = default;

  virtual void AddEdge(size_t from, size_t to) = 0;
  virtual size_t VerticesCount() const noexcept = 0;
  virtual void GetNextVertices(size_t vertex, std::vector<size_t>& vertices) const noexcept = 0;
  virtual void GetPrevVertices(size_t vertex, std::vector<size_t>& vertices) const noexcept = 0;
};
