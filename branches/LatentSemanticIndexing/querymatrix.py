import numpy
import math
from tokenization import TextHelper
from database import DataBase

class QueryMatrix:
	
	_textPro = None
	_tfWeight = {}
	_m_query = numpy.array([])
	_m_queryMatrix = numpy.array([])
	_documentsToBeQueried = {}
	
	def __init__(self, fileNameAndPath):
		_textPro = TextHelper.Instance()
		__listOfStopWords = _textPro.getStopWords()
		__listOfWords = []
		db = DataBase.Instance()
		
		self._tfWeight = {}
		self._m_query = numpy.array([])
		self._m_queryMatrix = numpy.array([])
		
		f = open( fileNameAndPath, 'r')
		for line in f:
			tokens = _textPro.tokenizeString( line )
			for word in tokens:
				if word != ",":
					__listOfWords.append(word)
		f.close()
		
		lengthOfDoc = len( __listOfWords )
		i = 0 
		while i < lengthOfDoc:
			for word in __listOfStopWords:
				if word == __listOfWords[i]:
					__listOfWords.pop(i)
					lengthOfDoc = len( __listOfWords )
					i = i - 1
					break
			i = i + 1
		
		for word in __listOfWords:
			stemmedWord = _textPro.stemWord(word)
			if self._tfWeight.has_key(stemmedWord):
				self._tfWeight[stemmedWord] = self._tfWeight[stemmedWord] + 1
			else:
				self._tfWeight[stemmedWord] = 1
		
		documentsList = db.GetAllUniqueKeywords()
		
		query = []
		for word in documentsList:
			if self._tfWeight.has_key(word):
				query.append(float(self._tfWeight[word]))
				documentsKeyword = {}
				documentsKeyword = db.GetKeywordDictionary(word)
				for docID in documentsKeyword.keys():
					if self._documentsToBeQueried.has_key(docID):
						continue
					else:
						self._documentsToBeQueried[str(docID)] = 0
						print 'added doc' + str(docID)
				documentsKeyword.clear()
			else:
				query.append(float(0.0))
		
		self._m_query = numpy.array(query)
		
		del documentsList[:]
		del __listOfWords[:]
		del query[:]
		self._tfWeight.clear()
		
		
	def CalcQueryMatrix(self, Uk, Sk):
		
		inter = numpy.dot(self._m_query, Uk)
		
		self._m_queryMatrix = numpy.dot( inter, Sk)
		
	def cosine_distance(self, u, v):
		return numpy.dot(u, v) / (math.sqrt(numpy.dot(u, u)) * math.sqrt(numpy.dot(v, v)))
