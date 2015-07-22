#!/usr/bin/env python
import pandas as pd
import numpy as np


# import config file
import db_config

db_conn_vdashboard = torndb.Connection('192.168.1.19', db_vdashboard_name, user=db_vdashboard_name, password=db_vdashboard_pass)
def get_trackingWebsite_ids(db_vdashboard_name,company_id ):
    sql = """select group_concat(trackingWebsite_id) sample_trackingWebsite_ids from dailyViewsBasicSample where company_id = %s """ % (db_vdashboard_name, company_id)


    return ""
