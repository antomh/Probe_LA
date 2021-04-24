import os

step = 200
MIN_VOLT_MODE_12 = -5000
MAX_VOLT_MODE_12 = 12000
length_mode_12v = int(((-1)*MIN_VOLT_MODE_12+MAX_VOLT_MODE_12)/step)

MIN_VOLT_MODE_27 = -30000
MAX_VOLT_MODE_27 = 30000
length_mode_27v = int(((-1)*MIN_VOLT_MODE_27+MAX_VOLT_MODE_27)/step)

def create_calibrate_table(length_mode_12v,length_mode_27v):

    # Запись файла 
    f = open(r"temp_calibrate_table.txt", "w")

    f.write('//12V'+'\n')
    for item in list(range(length_mode_12v)):
        f.write("%s\n" % item)

    f.write('//27V'+'\n')
    for item in list(range(length_mode_27v)):
        f.write("%s\n" % item)
    f.close()
    
create_calibrate_table(length_mode_12v,length_mode_27v)

# #Чтение файла
# with open("temp_calibrate_table.txt") as ff:
#     lines = [line.rstrip('\n') for line in open('temp_calibrate_table.txt')]
# print("read temp_calibrate_table:",lines)

# Поиск значения напряжения 

# def Volt2Index(volt,mode):
# # x 2400 
#     index = 0

#     if mode == "12v":



#     # return index


# Интерполяция
def findXPoint(xa,xb,ya,yb,yc):
    m = (xa - xb) / (ya - yb)
    xc = (yc - yb) * m + xb
    return xc

def findYPoint(xa,xb,ya,yb,xc):
    m = (ya - yb) / (xa - xb)
    yc = (xc - xb) * m + yb
    return yc