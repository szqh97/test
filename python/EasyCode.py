#-*- coding:utf-8 -*-
import os,sys
import traceback
import chardet, io
from collections import OrderedDict

INFO_LOG  = 3
DEBUG_LOG = 2

glb_logLevel = 2
def log(a):
    if glb_logLevel <= INFO_LOG:
        print 'INFO:',a
def debug(a):
    if glb_logLevel <= DEBUG_LOG:
        print 'DBUG:',a
def error(a):
    print 'EROR:',a

SQL_KEY_ARRAY  = ['CREATE','create','TABLE','table','PRIMARY','primary','KEY','key','DROP','drop','INDEX','ENGINE','UNIQUE']
TYPE_KEY_MAP = {
    'mediumint':'uint32_t',
    'varchar':'string',
    'char':'string',
    'tinyint':'uint8_t',
    'smallint':'uint8_t',
    'int':'uint32_t',
    }

class TableTemplate:
    def __init__(self, fileName):
        self.file_name = fileName
        self.table_field_map = OrderedDict()
        self.primary_key = None
        self.auto_increment = None
        self.table_name = fileName.split('.')[0]
        self.include_name = 'DB%s' % self.table_name
        self.struct_name = 'DB%s_t' % self.table_name
        self.class_name = 'C%s' % self.table_name
        self.header_file_name = 'DB%s.h' % self.table_name
        self.cpp_file_name = 'DB%s.cpp' % self.table_name
        log('will create header file: %s' % self.header_file_name)
        log('will create cpp file   : %s' % self.cpp_file_name)

    def getTableField(self):
        if not os.path.exists(self.file_name):
            error('%s not exists' % self.file_name)
            exit(1)

        # detect file encoding
        encoding = None
        with open(self.file_name, 'rb') as file:
            raw = file.read(32) # at most 32 bytes are returned
            encoding = chardet.detect(raw)['encoding']
            if encoding == 'ascii':
                encoding = None

        index = 0
        for line in io.open(self.file_name, encoding=encoding):
            index = index + 1
            line = line.strip(' ')
            line = line.replace('`','')
            line = line.replace('(',' ')
            line = line.replace(')',' ')
            line = line.replace('=',' ')
            lineArray = line.split()
            if lineArray[0] in SQL_KEY_ARRAY or len(lineArray) <= 2:
                if (lineArray[0] == 'PRIMARY' or lineArray[0] == 'parimay') and (lineArray[1] == 'KEY' or lineArray[1] == 'key'):
                    self.primary_key = lineArray[2]
                continue
            if line.find('AUTO_INCREMENT') >= 0:
                self.auto_increment = lineArray[0]
            #debug('%d:%s' % (index, line))
            #debug(' %s' % lineArray)
            self.table_field_map[lineArray[0]] = TYPE_KEY_MAP[ lineArray[1].split('(')[0] ]

    def createHeaderFile(self):
        if os.path.exists(self.header_file_name):
            os.remove(self.header_file_name)
        fd = open(self.header_file_name,'w')

        #头文件部分 防止重复包含
        head1 = '#ifndef __%s__H__\n' % self.include_name.upper()
        head2 = '#define __%s__H__\n' % self.include_name.upper()
        head3 = '#include <list>\n#include "public_define.h"\n\nusing namespace std;\n'
        fd.write(head1)
        fd.write(head2)
        fd.write(head3)

        #------------------------开始结构体字符串生成-------------------------
        #数据库记录对应的结构体/类格式
        structBox = 'class %s {\n\n%s\n};\n\n'

        #表结构对应的类对象 成员变量部分
        table2filedBox = 'private:\n'
        #对应变量是否被使用标志
        filed2hasBox = 'public:\n'
        #设置变量内敛函数
        function2Box = 'public:\n'
        #构造函数模版
        init2Str = '\n'
        new2Box = 'public:\n    %s()\n    {%s    }\n'

        for k,v in self.table_field_map.items():
            #成员变量-对应表字段
            tmpStr1 = '    %s %s;\n' % (v,k)
            table2filedBox += tmpStr1
            #增加变量-标识是否被使用/赋值
            tmpStr2 = '    bool has_%s;\n' % k
            filed2hasBox += tmpStr2 
            #赋值函数-标识被使用-隐式内敛函数
            tmpStr3 = '    void set_%s(%s value) { %s = value; has_%s = true;}\n' % (k, v, k, k)
            tmpStr3x= '    %s get_%s() { return %s; }\n\n' % (v, k, k)
            function2Box += tmpStr3
            function2Box += tmpStr3x
            #构造函数中初始化字符串
            tmpStr4 = '        has_%s = false;\n' % k
            if v == 'string':
                tmpStr5 = '        %s = "";\n' % k
            else:
                tmpStr5 = '        %s = 0;\n' % k
            init2Str += tmpStr4
            init2Str += tmpStr5

        #构造函数
        new2Box = new2Box % (self.struct_name, init2Str)
        structBox = structBox % (self.struct_name,table2filedBox+filed2hasBox+function2Box+new2Box)
        #------------------------结束结构体字符串生成-------------------------

        #------------------------开始单例类字符串生成-------------------------
        #对外使用的单例类结构
        singlonBox = 'class %s\n{\n\n%s\n};\n'
        publicFunBox = 'public:\n'
        publicFunBox += '    static %s* getInstance();\n' % self.class_name
        publicFunBox += '    ~%s(){}\n\n' % self.class_name
        publicFunBox += '    bool insertRecord( %s& value);\n' % self.struct_name
        publicFunBox += '    void deleteRecord( %s& value);\n' % self.struct_name
        publicFunBox += '    bool updateRecord( %s& condition,  %s& value);\n' % (self.struct_name,self.struct_name)
        publicFunBox += '    void selectRecord(%s& value);\n' % self.struct_name
        publicFunBox += '    void selectRecords(%s& value, list<%s>& result);\n' % (self.struct_name,self.struct_name)
        privateFunBox = 'private:\n    %s(){}\nprivate:\n    static %s* m_pInstance;\n' % (self.class_name,self.class_name)
        singlonBox = singlonBox % (self.class_name, publicFunBox+privateFunBox)
        #------------------------结束单例类字符串生成-------------------------
        fd.write(structBox)
        fd.write(singlonBox)
        tailStr = '#endif'
        fd.write(tailStr)
        fd.close()

    def _createInsert2(self):
        templateInsert = '\nbool %s::insertRecord( %s& value)\n{%s}\n'
        templateCheck = '\n\
    bool bRet = false;\n\
    CDBManager* pDBManager = CDBManager::getInstance();\n\
    CDBConn* pDBConn = pDBManager->GetDBConn("teamtalk_master");\n\
    if (pDBConn)\n\
    {\n\
%s\n\
    }\n\
    else\n\
    {\n\
        error("no db connection for teamtalk_master");\n\
    }\n\
    return bRet;\n\
'
        sqlCharBuff = '        string sqlFromat="%s";\n'
        insertSqlFormat = 'REPLACE INTO %s (%s) VALUES(%s)'
        fieldStr = ''
        listValue = ''
        valueStr = ''
        div = ''
        bBegin = True
        for k,v in self.table_field_map.items():
            #插入跳过自增字段
            if k == self.auto_increment:
                continue
            fieldStr += '%s%s' % (div, k)
            if v == 'string':
                valueStr += (div+'\\"%s\\"')
                listValue += '%svalue.get_%s().c_str()' % (div,k)
            else:
                valueStr += (div+'%d')
                listValue += '%svalue.get_%s()' % (div,k)
            if bBegin:
                bBegin = False
                div =','
        insertSqlFormat = insertSqlFormat % (self.table_name,fieldStr,valueStr)
        sqlCharBuff = sqlCharBuff % (insertSqlFormat)
        sqlString = '        char czSql[512];\n        sprintf(czSql,sqlFromat.c_str(),%s);\n' % (listValue)
        sqlBox = sqlCharBuff + sqlString
        executeString = '\
        string strSql=czSql;\n\
        bRet = pDBConn->ExecuteUpdate(strSql.c_str());\n\
        if(!bRet)\n\
        {\n\
            error("update failed:%s", strSql.c_str());\n\
        }\n\
        pDBManager->RelDBConn(pDBConn);'
        sqlBox += executeString
        templateCheck = templateCheck % sqlBox
        templateInsert = templateInsert % (self.class_name,self.struct_name,templateCheck)
        return templateInsert

    def _createInsert(self):
        templateInsert = '\nbool %s::insertRecord(%s& value)\n{%s}\n'
        #获取db连接
        templateDB = '\n\
    bool bRet = false;\n\
    CDBManager* pDBManager = CDBManager::getInstance();\n\
    CDBConn* pDBConn = pDBManager->GetDBConn("teamtalk_master");\n\
    if (pDBConn)\n\
    {\n\
        %s\n\
        bRet = pDBConn->ExecuteUpdate(strSql.c_str());\n\
        if(!bRet)\n\
        {\n\
             error("insert failed:%%s", strSql.c_str());\n\
        }\n\n\
        pDBManager->RelDBConn(pDBConn);\n\
    }\n\
    else\n\
    {\n\
        error("no db connection for teamtalk_master");\n\
    }\n\
    return bRet;\n'

        #sql字符串拼接
        codeBox = 'string strField, strFormat, strValue, splitDiv;\n        splitDiv = "";\n'
        field_split = '\
        if(value.has_%s)\n\
        {\n%s\
            splitDiv = ", ";\n\
        }\n'

        fieldBox = ''
        for k,v in self.table_field_map.items():
            strField = ''
            strFormat = ''
            formatSplit = ''
            strField = strField + '            strField += (splitDiv + "%s");\n' % k
            if v == 'string':
                strFormat = strFormat + '            strValue += (splitDiv + value.get_%s());\n' % k
            else:
                strFormat = strFormat + '            strValue += (splitDiv + int2string(value.get_%s()));\n' % k
            fieldBox = field_split % (k, strField + strFormat)
            codeBox += fieldBox

        strSql = '\n        string strSql = "REPLACE INTO ' + self.table_name + '(" + strField + ") VALUES (" + strValue + ")";\n'
        codeBox = codeBox + strSql

        templateDB = templateDB % codeBox
        templateInsert = templateInsert % (self.class_name, self.struct_name, templateDB)
        return templateInsert
    def _createDelete(self):
        #不提供删除函数
        templateDelete = '\nvoid %s::deleteRecord( %s& value)\n{\n\n}\n' % (self.class_name, self.struct_name)
        return templateDelete
    def _createUpdate(self):
        templateUpdate = '\nbool %s::updateRecord( %s& condition,  %s& value)\n{%s}\n'
        #获取db连接
        templateDB = '\n\
    bool bRet = false;\n\
    CDBManager* pDBManager = CDBManager::getInstance();\n\
    CDBConn* pDBConn = pDBManager->GetDBConn("teamtalk_master");\n\
    if (pDBConn)\n\
    {\n\
        %s\n\
        bRet = pDBConn->ExecuteUpdate(strSql.c_str());\n\
        if(!bRet)\n\
        {\n\
             error("update failed:%%s", strSql.c_str());\n\
        }\n\n\
        pDBManager->RelDBConn(pDBConn);\n\
    }\n\
    else\n\
    {\n\
        error("no db connection for teamtalk_master");\n\
    }\n\
    return bRet;\n'

        #sql字符串拼接
        codeBox = 'string strSetList, strWhereList, whereDiv, setDiv;\n        whereDiv = "";\n        setDiv = "";\n'

        conditon_split = '\
        if(condition.has_%s)\n\
        {\n%s\
            whereDiv = " and";\n\
        }\n'
        value_split = '\
        if(value.has_%s)\n\
        {\n%s\
            setDiv = ", ";\n\
        }\n'

        for k,v in self.table_field_map.items():
            whereList = ''
            setList = ''
            if v == 'string':
                whereList = whereList + '            strWhereList = strWhereList + whereDiv + " %s=" + condition.get_%s();\n' % (k,k)
                #更新字段跳过主键 和自增字段
                if k != self.primary_key and k != self.auto_increment:
                    setList = setList + '            strSetList = strSetList + setDiv + " %s=" + value.get_%s();\n' % (k,k)
            else:
                whereList = whereList + '            strWhereList = strWhereList + whereDiv + " %s=" + int2string(condition.get_%s());\n' % (k,k)
                #更新字段跳过主键 和自增字段
                if k != self.primary_key and k != self.auto_increment:
                    setList = setList + '            strSetList = strSetList + setDiv + " %s=" + int2string(value.get_%s());\n' % (k,k)

            whereString = conditon_split % (k, whereList)
            #更新字段跳过主键 和自增字段
            if setList == '':
                setString = ''
            else:
                setString = value_split % (k, setList)
            codeBox = codeBox + setString + whereString

        strSql = '\n        string strSql = "UPDATE ' + self.table_name + ' SET " + strSetList + " WHERE " + strWhereList;'
        codeBox = codeBox + strSql

        templateDB = templateDB % codeBox
        templateUpdate = templateUpdate % (self.class_name, self.struct_name, self.struct_name, templateDB)
        return templateUpdate
    def _createSelect1(self):
        templateSelect = '\nvoid %s::selectRecord(%s& value)\n{%s}\n'
        #获取db连接
        templateDB = '\n\
    CDBManager* pDBManager = CDBManager::getInstance();\n\
    CDBConn* pDBConn = pDBManager->GetDBConn("teamtalk_slave");\n\
    if (pDBConn)\n\
    {\n\
        %s\n\
        CResultSet* pResultSet = pDBConn->ExecuteQuery(strSql.c_str());\n\
        if(pResultSet)\n\
        {\n\
            while (pResultSet->Next())\n\
            {\n%s\
            }\n\
            delete pResultSet;\n\
        }\n\
        else\n\
        {\n\
            error("select none:%%s", strSql.c_str());\n\
        }\n\n\
        pDBManager->RelDBConn(pDBConn);\n\
    }\n\
    else\n\
    {\n\
        error("no db connection for teamtalk_slave");\n\
    }\n'

        #sql字符串拼接
        codeBox = 'string strWhereList;\n'
        setBox = ''
        conditon_split = '        if(value.has_%s)\n        {\n%s        }\n'
        for k,v in self.table_field_map.items():
            whereList = ''
            setLine = ''
            if v == 'string':
                whereList = whereList + '            strWhereList = strWhereList + " AND %s=" + value.get_%s();\n' % (k,k)
                setLine = setLine + '                value.set_%s(pResultSet->GetString("%s"));\n'
            else:
                whereList = whereList + '            strWhereList = strWhereList + " AND %s=" + int2string(value.get_%s());\n' % (k,k)
                setLine = setLine + '                value.set_%s(pResultSet->GetInt("%s"));\n'
            setLine = setLine % (k, k)
            whereString = conditon_split % (k, whereList)
            codeBox = codeBox + whereString
            setBox += setLine

        strSql = '\n        string strSql = "SELECT * FROM ' + self.table_name + ' WHERE 1=1 " + strWhereList;'
        codeBox += strSql

        templateDB = templateDB % (codeBox, setBox)
        templateSelect = templateSelect % (self.class_name, self.struct_name, templateDB)
        return templateSelect
    def _createSelect2(self):
        templateSelect = '\nvoid %s::selectRecords(%s& value, list<%s>& result)\n{%s}\n'
        #获取db连接
        templateDB = '\n\
    CDBManager* pDBManager = CDBManager::getInstance();\n\
    CDBConn* pDBConn = pDBManager->GetDBConn("teamtalk_slave");\n\
    if (pDBConn)\n\
    {\n\
        %s\n\
        CResultSet* pResultSet = pDBConn->ExecuteQuery(strSql.c_str());\n\
        if(pResultSet)\n\
        {\n\
            while (pResultSet->Next())\n\
            {\n%s\
            }\n\
            delete pResultSet;\n\
        }\n\
        else\n\
        {\n\
            error("select none:%%s", strSql.c_str());\n\
        }\n\n\
        pDBManager->RelDBConn(pDBConn);\n\
    }\n\
    else\n\
    {\n\
        error("no db connection for teamtalk_slave");\n\
    }\n'

        #sql字符串拼接
        codeBox = 'string strWhereList;\n'
        setBox = ''
        conditon_split = '        if(value.has_%s)\n        {\n%s        }\n'
        setBox = '                %s tmp;\n' % self.struct_name
        for k,v in self.table_field_map.items():
            whereList = ''
            setLine = ''
            if v == 'string':
                whereList = whereList + '            strWhereList = strWhereList + " AND %s=" + value.get_%s();\n' % (k,k)
                setLine = setLine + '                tmp.set_%s(pResultSet->GetString("%s"));\n'
            else:
                whereList = whereList + '            strWhereList = strWhereList + " AND %s=" + int2string(value.get_%s());\n' % (k,k)
                setLine = setLine + '                tmp.set_%s(pResultSet->GetInt("%s"));\n'
            setLine = setLine % (k, k)
            whereString = conditon_split % (k, whereList)
            codeBox = codeBox + whereString
            setBox += setLine

        setBox += '                result.push_back(tmp);\n'
        strSql = '\n        string strSql = "SELECT * FROM ' + self.table_name + ' WHERE 1=1 " + strWhereList;'
        codeBox += strSql

        templateDB = templateDB % (codeBox, setBox)
        templateSelect = templateSelect % (self.class_name, self.struct_name, self.struct_name, templateDB)
        return templateSelect

    def createCppFile(self):
        if os.path.exists(self.cpp_file_name):
            os.remove(self.cpp_file_name)
        fd = open(self.cpp_file_name,'w')

        #包含头文件和初始化
        head1 = '#include "%s"\n\n' % self.header_file_name
        head2 = '#include \"../DBPool.h\"\n#include \"../CachePool.h\"\n'
        head3 = '%s* %s::m_pInstance = NULL;\n\n' % (self.class_name, self.class_name)
        head = head1 + head2 + head3

        #单例句柄获取函数
        getInstance = '%s* %s::getInstance()\n{\n    if(m_pInstance == NULL)\n    {\n        m_pInstance = new %s();\n    }\n    return m_pInstance;\n}\n'
        getInstance = getInstance % (self.class_name, self.class_name, self.class_name)

        functionStr = None
        #insertRecord函数
        functionInsert = self._createInsert()
        #deleteRecord函数
        functionDelete = self._createDelete()
        #updateRecord函数
        functionUpdate = self._createUpdate()
        #selectRecord函数
        functionSelect1 = self._createSelect1()
        functionSelect2 = self._createSelect2()
        functionStr = functionInsert + functionDelete + functionUpdate + functionSelect1 + functionSelect2

        fd.write(head + getInstance + functionStr)
        fd.close()

if __name__ == '__main__':

    try:
        table = TableTemplate('TableName.txt')

        table.getTableField()
        table.createHeaderFile()
        table.createCppFile()
    except Exception,e:
        print Exception,e
        print traceback.print_exc()
    finally:
        exit(0)