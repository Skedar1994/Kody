# zlozonosc n sqrt(n), python3
#p[0] = 1, p[1] = 1, p[2] = 2, p[100] to ok. 190 000 000, p[405] jako ostatnie sie miesci w long longu zwyklym
#1 1 2 3 5 7 11 15 22 30 42 56 77
def podzialy(n):
  pent = [0]
  for i in range(1, n+1):
    pent.append( (3*i-1)*i//2 )
  p = [1]
  for i in range(1, n+1):
    mnoz = j = 1
    akt = 0
    while pent[j] <= i:
      akt += mnoz * p[i-pent[j]]
      if i-pent[j]-j >= 0:
        akt += mnoz * p[i-pent[j]-j]
      mnoz *= -1
      j+=1
    p.append(akt)
  return p


odp = podzialy(100)
for el in odp:
  print(el, end=' ')
