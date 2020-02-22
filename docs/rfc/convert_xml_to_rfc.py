#!/usr/bin/env python3

import requests

files = {'input': open('rfc.xml','rb')}

res = requests.post('https://xml2rfc.tools.ietf.org/cgi-bin/xml2rfc.cgi',
                    files=files)

ftow = open("rfc.txt", "w+")

ftow.write(res.text)
ftow.close()
