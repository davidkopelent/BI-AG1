# Detekce cyklů v orientovaném grafu

**Pseudokód**
has_cycle(graf G):\
(1) Pro každý vrchol u \in V(G):\
(2)     Stav[u] := nenalezený\
(3)\
(4) Pro každý vrchol u \in V(G):\
(5)     Pokud stav[u] = nenalezený && cyclic_util(G, u):\
(6)         vrať true\
(7) vrať false\
\
cyclic_util(vrchol u):\
(1) Pokud stav[u] = otevřený: vrať true\
(2) Pokud stav[u] = uzavřený: vrať false\
(3) stav[u] = otevřený\
(4) \
(5) Pro každého souseda v vrcholu u:\
(6)     Pokud cyclic_util(v) = true: vrať true\
(7)\
(8) stav[u] = uzavřený\
(9) vrať false\