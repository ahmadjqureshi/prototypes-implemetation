from database import DataBase
from svmutil import *
from math import sqrt
import re


def BuildSVMTrainingData(documentsMatrix):
	db = DataBase.Instance()
	categoryDictionary = {}
	trainingData = []
	trainingDataLabels = []

	f = open( 'categories.csv', 'r')

	for line in f:
		tokens = []
		tokens = re.split( r'[,]+', line)
		
		document =  tokens[0].strip()
		category = tokens[1].strip()
		
		if categoryDictionary.has_key(category):
			categoryDictionary[category].append(document)
		else:
			categoryDictionary[category] = []
			categoryDictionary[category].append(document)
		
	f.close()
	labelID = 1
	labelDictionary = {}
	for val in categoryDictionary.keys():
		labelDictionary[val] = labelID
		labelID = labelID + 1
	
	for val in categoryDictionary.keys():
		count = 0
		for trainingDoc in categoryDictionary[val]:
		#trainingDoc = categoryDictionary[val]
			i = 1
			trainingDocDictionary = {}
			
			docID = int(db.GetDocID( trainingDoc))
			
			trainingDocVector = documentsMatrix[docID - 1]
			
			for word in trainingDocVector:
				trainingDocDictionary[i] = float(word)
				i = i + 1
			
			trainingData.append( trainingDocDictionary)
			trainingDataLabels.append( float(labelDictionary[val]) )
			count = count + 1
			if count > 100:
				break
		
		
	return (trainingDataLabels, trainingData)

def calculateGamma(documentsMatrix):
	labels, docVectors = FeatureVectorsForParamCalc(documentsMatrix)
	
	allDistances = []
	sumAllDistances = float(0.0)
	totalVectors = float(0.0)
	
	i = 0
	j = 0
	while i < len( docVectors):
		while j < len( docVectors):
			distance = CalcDistance( docVectors[i], docVectors[j])
			sumAllDistances = sumAllDistances + distance
			allDistances.append( distance )
			totalVectors = totalVectors + 1
			j = j + 1
		i = i + 1
	
	gamma = float(0.0)
	gamma = sumAllDistances / totalVectors
	
	return gamma

def FeatureVectorsForParamCalc(documentsMatrix):
	db = DataBase.Instance()
	categoryDictionary = {}
	trainingData = []
	trainingDataLabels = []

	f = open( 'categories.csv', 'r')

	for line in f:
		tokens = []
		tokens = re.split( r'[,]+', line)
		
		document =  tokens[0].strip()
		category = tokens[1].strip()
		
		if categoryDictionary.has_key(category):
			categoryDictionary[category].append(document)
		else:
			categoryDictionary[category] = []
			categoryDictionary[category].append(document)
		
	f.close()
	labelID = 1
	labelDictionary = {}
	for val in categoryDictionary.keys():
		labelDictionary[val] = labelID
		labelID = labelID + 1
	
	for val in categoryDictionary.keys():
		count = 0
		for trainingDoc in categoryDictionary[val]:
		#trainingDoc = categoryDictionary[val]
			i = 1
			trainingDocDictionary = {}
			
			docID = int(db.GetDocID( trainingDoc))
			
			trainingDocVector = []
			trainingDocVector = documentsMatrix[docID - 1]
			
			#for word in trainingDocVector:
			#	trainingDocDictionary[i] = float(word)
			#	i = i + 1
			
			trainingData.append( trainingDocVector)
			trainingDataLabels.append( float(labelDictionary[val]) )
			count = count + 1
			break
		
	return (trainingDataLabels, trainingData)

def CalcDistance(x1, x2):
	if len(x1) != len(x2):
		return -1
	i =0
	xLength = len( x1 )
	
	p1 = 0
	p2 = 0
	p3 = 0
	interimVal = 0
	distanceMeasure = 0
	
	while i < xLength:
		p1 = p1 + ( KFunction( x1[i], x1[i]) / ( xLength * xLength ) )
		
		p2 = p2 + ( KFunction( x2[i], x2[i]) / ( xLength * xLength ) )
		
		p3 = p3 + ( KFunction( x1[i], x2[i]) / ( xLength * xLength ) )
		
		i = i + 1
	
	interimVal = p1 + p2 - ( 2 * p3 )
	
	distanceMeasure = sqrt( interimVal )
	
	return distanceMeasure
	
	
def KFunction(x1, x2):
	result = x1 * x2
	return result

def svm_problem_helper( labels, trainingData):
	prob = svm_problem( labels, trainingData)
	return prob
	
def svm_parameter_helper( parameters ):
	param = svm_parameter( parameters )
	return param
	
def svm_train_helper( prob, param ):
	m = svm_train( prob, param)
	return m
	
def svm_predict_helper( labels, documentToBePredicted, trainingResultSet ):
	#x0, max_idx = gen_svm_nodearray(documentToBePredicted)
	#returnedLabel = libsvm.svm_predict( trainingResultSet, x0)
	p_label, p_acc, p_val = svm_predict(labels, documentToBePredicted, trainingResultSet, "")
	return p_label, p_acc, p_val
	