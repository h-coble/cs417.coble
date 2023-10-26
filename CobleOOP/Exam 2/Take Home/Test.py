print("unicorn"[::-1])

def land (landlist):
    newlist = []
    for i in landlist:
        newlist.append(str(i) + "land")
    return newlist 

for word in land(["fat", "bat",2]):
    print(word)



def makeDict(animals):
    animalDict = {}
    i=-1
    for animal in animals:
        i+=1
        if animal == "newt":
            atuple = (animal,"Amphibian")
        elif animal == "snake":
            atuple = (animal, "Reptile")
        elif animal == "bat":
            atuple = (animal, "Mammal")
        else:
            atuple = (animal, "???")
        animalDict[i] = atuple
    return animalDict

dictOut = makeDict(["newt", "snake", "bat"])

def getMax(items):
    items.sort()
    return items[-1]

print(getMax([3,1,2]))

def avgEach(players):
    recorded = {}
    sumList = {}
    for player in players:
        if player[0] in recorded.keys():
            recorded[player[0]] += 1
            sumList[player[0]] += player[1]
        else:
            recorded[player[0]] = 1
            sumList[player[0]] = player[1]
    
    for player in recorded.keys():
        print(player + " average: " + str(sumList[player] / recorded[player])) 

avgEach([ ('smith', 92), ('jones',89), ('andrews',90), ('smith', 100) ])