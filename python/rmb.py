#!/usr/bin/env python
from collections import deque
keywords = {1:"壹",2:"贰", 3:"叁", 4:"肆", 5:"伍", 6:"陆", 7:"柒", 8:"捌", 9:"玖", 10:"拾", 100:"佰", 1000:"仟", 10000:"万", 0:r"零"}
def convert(num):

    tens = 0
    outlist = deque()
    outlist.appendleft("圆")
    while num:
        last = num % 10
        tens += 1
        num = num / 10
        if num :
            if last
    


