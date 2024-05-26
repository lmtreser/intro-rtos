# Ejemplos Ciclos #2

s = 0

for n in range(1, 10):    
    if n % 2 != 0:
        continue
        s += n
else:
    s += 5

print(s)