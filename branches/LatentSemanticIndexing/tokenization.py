#This is helper class for basic functionality like tokenization, stemming, etc.

import nltk
import re

obj1 = 0

class TextHelper:
	
	def __init__(self):
		f = open('stopwords.txt', 'r')
		for line in f:
			tokens = nltk.word_tokenize( line )
			for word in tokens:
				if word != ",":
					self.__listOfStopWords.append(word)
			
			#print self.__listOfStopWords
		f.close()

	@staticmethod
	def Instance():
		return obj1

	def tokenizeString(self, str):
		tokens = nltk.word_tokenize( str )
		
		finalTokens = []
		#| , . * ' \" ( ) & / \\ : ; \t \r \n 
		tokens2  = []
		for word in tokens:
			
			if self.is_number(word):
				finalTokens.append( word)
			else:
				tokens2 = re.split( r'[-*=,./\\\'\'";_:<>|\n\r\t]+', word)
			for word2 in tokens2:
				if word2 != None and len(word2.strip()) > 2:
					finalTokens.append( word2.lower())
		
		#print finalTokens
		
		return finalTokens

	def getStopWords(self):
			
		return self.__listOfStopWords
		
	def stemWord(self, word):
		stemmer = nltk.stem.porter.PorterStemmer()
		stemmedWord = stemmer.stem_word(word)
		
		return stemmedWord
	
	def is_number(self, s):
		try:
			float(s)
		except ValueError:
			try:
				complex(s)
			except ValueError:
				return False
		return True
	
	__listOfStopWords = []
	
	
	
obj1 = TextHelper()