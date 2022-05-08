# -*- coding:utf-8 -*-
# HoughCircles_Smartphone_Camera.py
# 2022-05-08
# 作者：bamboogun233
# 局域网读取手机摄像头，按下空格进行霍夫变换检测圆计算圆心距离，若圆的个数不足一个会提示没能检测到圆，若圆的个数不足两个会提示距离计算失败

import cv2 as cv
import numpy as np
import math


# 定义点的函数
class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def getx(self):
        return self.x

    def gety(self):
        return self.y


# 定义直线函数
class Getlen:
    def __init__(self, p1, p2):
        self.x = p1.getx() - p2.getx()
        self.y = p1.gety() - p2.gety()
        # 用math.sqrt（）求平方根
        self.len = math.sqrt((self.x ** 2) + (self.y ** 2))

    # 定义得到直线长度的函数
    def getlen(self):
        return self.len


def detect_circle(image):
    """
     作用：圆形检测
     参数：需要检测圆的图片
     返回：检测出圆形的信息
    """
    # 图像灰度处理
    gray_img = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    # 图像二值化处理
    dst = cv.adaptiveThreshold(gray_img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 15, 1)
    # 图像中值滤波处理
    img_median = cv.medianBlur(dst, 5)
    # 图像高斯模糊处理
    gaussian = cv.GaussianBlur(img_median, (3, 3), 0)
    # 霍夫圈变换
    # 参数分别为：image, method, dp, minDist, param1, param2, minRadius, maxRadius
    # 其中：image为灰度图像，method使用的方法为霍夫梯度法，minDist两个圆中心的最小距离
    circles = cv.HoughCircles(img_median, cv.HOUGH_GRADIENT, 1, 30, param1=100, param2=80, minRadius=85, maxRadius=270)
    # 对数据进行取整
    print("取整前信息（圆心[X,Y],半径）：" + str(circles))
    circles = np.uint16(np.around(circles))
    print("取整后信息（圆心[X,Y],半径）：" + str(circles))
    try:
        p1 = Point(int(circles[0, 0, 0]), int(circles[0, 0, 1]))
        p2 = Point(int(circles[0, 1, 0]), int(circles[0, 1, 1]))
        len = Getlen(p1, p2)
        distance = len.getlen()
        print("圆心的距离是：" + str(distance))
    except:
        print('距离计算失败')
    return circles


def draw_circle(img, circles):
    """
     作用：根据圆形信息在图片中绘制圆
     参数1：原始图片信息
     参数2：圆形坐标信息
     返回：无
    """
    for i in circles[0, :]:
        # 绘制圆外圈
        # 参数分别为：圆心、半径、颜色、线框宽度
        cv.circle(img, (i[0], i[1]), i[2], (0, 0, 255), 2)
        # 绘制圆心
        cv.circle(img, (i[0], i[1]), 2, (255, 0, 0), 2)
    cv.imshow("draw_circle_img", img)


if __name__ == '__main__':
    cv.namedWindow("look", 1)
    # 开启ip摄像头
    video = "http://admin:admin@10.25.65.218:8081/"  # http://admin:admin@自己的地址/
    capture = cv.VideoCapture(video)

    num = 0
    while True:
        success, img = capture.read()
        cv.imshow("look", img)
        c = cv.waitKey(10)
        if c == 27:
            # esc键退出
            print("esc break...")
            break
        if c == ord(' '):
            try:
                # 空格键保存一张图像
                # 检测圆
                circles = detect_circle(img)
                # 绘制圆
                draw_circle(img, circles)
                cv.waitKey(0)
                cv.destroyAllWindows()
                # 保存图片到当前文件夹
                # num = num + 1
                # filename = "picture_%s.jpg" % num
                # cv.imwrite(filename, img)
            except:
                print('没能检测到圆')

    capture.release()
    cv.destroyWindow("look")
