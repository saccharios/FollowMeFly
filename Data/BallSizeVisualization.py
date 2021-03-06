'''
======================
3D surface (color map)
======================

Demonstrates plotting a 3D surface colored with the coolwarm color map.
The surface is made opaque by using antialiased=False.

Also demonstrates using the LinearLocator and custom formatting for the
z axis tick labels.
'''



from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np


# plt.close("all")

# 0 - 12 \ # 13 - 25 # 26 - 36 # 37 - 47 # 48 -56 # 57 -66
x_data_z0 = np.array([10 , 20  ,30 , 40 , 50 , 60 , 70 , 80 , 90, 100, 110, 120 ,130 ,\
10  ,20 , 30 , 40,  50,  60 , 70, 80 , 90, 100, 110, 120, 130,\
30,  40 , 50  ,60 , 70 , 80 , 90, 100 ,110, 120, 130,\
30 , 40  ,50 , 60 , 70 , 80 , 90, 100, 110, 120, 130,\
50 , 60  ,70,  80,  90, 100 ,110, 120, 130,\
60 , 70  ,80 , 90 ,100, 110, 120, 130]) 
y_data_z0 = np.array([0,0,0,0,0,0,0,0,0,0,0,0,0,\
10,10,10,10,10,10,10,10,10,10,10,10,10,\
20,20,20,20,20,20,20,20,20,20,20,\
40,40,40,40,40,40,40,40,40,40,40,\
60,60,60,60,60,60,60,60,60,\
80,80,80,80,80,80,80,80])

size_data_z0 = np.array([161.767 , 74.74,  49.21 , 36.51 , 30.38 , 26.5 , 22.79 , 21.15 , 19.807, 17.483, 13.95, 12.39, 12.22,\
148.92 , 86.55, 57.21 , 42.122 , 32.47 , 28.245,  24.85 , 19.92,  18.67, 16.85 ,15.16 ,13.79 ,13.36  ,\
60.51 , 47.03 , 36.61 , 29.83  ,24.63 , 21.85,  19.15 ,15.11 ,14.8 ,12.82 ,12.26,\
47.7 , 41.11 , 36.48, 29.34, 25.85, 22.39, 19.25, 18.06 ,15.22, 13.59, 12.3 ,\
29.44 , 25.84  ,23.25  ,21.03,  18.43, 16.855, 14.31, 14.03, 11.86,\
23.01 , 20.21 ,18.53 ,17.51 ,15.43 ,15.11 ,13.16, 12.53])

y_pix_z0 = np.array([-1.45821,0.811479,1.468,2.008,-0.212,-0.25,-0.00102,-0.43,-0.53578,-0.8714,-2.59,-1.6282,-0.684833,\
236.669, 117.244, 75.129, 54.2736,42.8793,35.3166,29.4924,25.883,22.68,19.58,20.1,19.3972,17.2817,\
149.389, 112.44,87.043,73.0742,59.9595,52.5521,46.5424,42.6058,40.18,37.022,33.6179,\
274.43, 219.412,179.912,152.89,130.67,114.7,100.05,88.88,80.517,73.22,66.29,\
256.27,220.96,193.54,170.795,150.75,135.75,121.84,110.99,101.53,\
271.93,244.21,220.02,198.46,180.35,163.75,149.46,137.8])
z_pix_z0 = np.array([69.357,34.355,23.611,17.17,15.3166,12.977,11.3122,11.23,10.6153,9.925,7.1636,6.8358,6.6,\
65.7308,33.6287,23.5099,17.2972,15.5514,13.5371,12.0561,10.5,10.23,9.86,7.79,7.01336,6.76956,\
23.8434,18.879,16.0877,13.7614,11.7409,11.1331,10.2389,8.35536,7.31,6.724,6.224,\
19.32,16.33,14.166,12.3,11.117,10.816,9.12,8.59,7.28,6.68,6.2,\
12.77,12.01,10.85,8.94,8.84,8.58,7.95,7.5824,7.3,\
10.19,9.93,9.32,8.64,8.1,7.9,7.826,7.24])

