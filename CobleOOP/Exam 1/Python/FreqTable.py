class FreqTable():

    def countFrequency(self, listToCount):
        wordDict = {}

        for word in listToCount:
            if word not in wordDict:
                wordDict[word]=1
            else:
                wordDict[word] +=1
        return wordDict
    
    def __init__(self, wordArray):
        self.listToCount = wordArray
        self.freqTable = self.countFrequency(self.listToCount)
    
    def printFreqTable(self):
        print("Frequency Report:")
        for word, count in  self.freqTable.items():
            print(f"{word:} {count}")
    
def main():
    testArray = ["these","test","words","are","words","that","test","words"]
    table = FreqTable(testArray)
    table.printFreqTable()
    print()
    testArray = [1,2,3,4,2]
    table = FreqTable(testArray)
    table.printFreqTable()

    return


main()
