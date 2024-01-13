from random import *
from cyaron import *
from luogu import *

n = randint(1, int(4e4))
m = int(1e5)
print(n, m)
for _ in range(n):
  print(randint(0, int(2e9)), end = ' ')
print()
graph = Graph.tree(n)
for edge in graph.iterate_edges():
  print(edge.start, edge.end)
for _ in range(m):
  print(randint(1, n), randint(1, n))