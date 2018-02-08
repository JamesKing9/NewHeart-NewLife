#!/usr/bin/python
# -*- coding: UTF-8 -*-
"""
需求：打印楼梯，同时在楼梯上放打印两个笑脸。
分析：用i控制行， j控制列， j根据 i 的变化来控制输出黑方格的个数。
"""
import sys;
# sys.stdout.write(chr(1)) # ASCII表中 十进制 1 对应的字符是个笑脸
sys.stdout.write(chr(33))
sys.stdout.write(chr(33))
print ''

for i in range(1, 11):
    for j in range(1, i):
        sys.stdout.write(chr(37))
        sys.stdout.write(chr(37))
    print ''
