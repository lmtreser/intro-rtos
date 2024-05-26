import math

def fibo(num):
#fib(n) = fib(n-1) + fib(n-2) 
    num = (((1+math.sqrt(5))/2)**(num)-((1-math.sqrt(5))/2)**(num))/math.sqrt(5)
    return num

tunum = input("Ingrese un número a evaluar: ")
tunum = float(tunum)

print(fibo(tunum))
