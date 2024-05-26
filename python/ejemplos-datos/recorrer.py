def resultado(fil, col, val):

    mat = [[0,0,0],[0,0,0],[0,0,0]]
    mat[fil][col] = val

    diagonal1, diagonal2 = 1, 1
    columna1, columna2, columna3 = 1, 1, 1
    fila1, fila2, fila3 = 1, 1, 1

    for row in range (3):
        diagonal1 = diagonal1 * mat[row][row]
        diagonal2 = diagonal2 * mat[row][2-row]
        columna1 = columna1 * mat[row][0]
        columna2 = columna2 * mat[row][1]
        columna3 = columna3 * mat[row][2]
        fila1 = fila1 * mat[0][row]
        fila2 = fila2 * mat[1][row]
        fila3 = fila3 * mat[2][row]
    print(mat)

resultado(0,0,1)
resultado(1,0,1)
resultado(2,0,1)