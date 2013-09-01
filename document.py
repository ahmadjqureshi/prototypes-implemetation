#This class represents a document and it calculates weight of each word, it also expands the terms

from tokenization import TextHelper
from database import DataBase
from math import log
from nltk.corpus import wordnet
import re

#The object of this class is stored in document's dictionary
class WordProperties:
	_m_docID = 0
	_m_word = ""
	_m_weight = float(0.0)
	_m_termFrequency = int(0)
	
	def __init__(self, docID, word, weight, termFrequency):
		self._m_docID 	= docID
		self._m_word 	= word
		self._m_weight 	= weight
		self._m_termFrequency = termFrequency
	

class Document:
	
	_textPro = None		#text processor e.g. tokenization and stop words
	_tfWeight = {}		# term frequency
	_globalWeight = {}	# global weight
	_entropyWeight = {} # final entropy based weight

	def __init__(self, fileNameAndPath, existingDocID=0):
		print "Start-------------"
		self._textPro = TextHelper.Instance()
		listOfStopWords = self._textPro.getStopWords()
		listOfWords = []
		print "Get stopwords-------------"
		f = open( fileNameAndPath, 'r')
		
		reweight = 0
		
		#tokenize file line by line
		#for line in f:
		#	tokens = self._textPro.tokenizeString( line )
		#	for word in tokens:
		#		listOfWords.append(word)
				
		i = 0
		oneIteration = 100
		
		lines = f.readlines()
		
		while i <len(lines):
			j = i
			multipleLines = ''
			if (i + oneIteration) >= len(lines):
				oneInteration = len(lines) - i - 1
			
			while j < (i + oneIteration) and j < len(lines):
				multipleLines += ' ' + lines[j]
				j = j + 1
				
			tokens = self._textPro.tokenizeString( multipleLines )
			for word in tokens:
				listOfWords.append(word)
			
			i = i + oneIteration
			
		f.close()
		
		#remove stop words
		lengthOfDoc = len( listOfWords )
		i = 0 
		while i < lengthOfDoc:
			for word in listOfStopWords:
				if word == listOfWords[i]:
					listOfWords.pop(i)
					lengthOfDoc = len( listOfWords )
					i = i - 1
					break
			i = i + 1
		
		#stem words and calculate term frequency
		for word in listOfWords:
			stemmedWord = self._textPro.stemWord(word)
			if self._tfWeight.has_key(stemmedWord):
				self._tfWeight[stemmedWord] = self._tfWeight[stemmedWord] + 1
			else:
				self._tfWeight[stemmedWord] = 1
		
		totalNumberOfWord = float(len(listOfWords))
		
		print "Tokenization complete-------------"
		
		#calculate global weight
		newDocID = int(existingDocID)
		db = DataBase.Instance()
		
		if newDocID == 0:
			newDocID = db.InsertDoc( fileNameAndPath, totalNumberOfWord)
		else:
			db.DeleteDocKeywords(newDocID)
			reweight = 1
		
		k1 = 1.2
		b = 0.75
		#print "New Doc ID"
		#print newDocID
		for key in self._tfWeight.keys():
			IDF = float(0.0)
			# total number of words
			N = len( db._totalDocWords)
			
			nq = db.NumberOfDocumentsContainingKeyword(key)
			
			globalVal = (N - nq + 0.5) / ( nq + 0.5 )
			IDF = log( globalVal)
			
			avgLen = ( db._totalNumberOfWords ) / float(N)
			
			localValDen =  float(self._tfWeight[key]) * ( k1 + 1 )
			localValNum = float(self._tfWeight[key]) + ( k1 * ( 1 - b + ( b * ( N / avgLen) )  ) )
			localVal = localValDen / localValNum
			
			totalWeight = IDF * localVal
			
			self._entropyWeight[key]  = WordProperties(newDocID, key, totalWeight, self._tfWeight[key])
			
			#print "new keyword ID"
			#print self._entropyWeight[key]
		print "Weighting complete-------------"
		#expand all terms/words
		self.ExpandTerms( totalNumberOfWord)
		print "Term Expansion complete-------------"
		#Add orignal and expanded words in database
		for word in self._entropyWeight.keys():
			newKeywordID = db.InsertKeyword( self._entropyWeight[word]._m_docID, self._entropyWeight[word]._m_word, self._entropyWeight[word]._m_weight, self._entropyWeight[word]._m_termFrequency, reweight)
			#print newKeywordID
		print "Insert into Db complete-------------"
		self._tfWeight.clear()
		self._globalWeight.clear()
		self._entropyWeight.clear()
	
	#This function expands all terms in the document
	def ExpandTerms(self, totalNumberOfWord):
		tempTerms = {}
		for word in self._entropyWeight.keys():
			currentWord = wordnet.synsets(word)
			for synset in currentWord:
				currentSynsets = synset.hyponyms()
				for currentSynset in currentSynsets:
					similarity = synset.wup_similarity( currentSynset)
					if similarity > 0.8:
						tokens = re.split( r'[.]+', currentSynset.name)
						#print '{0},  {1} = {2} : {3}'.format(currentSynset.name, synset.name, similarity, tokens[0])
						if tokens[0].find("_") == -1 and tokens[0].find("-") == -1:
							if self._entropyWeight.has_key(tokens[0]):
								#existing term
								self._entropyWeight[tokens[0]]._m_weight = self._entropyWeight[tokens[0]]._m_weight + ( self._entropyWeight[tokens[0]]._m_weight / totalNumberOfWord)
							else:
								#new term
								newWeight = ( self._entropyWeight[word]._m_weight * similarity ) / totalNumberOfWord
								newKeywordID = WordProperties( self._entropyWeight[word]._m_docID, tokens[0], newWeight, 0)
								tempTerms[tokens[0]] = newKeywordID
						
				currentSynsets = synset.hypernyms()
				for currentSynset in currentSynsets:
					similarity = synset.wup_similarity( currentSynset)
					if similarity > 0.8:
						tokens = re.split( r'[.]+', currentSynset.name)
						#print '{0},  {1} = {2} : {3}'.format(currentSynset.name, synset.name, similarity, tokens[0])
						if tokens[0].find("_") == -1 and tokens[0].find("-") == -1:
							if self._entropyWeight.has_key(tokens[0]):
								#existing term
								self._entropyWeight[tokens[0]]._m_weight = self._entropyWeight[tokens[0]]._m_weight + ( self._entropyWeight[tokens[0]]._m_weight / totalNumberOfWord)
							else:
								#new term
								newWeight = ( self._entropyWeight[word]._m_weight * similarity ) / totalNumberOfWord
								newKeywordID = WordProperties( self._entropyWeight[word]._m_docID, tokens[0], newWeight, 0)
								tempTerms[tokens[0]] = newKeywordID
				break
		
		#add expanded terms weights in document dictionary
		for word in tempTerms:
			if not self._entropyWeight.has_key(word):
				self._entropyWeight[word] = tempTerms[word]
		