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
from svmhelper import *
from math import pow

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

#currentDir = os.getcwd()
#currentDir += '\\sgms\\'

#filenames  = os.listdir(currentDir)

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

predictedLabel = 0

tDataLabels, tData = BuildSVMTrainingData(dm._m_docMatrix)

#gamma = calculateGamma(dm._m_docMatrix)

print '{0} : {1}'.format(len(tDataLabels), len(tData))

problem = svm_problem_helper( tDataLabels, tData)
#cPower = float(1)
#gPower = float( -7 )
cPower = float(-5)
gPower = float( -15 )
cList = []
gList = []
accuracyList = []

while cPower <= 15:
	cVal = pow(2, cPower )
	gVal = pow( 2, gPower )
	#cVal = cPower
	parameterString = '-c ' + str( cVal ) + ' -d 2 -g ' + str( gVal ) + ' -v 5'
	#parameterString = ' -t 0 -c ' + str( cVal ) + ' -v 5'
	
	#parameterString = '-c ' + str( cVal ) + ' -d 2 -g ' + str( gamma ) + ' -v 2'
	
	print parameterString
	parameter = svm_parameter_helper(parameterString)
	accuracy = svm_train_helper( problem, parameter)
	
	cList.append( cVal )
	gList.append( gVal )
	accuracyList.append( accuracy )
	
	cPower = cPower + 0.25
	gPower = gPower + 0.25
#	cPower = cPower + 2
#	gPower = gPower + 2

i = 0
maxIndex = -1
maxAcc = float(-10000)
for acc in accuracyList:
	if acc > maxAcc:
		maxAcc = acc
		maxIndex = i
	i = i + 1

print parameterString
parameterString = '-c ' + str( cList[maxIndex] ) + ' -d 2 -g ' + str( gList[maxIndex] )
#parameterString = ' -t 0 -c ' + str( cList[maxIndex] )

#parameterString = '-c ' + str( cList[maxIndex] ) + ' -g ' + str( gamma )

parameter = svm_parameter_helper( parameterString )

trainResult = svm_train_helper( problem, parameter)
docIndex = 1
results = open('svmresults.csv','w')
for doc in dm._m_docMatrix:
	testDocVector = doc
	testDocDictionary = {}
	testDocDictionaryContainer = []
	#predictLabel = []
	
	i =1
	for word in testDocVector:
		testDocDictionary[i] = float(word)
		i = i + 1
	
	#for label in tDataLabels:
	testDocDictionaryContainer.append( testDocDictionary )
	#predictLabel.append( float(label) )
	
	predictLabel = []
	predictLabel.append( float(tDataLabels[0]) )
	
	p_label, p_acc, p_val = svm_predict_helper( predictLabel, testDocDictionaryContainer, trainResult)
	i = 0
	#for label in p_label:
	results.write(' {0}, {1}\n'.format( docIndex, int(p_label[0])))
	#	i = i + 1
	
	docIndex = docIndex + 1
	#if docIndex == 500:
	#	break
	testDocDictionary.clear()
	del testDocDictionaryContainer[:]
	
results.close()