# Make data.
X_plot_z0 = np.matrix('10.0  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130')
Y_plot_z0 = np.matrix(' 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 10 10 10 10 10 10 10 10 10 10 10 10 10;20 20 20 20 20 20 20 20 20 20 20 20 20;40 40 40 40 40 40 40 40 40 40 40 40 40;60 60 60 60 60 60 60 60 60 60 60 60 60;80 80 80 80 80 80 80 80 80 80 80 80 80')
Z_size_z0 = np.matrix('161.767  74.74  49.21  36.51  30.38  26.5  22.79  21.15  19.807 17.483 13.95 12.39 12.22;148.92  86.55 57.21  42.122  32.47  28.245  24.85  19.92  18.67 16.85 15.16 13.79 13.36;0  0  60.51  47.03  36.61  29.83  24.63  21.85  19.15 15.11 14.8 12.82 12.26;0  0  47.7  41.11  36.48 29.34 25.85 22.39 19.25 18.06 15.22 13.59 12.3;0 0 0 0 29.44  25.84  23.25  21.03  18.43 16.855 14.31 14.03 11.86;0 0 0 0 0  23.01  20.21 18.53 17.51 15.43 15.11 13.16 12.53')
Y_plot_pix_z0 = np.matrix('1.45821,-0.811479,-1.468,-2.008,0.212,0.25,0.00102,0.43,0.53578,0.8714,2.59,1.6282,0.684833;\
236.669, 117.244, 75.129, 54.2736,42.8793,35.3166,29.4924,25.883,22.68,19.58,20.1,19.3972,17.2817;\
0,0,149.389, 112.44,87.043,73.0742,59.9595,52.5521,46.5424,42.6058,40.18,37.022,33.6179;\
0,0,274.43, 219.412,179.912,152.89,130.67,114.7,100.05,88.88,80.517,73.22,66.29;\
0,0,0,0,256.27,220.96,193.54,170.795,150.75,135.75,121.84,110.99,101.53;\
0,0,0,0,0,271.93,244.21,220.02,198.46,180.35,163.75,149.46,137.8')
Z_plot_pix_z0 = np.matrix('69.357,34.355,23.611,17.17,15.3166,12.977,11.3122,11.23,10.6153,9.925,7.1636,6.8358,6.6;\
65.7308,33.6287,23.5099,17.2972,15.5514,13.5371,12.0561,10.5,10.23,9.86,7.79,7.01336,6.76956;\
0,0,23.8434,18.879,16.0877,13.7614,11.7409,11.1331,10.2389,8.35536,7.31,6.724,6.224;\
0,0,19.32,16.33,14.166,12.3,11.117,10.816,9.12,8.59,7.28,6.68,6.2;\
0,0,0,0,12.77,12.01,10.85,8.94,8.84,8.58,7.95,7.5824,7.3;\
0,0,0,0,0,10.19,9.93,9.32,8.64,8.1,7.9,7.826,7.24')


ranges_z0 = {}
ranges_z0[0] = (0,13)
ranges_z0[1] = (13,26)
ranges_z0[2] = (26,37)
ranges_z0[3] = (37,48)
ranges_z0[4] = (48,57)
ranges_z0[5] = (57,68)


# Calculate x distance from the size. Use a simple Ansatz. Neglect distortions at the edges.
# Ansatz: z(x) = a/x + b
# Reformulate as  b*x+a = z(x)*x
# z_x = np.multiply(size_data_z0, x_data_z0)
# coeffs_z0 = np.polyfit(x_data_z0, z_x, 1)
# print(coeffs_z0)
# best_fit_z0 = np.zeros(13)
# for i in range(0,13):
#     best_fit_z0[i] = coeffs_z0[1] /x_data_z0[i] + coeffs_z0[0]
#     # print(x_data_z0[i], best_fit[i])
# #---------------------------------------------------------------------------------------------------------------------------------------------------
# # Plot focal length on y axis, x constant, z = 3.6
#     
# fig_2d = plt.figure()
# ax = fig_2d.gca()
# for i in range(0,13):
#     distance = X_plot_z0[:,i]
#     df = np.multiply(Y_plot_pix_z0[:,i],distance)
#     df = np.divide(df,Y_plot_z0[:,i])
#     ax.plot(Y_plot_z0[:,i],df,label=str(X_plot_z0[0,i])+' cm')
# 
# ax.legend() 
# ax.set_title('2d plot, focal length given distance (x), z = 3.6')
# ax.set_xlabel('y')
# ax.set_ylabel('focal length,')
# plt.show()  
#     
#---------------------------------------------------------------------------------------------------------------------------------------------------
# 3D size plot, z = 3.6

# 
# fig = plt.figure()
# ax = fig.gca(projection='3d')
# # Plot the surface.
# surf = ax.plot_surface(Y_plot_z0, X_plot_z0, Z_size_z0, cmap=cm.coolwarm,
#                         linewidth=0, antialiased=False)
# 
# ax.set_xlabel('y')
# ax.set_ylabel('x')
# ax.set_zlabel('size')
# # Add a color bar which maps values to colors.
# fig.colorbar(surf, shrink=0.5, aspect=5)
# ax.set_title('3d plot, size of ball, z = 3.6')
# plt.show()

