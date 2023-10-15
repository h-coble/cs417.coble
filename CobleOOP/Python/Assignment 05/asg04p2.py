from abc import ABC

class Subject(ABC):
    def __init__(self):
        self.observers = []
    def register(self,observer):
        self.observers.append(observer)

    def notifyAll(self,*args,**kwargs):
        for observer in self.observers:
            observer.notify(self,*args,**kwargs)

class Observer(ABC):
    def __init__(self,subject):
        subject.register(self)

    def notify(self,subject,*args):
        print(type(self).__name__,':: Got', args,'From',subject)

class ConcreteSubject(Subject):
    def __init__(self):
        super.__init__(self)

class ConcreteObserver(Observer):
    def _init__(self):
        super.__init__(self)