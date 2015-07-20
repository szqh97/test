#!/usr/bin/env python
import pandas as pd
import numpy as np

with file('/data/gen_test_data.csv', 'w') as of:
    of.write('matchedVideo_id,company_id,report_at,view_count')
    for matchedvideo_id in xrange(1000000):
        for date in pd.date_range('2012-01-01', end='2015-07-07', freq='D'):
            s = ','.join([str(matchedvideo_id), '14', date.strftime('%Y-%m-%d'), str(np.random.randint(1000)), ])
            of.write(s)

