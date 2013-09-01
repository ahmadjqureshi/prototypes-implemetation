#Main program
from tokenization import TextHelper
from document import Document
from database import DataBase
from documentmatrix import DocumentMatrix
from querymatrix import QueryMatrix
import numpy
from reweight import ReWeightAllDoc
import os

class SimilarityResult:
	_simVal = float(0.0)
	_docID = 0
	def __init__(self, simVal, docID):
		self._simVal = simVal
		self._docID = docID
		
	def __lt__(self, other):
		return self._simVal > other._simVal
#doc = Document('Test.txt')
#print doc._tfWeight

#db = DataBase.Instance()
#word1 = 'FirstWord'
#word = []
#word.append(word1)
#data = db.GetKeywordData(word)

#print data[0][1]

#word = []
#word.append(1)
#data = db.GetTotalDocWords( word)

#print data[0][0]

currentDir = os.getcwd()
currentDir += '\\sgms\\'

filenames  = os.listdir(currentDir)

#for filename in filenames:
#	print filename
#	d = Document(currentDir+filename)
	#break;

#d = Document('reut2-000.sgm')
#d1 = Document('reut2-001.sgm')
#d2 = Document('reut2-002.sgm')
#d3 = Document('reut2-003.sgm')
#d4 = Document('reut2-004.sgm')

#docReweight = ReWeightAllDoc()



dm = DocumentMatrix()
matrix = dm.BuildDocumentMatrix()

print matrix
dm.CalculateSVD(matrix)

print "self._m_Vhk----------------"
print dm._m_Vhk

print "self._m_Uk---------------"
print dm._m_Uk

print "self._m_Sk-------------"
print dm._m_Sk
j = 0

currentDir = os.getcwd()
currentDir += '\\queries\\'

filenames  = os.listdir(currentDir)

queriesRCurrentDir = os.getcwd()
queriesRCurrentDir += '\\queriesresult\\'

db = DataBase.Instance()
docTable  = []
docTable = db.GetAllDocuments()
docPaths = []
docPaths = docTable[1]

for filename in filenames:
	#print 'Enter Document name to calculate similarity>>>'
	#filename = raw_input()
	docSim = []
	results = open(queriesRCurrentDir+filename + '.csv','w')
	queryObj = QueryMatrix(currentDir+filename)
	queryObj.CalcQueryMatrix(dm._m_Uk, dm._m_Sk)
	#print "query Matrix"
	#print queryObj._m_queryMatrix

	q = queryObj._m_queryMatrix

	i = 0
	maxSimilarity = float(0.0)
	maxIndex = 0
	
	print queryObj._documentsToBeQueried
	
	for doc in dm._m_docMatrix:
		i = i + 1
		
		if queryObj._documentsToBeQueried.has_key(str(i)):
			similarity = queryObj.cosine_distance(q, doc)
			print "{0} = {1}".format( i, similarity)
			simResult = SimilarityResult( similarity, i)
			docSim.append( simResult )
	
	#sorted( docSim, key=float SimilarityResult: SimilarityResult._simVal, reverse=True)
	docSim.sort()
	highestSimilarity = docSim[0]._simVal
	highestSimilarity = highestSimilarity - 0.5
	#print '================================'
	
	for val in docSim:
		if val._simVal > highestSimilarity and val._simVal > 0:
			print "{0} , {1}, {2}".format( val._simVal, val._docID, docPaths[val._docID - 1])
			results.write("{0} , {1} , {2}\n".format( val._simVal, val._docID, docPaths[val._docID - 1]))
	
	results.close()

