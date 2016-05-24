#!/usr/bin/env python
# -*- coding: utf-8 -*-
def makeHTMLTag(tag, *args, **kwargs):
    def real_decorator(fn):
        css_class = 'class = {0}'.format(kwargs['css_class']) \
                if 'css_class' in kwargs else ''
        def wrapped(*args, **kwargs):
            return '<' + tag + css_class + '>' + fn(*args, **kwargs) + '</' + tag + '>'
        return wrapped
    return real_decorator


@makeHTMLTag(tag = 'b', css_class = 'bold_css')
@makeHTMLTag(tag = 'i', css_class = 'italic_css')
def hello():
    return 'hello world'

print hello()
