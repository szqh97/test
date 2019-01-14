import httplib2, mimetypes


def post2_multipart(host, files):
    content_type, body = encode_multipart_formdata( files)
    h = httplib2.Http(disable_ssl_certificate_validation=True)
    headers = {'Content-Type':content_type}
    resp, content = h.request(host, method='POST', body=body, headers=headers)
    print resp
    print content
    return resp, content

def encode_multipart_formdata(img_file):
    """
    fields is a sequence of (name, value) elements for regular form fields.
    files is a sequence of (name, filename, value) elements for data to be uploaded as files
    Return (content_type, body) ready for httplib.HTTP instance

    """

    content_type = "Content-Type: multipart/form-data; boundary=WebKitFormBoundary8riBH6S4ZsoT69so"
    body = "--WebKitFormBoundary8riBH6S4ZsoT69so\r\nContent-Disposition: form-data; name=\"file\"; filename=\"1.audio\"\r\nContent-Type:image/jpg\r\n\r\n"
    with open(img_file, 'rb') as f:
        imgbuf = f.read()
        body += imgbuf
        del imgbuf
        body += "\r\n--WebKitFormBoundary8riBH6S4ZsoT69so--\r\n\r\n"
    return content_type, body

if __name__ == '__main__':
    f = './test.db'
    import sys
    host = 'http://120.26.137.224:38700/upload'
    post2_multipart(host, sys.argv[1])

