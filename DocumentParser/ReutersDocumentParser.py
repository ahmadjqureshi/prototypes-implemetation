from HTMLParser import HTMLParser
import os

i = 0

# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
	_currentTag = ''
	_subTag = ''
	_f = None
	_fileno = 1
	__filePrefix = 0
	
	def handle_starttag(self, tag, attrs):
		#print "Encountered a start tag:", tag
		
		if tag == 'd' and self._currentTag == 'topics':
			self._subTag = tag
			return
		
		self._currentTag = str(tag)
		if tag == 'text':
			self._f = None
			self._f = open( '.\\extracted\\doc_'+str(i) + '_'+str(self._fileno)+'.txt', 'w')
			
	def handle_endtag(self, tag):
		#print "Encountered an end tag :", tag
		if self._currentTag == 'topics' and self._subTag == 'd' and tag == 'd':
			return
		
		self._currentTag = ''
		if str(tag) == 'text':
			self._f.close()
			self._fileno = self._fileno + 1
		
	def handle_data(self, data):
		#print "Encountered some data  :", data
		if self._currentTag == 'body':
		#	print "write body to file"
			self._f.write(data)
		if self._currentTag == 'text':
		#	print "write body to file"
			self._f.write(data)
		if self._currentTag == 'title':
		#	print "write title to file"
			self._f.write(data+'\n')
		if self._currentTag == 'topics':
		#	print "write title to file"
			categories.write('{0}, {1}\n'.format('doc_'+str(i) + '_'+str(self._fileno)+'.txt', data))
			#print data
		
currentDir = os.getcwd()
currentDir += '\\sgmorg\\'

filenames  = os.listdir(currentDir)
i=1

categories = open( 'categories.csv', 'w')

for filename in filenames:
	f = open( currentDir+filename, 'r')
	text = ''
	for line in f:
		text += str(line)
	parser = MyHTMLParser()
#	parser.__filePrefix = i
	parser.feed(text)
	parser = None
	i = i + 1

categories.close()
