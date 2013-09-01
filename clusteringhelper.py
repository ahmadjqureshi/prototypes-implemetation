from database import DataBase
from Pycluster import *
from math import sqrt
import re


def BuildClusteringTrainingData(documentsMatrix):
	db = DataBase.Instance()
	categoryDictionary = {}
	trainingData = numpy.array([])
	trainingDataTemp = []
	
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
	
	for val in categoryDictionary.keys():
		#count = 0
		for trainingDoc in categoryDictionary[val]:
			trainingDocVector = []
			
			docID = int(db.GetDocID( trainingDoc))
			
			trainingDocVector = documentsMatrix[docID - 1]
			
			trainingDataTemp.append( trainingDocVector)
			
			#count = count + 1
			#if count > 5:
			#	break
	
	trainingData = numpy.array( trainingDataTemp )
	
		
	return trainingData

def kcluster_helper(documentsMatrix):
	clusterid, error, nfound = kcluster(documentsMatrix, nclusters=120, transpose=0, npass=120, method='a', dist='e')
	
	return clusterid
