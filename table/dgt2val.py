#[-5:12:0,2]
#[-5:27:0,2]
# x0 -5000 | y0 0
# x1 12000 | y1 85
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

x = 300 #/ Ktr
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






















