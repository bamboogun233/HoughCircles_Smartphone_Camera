# -*- coding:utf-8 -*-
# HoughCircles_Smartphone_Camera.py
# 2022-05-08
# 作者：bamboogun233
# 局域网读取手机摄像头，按下空格进行霍夫变换检测圆计算圆心距离，若圆的个数不足一个会提示没能检测到圆，若圆的个数不足两个会提示距离计算失败
使用方法：
下载IP摄像头APP或者利用其他方法将自己的摄像头的数据传输到局域网IP
将代码第90行的IP地址替换成自己的IP地址    video = "http://admin:admin@10.25.65.218:8081/"  # http://admin:admin@自己的地址/
