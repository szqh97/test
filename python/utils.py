#!/usr/bin/env python
import datetime
import pandas as pd
import numpy as np

# report_at : string
# dataframe : pd.DataFrame
# for exampel reaport_at is '3-11'
def get_daily_viewcount(report_at, dataframe):
    #FIXME
    index = dataframe[dataframe == report_at].index[0]
    #case 1: only 3-11 in dataframe
    if index == 0:
        return dataframe[dataframe == report_at].view_count.iloc[0]
    #case 1: 3-10,3-11 all in dataframe
    d_report_at = datetime.datetime.strptime(report_at, '%Y-%m-%d')
    prev_day = d_report_at + datetime.timedelta(-1)
    prev_day = prev_day.strftime('%Y-%m-%d')
    prev_created_at = datetime.datetime.strptime(dataframe.iloc[index-1].created_at, '%Y-%m-%d')
    delta_days = (d_report_at - prev_created_at).days
    if not dataframe[dataframe.created_at == report_at].empty and dataframe.iloc[index-1].created_at != prev_day:
        return (dataframe.loc[index].view_count-dataframe.loc[index-1].view_count) / delta_days 


