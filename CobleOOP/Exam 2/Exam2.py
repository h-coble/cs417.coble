#Problem 1

def linetest(x: tuple, y:tuple,z:tuple ):
    #a bit confusing, but I used the naming convention given in the problem
    #I tried to follow as closely as I could
    #assuming x0 is x of initial tuple (x) and x1 is x coordinate of second tuple (y)
    #[0] = x coordinate, [1] = y coordinate
    #x0 = x[0]
    #x1 = y[0]

    a = y[1] - x[1]
    b = x[0] - y[0]
    c = x[0]*y[1] - y[0]*x[1]

    #negate the value
    return -(a * z[0] + b * z[1] - c)
        #after testing, I found I was gettting the opposite sign than I should,
        #but I don't think I messed up the math.
        #This gives a negative value if below or right and positive for above or left


#Problem 2
import csv

def readCoords(fileName:str):
    outList = []
    with open(fileName,"r") as csvfile:
        fileReader = csv.reader(csvfile, quoting = csv.QUOTE_NONNUMERIC)
        for row in fileReader:
            outList = outList + [tuple(row)]
    csvfile.close()
    return outList


#Problem 3
def convexHull(points:list):
    #Flags for above/below
    above = False
    below = False
    outList = []
    for point in points:
        for current in points[points.index(point)::]:
            for next in points:
                if point != current and point != next:
                    #Set flags
                    if linetest(point,current, next) > 0:
                        above = True
                    elif linetest(point,current, next) < 0:
                        below = True

                    #if both set, no need to continue
                    if above and below:
                        break

            #If neither flags were set, log the coordinates
            if above != below:
                if point not in outList:
                    outList = outList + [point]
                if current not in outList:
                    outList = outList + [current]

            #Reset flags for next set of points
            above = False
            below = False
            
    return outList

#Test Driver Code
#P1
print("Used points on y =-x to set line")
print("(1,1) and (3,3)")
print(str(linetest( (1,1),(3,3),(-1,1))) + " results from (-1,1)" )
print(str(linetest( (1,1),(3,3),(1,-1))) + " results from (1,-1)" )
print(str(linetest( (1,1),(3,3),(0,0))) + " results from (0,0)" )

#P2
#Output to confirm list was stored
#Output to txt file to more easily read data
allPoints = readCoords("e2p2data.csv")
file = open("P2_out.txt", "w")
print("\nPoints:")
file.write("Points:\n")
for point in allPoints:
    print(point)
    file.write(str(point) + "\n")
file.close

#P3
#Same actions here
file = open("P3_out.txt", "w")
print("\nConvex Hull:")
file.write("Convex Hull:\n")

for point in convexHull(allPoints):
    print (point)
    file.write(str(point) + "\n")
    
file.close()