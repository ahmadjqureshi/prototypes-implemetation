import os
import re
from database import DataBase
from string import *

categoryDictionary = {}
categoryDictionaryNumeric = {}
categoryToID = {}
resultsCategoryDictionary = {}

db = DataBase.Instance()
docTable  = []
docTable = db.GetAllDocuments()
docPaths = []
docPaths = docTable[1]
trainingDocsList = []

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

	trainingDocsList.append( document )

f.close()



i = 1
for val in categoryDictionary.keys():
	print "{0} : {1} : {2} : First Document ID: {3}".format( i, val, len( categoryDictionary[val] ), categoryDictionary[val][0])
	
	categoryDictionaryNumeric[i] = []
	categoryDictionaryNumeric[i] = categoryDictionary[val]
	categoryToID[i] = str(val)
	i = i + 1
	
i = 0

f = open( 'svmresults.csv', 'r')

for line in f:
	tokens = []
	tokens = re.split( r'[,]+', line)
	
	document =  int (tokens[0].strip())
	category = int (tokens[1].strip())
	
	found = 0
	for doc in trainingDocsList:
		if docPaths[document -1].find(doc) != -1:
			found = 1
			break
			
	if found == 0:
		continue
	
	if resultsCategoryDictionary.has_key(categoryToID[category]):
		resultsCategoryDictionary[categoryToID[category]].append(docPaths[document -1])
	else:
		resultsCategoryDictionary[categoryToID[category]] = []
		resultsCategoryDictionary[categoryToID[category]].append(docPaths[document -1])
	i = i + 1
f.close()

print 'Total items in resultsCategoryDictionary: ' + str(i) + ' trainingDocsList: ' + str(len(trainingDocsList))

while 1<2:
	print 'Category name'
	categoryName = raw_input()

	relevantDocument = []
	relevantDocument = categoryDictionary[categoryName]
	relevantDocumentsRetrieved = float(0.0)
	relevantDocumentInDataSet = float(len(relevantDocument))
	
	retrievedDocList = []
	retrievedDocList = resultsCategoryDictionary[categoryName]

	for doc in relevantDocument:
		for retDoc in retrievedDocList:
			if doc in retDoc:
				relevantDocumentsRetrieved = relevantDocumentsRetrieved + 1
				break
	
	retrievedDocuments = float(len(retrievedDocList))
	#retrievedDocuments = relevantDocumentsRetrieved
	precision = float(0.0)
	recall = float(0.0)
	
	precision = relevantDocumentsRetrieved/retrievedDocuments
	recall = 	relevantDocumentsRetrieved/relevantDocumentInDataSet
	print 'Precision {0} , Recall {1}'.format( precision, recall)
	print 'relevantDocumentsRetrieved: {0} , relevantDocumentInDataSet: {1} , retrievedDocuments: {2}'.format( relevantDocumentsRetrieved, relevantDocumentInDataSet, retrievedDocuments)
	
