#[-5:12:0,2]
#[-5:27:0,2]
# x0 -5000 | y0 0
# x1 12000 | y1 85
# length_mode_12v = int(((-1)*MIN_VOLT_MODE_12+MAX_VOLT_MODE_12)/step_calibrate)

# MIN_VOLT_MODE_27 = -27000
# MAX_VOLT_MODE_27 = 27000
# length_mode_27v = int(((-1)*MIN_VOLT_MODE_27+MAX_VOLT_MODE_27)/step_calibrate)


Ktr = 1.04
minVolt = -5000
maxVolt = 12000

x0 = abs(minVolt)
x1 = abs(maxVolt)

step = 200
count = (x0+x1)/step



y0 = 0
y1 = count

b = (count*x0)/(x0+x1)
a = b/x0

x = 300 #/ Ktr!!!!!!!!!!!!!!
y = a*x+b
print(y)
#--------------------------
aX = x

Ca0 = 2167
Ca1 = 2225
a0 = 200
a1 = 400

CodeX = (((Ca1-Ca0)/(a1-a0)))*(aX-a0)+Ca0
print((CodeX))


# # Параметры щупа
# step_calibrate = 200
# MIN_VOLT_MODE_12 = -12000
# MAX_VOLT_MODE_12 = 12000
# length_mode_12v = int(((-1)*MIN_VOLT_MODE_12+MAX_VOLT_MODE_12)/step_calibrate)

# MIN_VOLT_MODE_27 = -27000
# MAX_VOLT_MODE_27 = 27000
# length_mode_27v = int(((-1)*MIN_VOLT_MODE_27+MAX_VOLT_MODE_27)/step_calibrate)



# dacValA = 0
# dacValB = 0

# dacValZero_m12 = 2048
# dacValMin_A_m12 = 0
# dacValMax_A_m12 = 4095
# dacValMin_B_m12 = 0
# dacValMax_B_m12 = 4095

# dacValZero_m27 = 2048
# dacValMin_A_m27 = 0
# dacValMax_A_m27 = 4095
# dacValMin_B_m27 = 0
# dacValMax_B_m27 = 4095





