#---------------------------------------------------------------------------------------------------------------------------------------------------
#  2d plot, plot size on y axis, x axis constant, z = 3.6

# fig_2d = plt.figure()
# ax = fig_2d.gca()
# for i in range(0,12):
#     ax.plot(Y_plot_z0[:,i],Z_size_z0[:,i],label=str(X_plot_z0[0,i])+'cm')
# 
# ax.legend() 
# ax.set_title('2d plot, size of ball given distance (x), z = 3.6')
# ax.set_xlabel('y')
# ax.set_ylabel('size')
# plt.show()
# #---------------------------------------------------------------------------------------------------------------------------------------------------
# 2d plot, plot size on x axis, y axis constant
# fig_2d = plt.figure()
# ax = fig_2d.gca()
# for i in range(0,6):
#     ax.plot(np.transpose(X_plot_z0[i,:]),np.transpose(Z_size_z0[i,:]),label=str(Y_plot_z0[i,0])+'cm')
#     
# ax.plot(x_data_z0[0:13],best_fit_z0,label='best fit')  
# ax.legend() 
# ax.set_title('2d plot, size of ball given y, z = 3.6')
# ax.set_xlabel('x')
# ax.set_ylabel('size')
# plt.show()

#---------------------------------------------------------------------------------------------------------------------------------------------------
# 3D size plot, z = 11.9
# X,Y data differs from z = 3.6
X_plot_z1 = np.matrix('10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130;10  20  30  40  50  60  70  80  90 100 110 120 130')
Y_plot_z1 = np.matrix(' 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 10 10 10 10 10 10 10 10 10 10 10 10 10;20 20 20 20 20 20 20 20 20 20 20 20 20;40 40 40 40 40 40 40 40 40 40 40 40 40;60 60 60 60 60 60 60 60 60 60 60 60 60;80 80 80 80 80 80 80 80 80 80 80 80 80')
Z_size_z1 = np.matrix('0  78.84  51.91  39.01  32.07 25.95 22.64  19.31  17.51 16.08 14.6 13.72 12.3;0  83.43 54.97  40.67  33.53  27.74  22.69  19.21  18.49 16.26 15.14 14.13 12.25;0  0  53.35  41.06  33.61  27.82  24.25  20.16  18.92 17.3 15.35 13.61 13.87;0  0  43.05  38.9 33.35 28.19 24.79 22.54 19.65 17.46 16.41 14.76 13.2;0 0 0 0 29.76  27.7  25.34  22.36  20.68 18.81 16.78 15.13 14.6;0 0 0 0 0  23.71  22.24 19.65 19.32 17.74 15.86 14.65 14.32')

Y_plot_pix_z1 = np.matrix('0,2,1.26,-0.75,-2.03,-2.11,-0.18,-1.75,-1.36,-1.89,-0.75,-0.55,-0.83;\
0, 116.51,79.27,56.823,42.52,36.27,29.81,26.85,21.77,20.35,18.46,18.22,16.29;\
0,0,149.61,108.05,89.81,72.12,59.76,52.73,47.09,43.32,37.75,34.36,31.25;\
0,0,271,217.36,179.32,150,130.19,115.56,96.92,87.61,78.57,70.07,64.15;\
0,0,0,0,253.28,220.24,191,166.66,149.19,134.17,119,108.8,100.14;\
0,0,0,0,0,270.04,245.6,217.43,197.66,178.8,160.16,146.71,134.64')

Z_plot_pix_z1 = np.matrix('0,127.59,80.9,61.35,49.73,41.03,35.13,30.47,27.5,24.08,21.91,19.91,17.63;\
0, 133.38, 87.255, 62.68, 51.48,42.63, 35.99,31.22,27.89,24.91,23.4,21.35,17.72;\
0,0,85.49, 63.83,51.03,42.34,36.31,31.22,28.19,25.38,22.39,21.17,18.3;\
0,0,76.76,60.47,50.19,41.6,35.88,31.97,28.06,25.33,22.04,20.05,18.03;\
0,0,0,0,47.56,41.51,36.48,31.73,28.34,25.62,22.35,20.38,18.5;\
0,0,0,0,0,37.52,34.49,30.85,27.866,25.48,22.07,20.26,18.44')
y_pix_z1 = np.array([2,1.26,-0.75,-2.03,-2.11,-0.18,-1.75,-1.36,-1.89,-0.75,-0.55,-0.83,\
116.51,79.27,56.823,42.52,36.27,29.81,26.85,21.77,20.35,18.46,18.22,16.29,\
149.61,108.05,89.81,72.12,59.76,52.73,47.09,43.32,37.75,34.36,31.25,\
271,217.36,179.32,150,130.19,115.56,96.92,87.61,78.57,70.07,64.15,\
253.28,220.24,191,166.66,149.19,134.17,119,108.8,100.14,\
270.04,245.6,217.43,197.66,178.8,160.16,146.71,134.64])

