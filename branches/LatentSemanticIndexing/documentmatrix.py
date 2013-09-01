
from database import DataBase
import numpy
from scipy import linalg as linalg2
from scipy.sparse import linalg

class DocumentMatrix:

	_db = 0
	_m_Vhk = numpy.array([])
	_m_Uk = numpy.array([])
	_m_Sk = numpy.array([])
	_m_docMatrix = []
	
	def __init__(self):
		self._db = DataBase.Instance()

	#This function builds all documents matrix with following configuration:
	#		Doc1	Doc2	Doc3	Doc4 . . . 
	#Term1	0.14	0.04	0		0
	#Term2	0		0.01	0		0
	#Term3	0		0		0		0
	#Term4	0		0		0		0
	#.
	#.
	#.
	def BuildDocumentMatrix(self):
		docDictionaryList = {}
		wordsList = []
		docMatrix = []
		#documentsList = self._db.GetAllDocumentID()
		
		#wordsList = self._db.GetAllUniqueKeywords()
		docMatrix = self._db.GenerateTermDocMatrix()
		
		#for word in wordsList:
		#	print word + ':'
		#	matrixRow = []
		#	keywordDic = self._db.GetKeywordDictionary(word)
		#	for doc in documentsList:
		#		if keywordDic.has_key(doc):
		#			matrixRow.append( keywordDic[doc])
		#		else:
		#			matrixRow.append(0)
		#	docMatrix.append( matrixRow )
		
		#finalMatrix = numpy.array(docMatrix)
		return docMatrix
	
	def CalculateSVD(self, docMatrix):
		U, s, Vh = linalg.svds( docMatrix, k=200)
		print U
		print s
		print Vh
		
		#Reduce the dimentions of U s Vh to k
		k = 200
		
		# Generate VtK Matrix, keep first k rows of Vh
		#Vhk = []
		#self._m_Vhk = numpy.array([])
		#count = 0
		
		#for row in Vh:
		#	if count == k:
		#		break
		#	VhkRow = []
		#	for index in row:
		#		VhkRow.append(index)
		#	Vhk.append( VhkRow)
		#	count = count + 1
		
		self._m_Vhk = numpy.array(Vh)
		
		#print "self._m_Vhk----------------"
		#print self._m_Vhk
		
		# Generate Uk Matrix, keep first k columns
		
		#Uk = []
		
		#self._m_Uk = numpy.array([])
		#for row in U:
		#	count = 0
		#	UkRow = []
		#	for index in row:
		#		UkRow.append( index )
		#		count = count + 1
		#		if count == k:
		#			break
		#	Uk.append(UkRow)
		
		self._m_Uk = numpy.array( U )
		
		#print "self._m_Uk---------------"
		#print self._m_Uk
		
		# Generate Sk matrix, keep k * k matrix
		count = 0
		ncount = 0
		
		Sk = []
		self._m_Sk = numpy.array([])
		
		print len(s)
		
		while count < k:
			SkRow = []
			ncount = 0
			while ncount < k:
				SkRow.append( float(0) )
				ncount = ncount + 1
			SkRow[count] = s[count]
			Sk.append( SkRow )
			count = count + 1
		
		#we will calculate inverse of Sk because query calculation requires it
		self._m_Sk = linalg2.inv(numpy.array(Sk))
	
		self._m_docMatrix = []
		
		count = 0 
		ncount = 0
		#build vector for each document from _m_Vhk, every column in the matrix _m_Vhk represents a document
		while count < len(self._m_Vhk[0]):
			print '{0}  {1}'.format(count , ncount)
			docVector = []
			ncount = 0
			while ncount < k:
				docVector.append( self._m_Vhk[ncount][count] )
				ncount = ncount + 1
			self._m_docMatrix.append( numpy.array( docVector ) )
			count = count + 1
		#print "self._m_Sk-------------"
		#print self._m_Sk
		
		#print 'docMatrix: {0}, U: {1}, Uk: {2}'.format( len(docMatrix), len(U), len(self._m_Uk))