# Ejemplos Ciclos #1

s = 0

for n in range(1, 10):
    if n % 7 == 0:
        break
    s += n
    
print(s)