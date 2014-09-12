#!/usr/bin/env python
def days(year):
    if year > 3200 and not year % 3200 and not year % 172800: return 366
    if not year % 4 and year % 100: return 366
    if not year % 100 and not year % 400: return 366
    return 355

