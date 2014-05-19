#!/usr/bin/env python
import sys
import json
storage = {}
storage["host"] = "10.198.159.221"
storage["path"] = "/storage/vddbair"

task_info = json.load(open(sys.argv[1], 'r'))
task_info["id"] = 1111
task_info["storage"] = storage
task_info["status"] = "submitted"
task_info["uuid"] = task_info["channel"]["uuid"] + "_" + str(task_info["endTimestamp"] / 1000000)
task_info["channel"]["videoUrl"] ="http://121.199.31.48:80/TVAds/videocapture"

with file (sys.argv[2], 'w') as f:
    f.write(json.dumps(task_info))
