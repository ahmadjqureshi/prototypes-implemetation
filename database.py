#import sqlite3
import mysql.connector
from tokenization import TextHelper
from scipy.sparse import *

connection = 0

class DataBase:

	__conn = None
	_totalDocWords = []
	__docCount = {}
	__keywords = {}
	__words = []
	_totalNumberOfWords = float(0.0)
	
	def __init__(self):
		#self.__conn = sqlite3.connect('Text.db')
		self.__conn = mysql.connector.connect(user='padmin', password='padmin', host='localhost', database='lsiimp')
		
	@staticmethod
	def Instance():
		return connection
		
	def NumberOfDocumentsContainingKeyword(self, keyword):
	
		if self.__keywords.has_key(keyword):
			return self.__keywords[keyword]
		else:
			return 0
		
	def GetTotalDocWords(self, docID):
		
		rows = [[]]
		
		if self.__docCount.has_key(docID[0]):
			rows = [[ self.__docCount[docID[0]] ]]
		else:
			c = self.__conn.cursor()
			c.execute( 'select sum(noofoccurence) from Keywords where DocID = %s', docID)
			rows = c.fetchall()
			c.close()
		
			self.__docCount[docID[0]] = rows[0][0]
		
		return rows
	
	def InsertDoc(self, docPath, totalNoOfWords):
		c = self.__conn.cursor()
		docID = 0
		c.execute('select count(*)  from Documents')
		rows = c.fetchall()
		
		docID =  int(rows[0][0])
		
		docID = docID + 1
			
		del rows[:]
		
		#try:
		c.execute("insert into Documents(DocID,DocPath) values (%s,%s);", (docID, docPath))
		self.__conn.commit()
		#except:
		#	c.close()
			#return -1
		
		
		self._totalDocWords.append( totalNoOfWords)
		
		self._totalNumberOfWords = self._totalNumberOfWords + float(totalNoOfWords)
		
		c.close()
		return docID
		
	def InsertKeyword(self, docID, keyword, weight, noOfOccurence, reweight):
		c = self.__conn.cursor()
		keywordID = 0
		
		c.execute('select max(KeyWordID) from Keywords')
		rows = c.fetchall()
		#print rows
		if rows[0][0] != None:
			keywordID = int(rows[0][0])
		
		keywordID = keywordID + 1
		
		del rows[:]
		#print record
		
		try:
			c.execute("insert into Keywords( KeywordID, DocID, Keyword, Weight, NoOfOccurence) values (%s,%s,%s,%s,%s);", (keywordID, docID, keyword, weight, noOfOccurence))
			self.__conn.commit()
		except:
			c.close()
			#return -1
		
		c.close()
		
		if reweight == 0:
			if self.__keywords.has_key(keyword):
				self.__keywords[keyword] = self.__keywords[keyword] + 1
			else:
				self.__keywords[keyword] = 1
			
		return keywordID
	
	def GetAllUniqueKeywords(self):
		words = []
		c = self.__conn.cursor()
		c.execute('select distinct keyword from Keywords order by keyword asc')
		rows = c.fetchall()
		
		for row in rows:
			word = str(row[0])
			words.append(word)
		
		c.close()
		
		del rows[:]
		
		return words
		
	def GetAllDocumentID(self):
		DocumentIDs = []
		c = self.__conn.cursor()
		c.execute('select distinct DocID from Documents order by DocID asc')
		rows = c.fetchall()
		
		for row in rows:
			word = str(row[0])
			DocumentIDs.append(word)
		
		c.close()
		del rows[:]
		return DocumentIDs
	
	def GetAllDocuments(self):
		DocumentIDs = []
		DocumentPaths = []
		returnResult = []
		
		c = self.__conn.cursor()
		c.execute('select DocID,DocPath from Documents order by DocID asc')
		rows = c.fetchall()
		
		for row in rows:
			word = str(row[0])
			path = str(row[1])
			DocumentIDs.append(word)
			DocumentPaths.append(path)
		c.close()
		
		returnResult.append( DocumentIDs )
		returnResult.append( DocumentPaths )
		del rows[:]
		return returnResult
	
	def GetDocumentDictionary(self, docID):
		documentDict = {}
		c = self.__conn.cursor()
		c.execute('select Keyword, Weight from Keywords where DocID = %s order by Keyword asc', ( docID,))
		rows = c.fetchall()
		
		for row in rows:
			word = str(row[0])
			weight = float(row[1])
			documentDict[word] = weight
		
		c.close()
		
		return documentDict
	
	def GetKeywordDictionary(self, keyword):
		documentDict = {}
		c = self.__conn.cursor()
		c.execute('select DocID, Weight from Keywords where keyword = %s ', ( keyword,))
		rows = c.fetchall()
		
		for row in rows:
			docid = str(row[0])
			weight = float(row[1])
			documentDict[docid] = weight
		
		c.close()
		
		return documentDict
	
	def GenerateTermDocMatrix(self):
		docIds = self.GetAllDocumentID()
		initialMatrixRow = []
		i =0 
		docLen = len(docIds)
		while i <docLen:
			initialMatrixRow.append(float(0.0))
			i = i + 1
		
		self.__words = self.GetAllUniqueKeywords()
		
		startDocID = 1
		maxDocID = int (docIds[len(docIds) -1])
		oneIteration = 300
		
		mData = []
		mRows = []
		mColumn = []
		
		prefixes = []
		
		textObj = TextHelper.Instance()
		
		for word in self.__words:
			tempPrefix = word[0]
			
			if tempPrefix in prefixes:
				continue
			else:
				prefixes.append( tempPrefix)
		
		wIndex = 0
		previousKeyword = ''
		for prefix in prefixes:
			c = self.__conn.cursor()
			prefixWildCard = prefix + '%'
			print prefixWildCard
			c.execute('select  DocID, Weight, Keyword from Keywords where keyword like %s order by keyword asc', (prefixWildCard,))
			rows = c.fetchall()
			previousKeyword = ''
		
			for row in rows:
				if previousKeyword != str(row[2]):
					wIndex = self.GetWordIndex(str(row[2]))
				
				if wIndex == -1:
					break
				
				mRows.append(wIndex)
				docIndex = int(row[0]) - 1
				mColumn.append( docIndex )
				mData.append(float(row[1]))
				
				previousKeyword = str(row[2])
			c.close()
			
			del rows[:]
		
		noOfRows = len( self.__words )
		noOfColumns = len( docIds )
		
		print ' {0} {1} {2} {3} {4}'.format( len(mData), len(mRows), len(mColumn), noOfRows, noOfColumns)
		
		wholeMatrix = csc_matrix( (mData,(mRows, mColumn)), shape=(noOfRows, noOfColumns), dtype=float)
		
		del self.__words[:]
		
		return wholeMatrix
	
	def GetWordIndex(self, keyword):
		i = 0
		for word in self.__words:
			if word == keyword:
				return i
			i = i + 1
		return -1
	
	def DeleteDocKeywords(self, docID):
		c = self.__conn.cursor()
		c.execute('delete from Keywords where DocID = %s ', ( docID,))
		self.__conn.commit()
		c.close()

	def GetDocID(self, docName):
		c = self.__conn.cursor()
		prefixWildCard = '%' + docName + '%'
		c.execute('select  DocID from Documents where DocPath like %s ', (prefixWildCard,))
		rows = c.fetchall()
		DocID = 0
		for row in rows:
			DocID = int(row[0])
			break
		
		c.close()
		
		return DocID

connection = DataBase()