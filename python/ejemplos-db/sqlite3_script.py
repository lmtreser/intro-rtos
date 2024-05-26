import sqlite3

conn = sqlite3.connect(':memory:')
cursor = conn.cursor()

cursor.execute("""CREATE TABLE table_1 (ID integer primary key, name text)""")
cursor.execute("INSERT INTO table_1 VALUES (1, 'prueba')")

conn.commit()

query = "SELECT * FROM table_1"
currencies = cursor.execute(query).fetchall()
print(currencies)

conn.close()