z_pix_z1 = np.array([0,127.59,80.9,61.35,49.73,41.03,35.13,30.47,27.5,24.08,21.91,19.91,17.63,\
133.38, 87.255, 62.68, 51.48,42.63, 35.99,31.22,27.89,24.91,23.4,21.35,17.72,\
85.49, 63.83,51.03,42.34,36.31,31.22,28.19,25.38,22.39,21.17,18.3,\
76.76,60.47,50.19,41.6,35.88,31.97,28.06,25.33,22.04,20.05,18.03,\
47.56,41.51,36.48,31.73,28.34,25.62,22.35,20.38,18.5,\
37.52,34.49,30.85,27.866,25.48,22.07,20.26,18.44])
x_data_z1 = np.array([ 20  ,30 , 40 , 50 , 60 , 70 , 80 , 90, 100, 110, 120 ,130 ,\
20 , 30 , 40,  50,  60 , 70, 80 , 90, 100, 110, 120, 130,\
30,  40 , 50  ,60 , 70 , 80 , 90, 100 ,110, 120, 130,\
30 , 40  ,50 , 60 , 70 , 80 , 90, 100, 110, 120, 130,\
50 , 60  ,70,  80,  90, 100 ,110, 120, 130,\
60 , 70  ,80 , 90 ,100, 110, 120, 130]) 
y_data_z1 = np.array([0,0,0,0,0,0,0,0,0,0,0,0,\
10,10,10,10,10,10,10,10,10,10,10,10,\
20,20,20,20,20,20,20,20,20,20,20,\
40,40,40,40,40,40,40,40,40,40,40,\
60,60,60,60,60,60,60,60,60,\
80,80,80,80,80,80,80,80])

size_data_z1 = np.array([78.84 , 51.91 , 39.01  ,32.07, 25.95, 22.64 , 19.31 , 17.51 ,16.08, 14.6, 13.72 ,12.3,\
83.43, 54.97 , 40.67 , 33.53 , 27.74 , 22.69 , 19.21 , 18.49 ,16.26, 15.14, 14.13, 12.25,\
53.35 , 41.06  ,33.61,  27.82 , 24.25 , 20.16,  18.92 ,17.3, 15.35, 13.61 ,13.87,\
43.05 , 38.9 ,33.35 ,28.19, 24.79, 22.54, 19.65 ,17.46, 16.41, 14.76 ,13.2,\
29.76 , 27.7 , 25.34 , 22.36 , 20.68, 18.81, 16.78 ,15.13, 14.6,\
23.71  ,22.24 ,19.65 ,19.32 ,17.74 ,15.86, 14.65 ,14.32])


# 
# fig = plt.figure()
# ax = fig.gca(projection='3d')
# # Plot the surface.
# surf = ax.plot_surface(Y_plot_z1, X_plot_z1, Z_size_z1, cmap=cm.coolwarm,
#                         linewidth=0, antialiased=False)
# 
# ax.set_xlabel('y')
# ax.set_ylabel('x')
# ax.set_zlabel('size')
# # Add a color bar which maps values to colors.
# fig.colorbar(surf, shrink=0.5, aspect=5)
# ax.set_title('3d plot, size of ball, z = 11.9')
# plt.show()
# 
#---------------------------------------------------------------------------------------------------------------------------------------------------
# 2d plot, plot size on y axis, x axis constant, z = 11.9
# fig_2d = plt.figure()
# ax = fig_2d.gca()
# for i in range(0,12):
#     ax.plot(Y_plot_z1[:,i],Z_size_z1[:,i],label=str(X_plot_z1[0,i])+'cm')
# 
# ax.legend() 
# ax.set_title('2d plot, size of ball given distance (x), z = 11.9')
# ax.set_xlabel('y')
# ax.set_ylabel('size')
# plt.show()
# 

# Calculate x distance from the size. Use a simple Ansatz. Neglect distortions at the edges.
# Ansatz: z(x) = a/x + b
# Reformulate as  b*x+a = z(x)*x
# z1_x = np.multiply(size_data_z1, x_data_z1)
# coeffs_z1 = np.polyfit(x_data_z1, z1_x, 1)
# print(coeffs_z1)
# best_fit_z1 = np.zeros(12)
# for i in range(0,12):
#     best_fit_z1[i] = coeffs_z1[1] /x_data_z1[i] + coeffs_z1[0]


