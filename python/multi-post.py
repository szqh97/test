import httplib2, mimetypes


def post2_multipart(host, fields, files):
    content_type, body = encode_multipart_formdata(fields, files)
    h = httplib2.Http(disable_ssl_certificate_validation=True)
    headers = {'Content-Type':content_type}
    resp, content = h.request(host, method='POST', body=body, headers=headers)
    return resp, content
    print resp
    print content

def encode_multipart_formdata(fields, files):
    """
    fields is a sequence of (name, value) elements for regular form fields.
    files is a sequence of (name, filename, value) elements for data to be uploaded as files
    Return (content_type, body) ready for httplib.HTTP instance
    """
    BOUNDARY = '----------ThIs_Is_tHe_bouNdaRY_$'
    CRLF = '\n'
    L = []
    for (key, value) in fields:
        L.append('--' + BOUNDARY)
        L.append('Content-Disposition: form-data; name="%s"' % key)
        L.append('Content-Type: text/plain; charset=US-ASCII')
        L.append('Content-Transfer-Encoding: 8bit')
        L.append('')
        L.append(value)
    for (key, filename, value) in files:
        L.append('--' + BOUNDARY)
        L.append('Content-Disposition: form-data; name="%s"; filename="%s"' % (key, filename))
        L.append('Content-Type: %s' % 'application/octet-stream' )
        L.append('Content-Transfer-Encoding: binary')
        L.append('')
        L.append(value)
    L.append('--' + BOUNDARY + '--')
    body = CRLF.join(L)
    content_type = 'multipart/form-data; boundary=%s' % BOUNDARY
    return content_type, body


if __name__ == '__main__':
    file1 = '/home/li_yun/attach/df7c4d3db06f4bfcb2a5d486d704e0aa.war'
    file2 = '/home/li_yun/attach/df7c4d3db06f4bfcb2a5d486d704e0aa.war.md5'
    md5_context = open(file1, 'rb').read()
    file_context = open(file2, 'rb').read()
    content_type,body = encode_multipart_formdata([('file1', file1), ('file2', file2)], [('file1', file1, file_context), ('file2', file2, md5_context)] )
    print content_type
    print '==============='
    print body
    #print body
    resp, content = post2_multipart('http://192.168.1.13/upload/', [('file1', file1), ('file2', file2)], [('file1', file1, file_context), ('file2', file2, md5_context)] )
    print resp
    print content

