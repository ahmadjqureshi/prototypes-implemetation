#Main program
from tokenization import TextHelper
from document import Document
from database import DataBase
from documentmatrix import DocumentMatrix
from querymatrix import QueryMatrix
import numpy
from reweight import ReWeightAllDoc
import os

currentDir = os.getcwd()

currentDir = os.path.join(currentDir, 'sgms')

filenames  = os.listdir(currentDir)

for filename in filenames:
	d = Document(os.path.join( currentDir , filename))

dm = DocumentMatrix()
matrix = dm.BuildDocumentMatrix()

dm.CalculateSVD(matrix)

j = 0
while j < 15:
	print 'Enter Document name to calculate similarity>>>'
	filename = raw_input()
	queryObj = QueryMatrix(currentDir+filename)
	queryObj.CalcQueryMatrix(dm._m_Uk, dm._m_Sk)

	print "query Matrix"
	print queryObj._m_queryMatrix

	q = queryObj._m_queryMatrix

	i = 0

	for doc in dm._m_docMatrix:
		i = i + 1
		similarity = queryObj.cosine_distance(q, doc)
		print "{0} = {1}".format( i, similarity)
	j = j + 1
	