# 2d plot, plot size on x axis, y axis constant
# fig_2d = plt.figure()
# ax = fig_2d.gca()
# for i in range(0,6):
#     ax.plot(np.transpose(X_plot_z1[i,:]),np.transpose(Z_size_z1[i,:]),label=str(Y_plot_z1[i,0])+'cm')
# ax.plot(x_data_z1[0:12],best_fit_z1,label='best fit') 
# ax.plot(x_data_z0[1:13],best_fit_z0[1:13],label='best fit z0') 
# ax.legend() 
# ax.set_title('2d plot, size of ball given y, z = 11.9')
# ax.set_xlabel('x')
# ax.set_ylabel('size')
# plt.show()

# Plot focal length on y axis, x constant, z = 11.9
    
# fig_2d = plt.figure()
# ax = fig_2d.gca()
# for i in range(1,12):
#     distance = X_plot_z1[:,i]
#     df = np.multiply(Y_plot_pix_z1[:,i],distance)
#     df = np.divide(df,Y_plot_z1[:,i])
#     ax.plot(Y_plot_z1[:,i],df,label=str(X_plot_z1[0,i])+' cm')
# 
# ax.legend() 
# ax.set_title('2d plot, focal length given distance (x), z = 11.9')
# ax.set_xlabel('y')
# ax.set_ylabel('focal length,')
# plt.show()  
#---------------------------------------------------------------------------------------------------------------------------------------------------
# Take all measurements and make one huge Ax = b, given df constant, then repeat over multiple df's and plot

all_x_data = np.concatenate((x_data_z0,x_data_z1))
all_y_data = np.concatenate((y_data_z0,y_data_z1))
all_z_data = np.concatenate((np.ones(np.size(x_data_z0))*3.6,np.ones(np.size(x_data_z1))*11.9))
all_size_measurement = np.concatenate((size_data_z0,size_data_z1))
all_y_pix = np.concatenate((y_pix_z0,y_pix_z1))
all_z_pix = np.concatenate((z_pix_z0,z_pix_z1))

df_array = np.arange(200,241,0.5)
residuals = np.zeros(np.size(df_array))
output = []
idx = 0
for df in df_array:
    # Create A matrix
    A_matrix = np.zeros((np.size(all_y_pix)*3,2))
    b_vector = np.zeros((np.size(all_y_pix)*3,1))
    for i in range (0,np.size(all_y_pix)):
        A_matrix[i*3][0] = 1/ all_size_measurement[i]
        A_matrix[i*3][1] = 1
        A_matrix[i*3+1][0] = all_y_pix[i]/ all_size_measurement[i]/df
        A_matrix[i*3+1][1] = all_y_pix[i]/ df
        A_matrix[i*3+2][0] = all_z_pix[i]/ all_size_measurement[i]/df
        A_matrix[i*3+2][1] = all_z_pix[i]/df
        b_vector[i*3] = all_x_data[i]
        b_vector[i*3+1] = all_y_data[i]
        b_vector[i*3+2] = all_z_data[i]
    output.append( np.linalg.lstsq(A_matrix, b_vector))
    residuals[idx] = output[idx][1]
    idx +=1
# Plot residuals over df's 
fig_2d = plt.figure()
ax = fig_2d.gca()

ax.plot(df_array,residuals)
ax.set_title('residuals over df')
ax.set_xlabel('df (focal length)')
ax.set_ylabel('residuals,')
plt.show()

min_idx = np.argmin(residuals)
print('Best a = ' ,output[min_idx][0][0],', b = ' ,output[min_idx][0][1], ', df = ' , df_array[min_idx])

#---------------------------------------------------------------------------------------------------------------------------------------------------
# New Ansatz, the size is a function of the distance, not x --->> BAD IDEA
# distance_array = np.zeros(np.size(all_x_data))
# for i in range (0, np.size(all_x_data)):
#     distance_array[i] = np.sqrt(all_x_data[i]*all_x_data[i] + all_y_data[i]*all_y_data[i] + all_z_data[i]*all_z_data[i])
# 
# 
# # Ansatz: z(d) = a/d + b
# # Reformulate as  b*xda = z(x)*d
# d_x = np.multiply(distance_array, all_size_measurement)
# coeffs_dx = np.polyfit(all_size_measurement, d_x, 1)
# print(coeffs_dx)
