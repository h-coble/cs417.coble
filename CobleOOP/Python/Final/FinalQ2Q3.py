#Product
class Widget:
    def __init__(self):
        self.wheels = list()
        self.container = None
        self.body = None
        
    def attachWheel(self,wheel):
        self.wheels.append(wheel)
    def setContainerVolume(self,volume):
        self.container = volume
    def setBody(self,bodytype):
        self.body = bodytype

class WidgetA(Widget):
    def __init__(self):
        self.wheels = list()
        self.container = None
        self.body = None

class WidgetB(Widget):
    def __init__(self):
        self.wheels = list()
        self.container = None
        self.body = None

#Creator
class Builder:        
    def __init__(self):
        self.A = Widget()
    def setWheel(self):
        pass
    def setContainer(self):
        pass
    def setBody(self):
        pass   
    
class Wheel:
    size = None      
        
class Container:        
    volume = None

class Body:
    shape = None
    
#Concrete Product Creator
class WidgetBuilderA(Builder):
    def __init__(self):
        self.A = WidgetA()
        self.W = Wheel()
        self.W.size = 20

        self.C = Container()
        self.C.volume = 50

        self.B = Body()
        self.B.shape = "Triangular Pyramid"



    def setWheel(self):
        i = 0
        for i in range(4):
            self.A.attachWheel(self.W)
        

    def setContainer(self):
        self.A.setContainerVolume(self.C)
    
    def setBody(self):
        self.A.setBody(self.B)

class WidgetBuilderB(Builder):
    def __init__(self):
        self.A = WidgetB()
        self.W = Wheel()
        self.W.size = 10

        self.C = Container()
        self.C.volume = 20

        self.B = Body()
        self.B.shape = "Rectangular Prism"



    def setWheel(self):
        i = 0
        for i in range(6):
            self.A.attachWheel(self.W)
        

    def setContainer(self):
        self.A.setContainerVolume(self.C)
    
    def setBody(self):
        self.A.setBody(self.B)