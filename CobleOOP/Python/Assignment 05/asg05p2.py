from abc import ABC
from abc import abstractmethod
class Subject(ABC):

    @abstractmethod
    def __init__(self):
        pass

    def register(self,observer):
        self.observers.append(observer)

    @abstractmethod
    def notifyAll(self, args, kwargs):
        pass

class Observer(ABC):
    def __init__(self,subject):
        subject.register(self)

    @abstractmethod
    def notify(self,subject,args):
        pass

class ConcreteSubject(Subject):
    def __init__(self):
        self.observers = []
        self.items = {}

    def notifyAll(self, args, kwargs):
        for observer in self.observers:
            observer.notify(self,args,kwargs)

    #* and ** issue
    def append(self, entries, keywords):
        changed = False
        for i in range(len(entries)):
            # Exception here
            self.items[keywords[i]] = entries[i]
            changed = True
        if changed:
            self.notifyAll(entries, keywords)
            changed = False
        

    def delete(self,keysDel):
        deletion = False
        tempDict = {k: v for k, v in self.items.items()}
        for key in keysDel:
            if key in tempDict.keys():
                self.items.pop(key)
                deletion = True
        if deletion:
            self.notifyAllDel(keysDel)
        del tempDict

    def notifyAllDel(self,kwargs):
        for observer in self.observers:
            observer.notifyDel(kwargs, self)


class ConcreteObserver(Observer):
    def _init__(self):
        super.__init__(self)

    def notify(self, subject, args, keys):
        print(type(self).__name__,':: Got', args,'From',subject,'with',keys,'as keys')

    def notifyDel(self, keys, subject):
        print(type(self).__name__,':: Items with', keys, 'as key deleted from',subject)


sub = ConcreteSubject()
obs = ConcreteObserver(sub)

key = ["First","Middle","Last"]
data = ["Hayden","Eli","Coble"]

sub.append(data, key)

sub.delete(["Middle"])
print("ree")

