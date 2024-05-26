def es_primo(numero):

   resultado = True

   for divisor in range(2, numero):

       if (numero % divisor) == 0:

           resultado = False

           break

   return resultado 

es_primo(13)