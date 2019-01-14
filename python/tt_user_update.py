#!/usr/bin/env python
# -*- coding: utf-8 -*-
import torndb
kpdbhost='10.117.60.85'
kpdbname='kaipao'
kpdbuser='kaipao'
kpdbpass='kaipao'

imdbhost='10.168.31.125'
imdbname='teamtalk'
imdbuser='dongjia'
imdbpass='vPf_v6cd@123'

kpconn = torndb.Connection(kpdbhost, kpdbname, user=kpdbuser, password=kpdbpass)
imconn = torndb.Connection(imdbhost, imdbname, user=imdbuser, password=imdbpass)
sql = "select uid, username, avatar from kp_user  where createtm != updatetm and createtm !=0 "
res = kpconn.query(sql)
f = file('./imuser_update.sql', 'w')
for u in  res:
    name = 'dj{}'.format(u.uid)
    nick = u.username
    if nick.find("'") != -1:
        continue
    avatar = u.avatar
    if avatar.startswith('T3'):
        avatar = 'http://file.kaipao.cc/{}'.format(avatar)
    update_sql = """update IMUser set nick = '{nick}', avatar = '{avatar}', updated = unix_timestamp() where name = '{name}';\n""".format(nick=nick, avatar=avatar, name=name)
    try:
        res = imconn.execute(update_sql)
    except Exception as e:
        print update_sql 

    f.write(update_sql)
    #f.write('executeout: {}'.format(res))

f.flush()
f.close()
kpconn.close()
imconn.close()

