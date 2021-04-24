# py -3 -m venv .venv
# .venv\scripts\activate
# Ctrl + Shift + `


import os

# import matplotlib.pyplot as plt

# path = "matplotlib"

# Определяем сколько файлов в каталоге
# path = "matplotlib\data_la"
# list = os.listdir(path) # dir is your directory path
# number_files = len(list)
# print(number_files)

# Создаем массив данных с количеством файлов.

# Чтение файлов по очереди
# for filename in os.listdir(path):
#     if filename.endswith(".txt"):
#         with open(os.path.join(path, filename), 'rb') as myfile:
#             data=myfile.read()
#             print(data)

# Упаковываем данные в словарь

# Чтение и подготовка данных
d = {}
d_y=[]

d_cr1_12v = []
d_cr2_12v = []

with open(r"2_2.txt") as f:
   for line in f:
       key, *value = line.split()
       d[key] = value

for dt in d:
   d_y.append(dt)
   if dt == "//12V":
       # pass
       d[dt] = 0

   if dt != "//12V":
       if d[dt] != []:
           d_cr1_12v.append(d[dt][0])
           d_cr2_12v.append(d[dt][1])
        #    print(d_cr1_12v)
           # print('d_cr1_12v',d_cr1_12v,'d_cr2_12v',d_cr2_12v)

print('d_y_volt',d_y)
j = 0
for i in d_y:
   
   if i =="//12V" or i == '//27V'or i == '-12000':
       d_y.pop(j)
   
   j +=1
print('d_x',d_y)




   # if dt == "//27V":
   #     break

   # elif dt == "//27V":
   #     if d[dt] != []:
   #         d_cr1_27v = d[dt][0]
   #         d_cr2_27v = d[dt][1]
   #         # print('d_cr1_27v',d_cr1_27v,'d_cr2_27v',d_cr2_27v)

# Отрисовываем данные

# plt.plot(d_x,d_cr1_12v)
# plt.show()

# Вычисляем дисперсии и вероятности.

# mport numpy as np
# import matplotlib.pyplot as plt

# x = [95, 102.5]
# y = [5, 17]

# x_new = 100

# y_new = np.interp(x_new, x, y)
# print(y_new)
# # 13.0

# plt.plot(x, y, "og-", x_new, y_new, "or");