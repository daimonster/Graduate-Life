from urllib.error import URLError
from urllib.request import ProxyHandler,build_opener

proxy_handler=ProxyHandler({
	'http':'http://127.0.0.1:9743',
	'https':'https://127.0.0.1:9743'})
opener=build_opener(proxy_handler)

try:
	reponse=opener.open('https://www.baidu.com')
	print(reponse.read().decode('utf-8'))
except URLError as e:
	print(e.reason)
