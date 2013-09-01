#Main program
from tokenization import TextHelper
from document import Document
from database import DataBase
from documentmatrix import DocumentMatrix
from querymatrix import QueryMatrix
import numpy
from reweight import ReWeightAllDoc
import os
import re
from clusteringhelper import *
from math import pow

class SimilarityResult:
	_simVal = float(0.0)
	_docID = 0
	def __init__(self, simVal, docID):
		self._simVal = simVal
		self._docID = docID
		
	def __lt__(self, other):
		return self._simVal > other._simVal

currentDir = os.getcwd()
currentDir += '\\sgms\\'

filenames  = os.listdir(currentDir)

#for filename in filenames:
#	print filename
#	d = Document(currentDir+filename)
	#break;

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

predictedLabel = 0

trainData = BuildClusteringTrainingData( dm._m_docMatrix )

tDataLabels = kcluster_helper( trainData )

docIndex = 1
results = open('clusteringresults.csv','w')
for doc in tDataLabels:
	#for label in p_label:
	results.write(' {0}, {1}\n'.format( docIndex, int(doc)))
	
	docIndex = docIndex + 1
	
results.close()
