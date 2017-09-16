import requests
import re
import sqlite3
import time
import os

def get_one_page(url):
    response = requests.get(url)
    if response.status_code == 200:
        return response.text
    return None

def make_list(html):
	base_url='http://www.xs.la'
	pattern=re.compile('<dd>.*?href="(.*?)">(.*?)</a></dd>',re.S)
	items=re.findall(pattern,html)
	conn=sqlite3.connect('/home/dai/Graduate-Life/Backup/countnum.db')
	cur=conn.cursor()
	cur.execute('create table if not exists 异常生物见闻录 (name varchar(30),address varchar(50) primary key)')
#需要改成小说名字
	for item in items:
		#print(item)
		url=base_url+item[0]
		cur.execute('select * from 异常生物见闻录 where address=?',(url,))#需要改成小说名字
		values=cur.fetchall()
		if values==[]:
			cur.execute('insert into 异常生物见闻录 (name,address) values (?,?)',(item[1],url))#需要改成小说名字
		else:
			pass
	cur.execute('select * from 异常生物见闻录')#需要改成小说名字
	values=cur.fetchall()
	cur.close()
	conn.commit()
	conn.close()
	return values

def parse_one_page(bookpath,sourcecode):
	print(bookpath)
	sourcecode=re.sub('<br/>.*?<br/>|<script.*?></script>','',sourcecode)
	pattern=re.compile('<div.*?id="content">(.*?)</div>',re.S)
	items=re.findall(pattern,sourcecode)
	content=items[0].replace('&nbsp;&nbsp;&nbsp;&nbsp;','\n\t')
#    items=re.sub('<br/>.*?<br/>','',items)	
	with open('{}.txt'.format(bookpath), 'w') as f:
		f.write(content)
			
def main():
	novelname=input('Which content do you want to download novel?')
	if not novelname==None:
		novelname='/home/dai/文档/'+novelname
		if not os.path.exists(novelname):
			os.system('mkdir {}'.format(novelname))
	first_url='http://www.xs.la/3_3271/'#小说的首页，从首页就可以抓取目录
	sourcecode=get_one_page(first_url)
	values=make_list(sourcecode)
#	print(novelname)
	count=0
	for item in values:
		count+=1
#		print(item[0],item[1])
		bookpath=novelname+'/'+str(count)+' '+item[0]
		if not os.path.exists(bookpath):
			sourcecode=get_one_page(item[1])
			parse_one_page(bookpath,sourcecode)
			time.sleep(0.1)
		else:
			pass

main()

