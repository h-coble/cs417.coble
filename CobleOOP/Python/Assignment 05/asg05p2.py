from abc import ABC
from abc import abstractmethod
class Subject(ABC):

    @abstractmethod
    def __init__(self):
        pass

    def register(self,observer):
        self.observers.append(observer)

    def notifyAll(self,*args,**kwargs):
        for observer in self.observers:
            observer.notify(self,*args,**kwargs)

class Observer(ABC):
    def __init__(self,subject):
        subject.register(self)

    @abstractmethod
    def notify(self,subject,*args):
        pass

class ConcreteSubject(Subject):
    def __init__(self):
        self.observers = []
        self.items = {}

    #* and ** issue
    def append(self,entries*,keys**):
        changed = False
        for i in range(len(entries)):
            # Exception here
            self.items[keys[i]] = entries[i]
            changed = True
        if changed:
            self.notifyAll(entries,keys)
        

    def delete(self,**keys):
        deletion = False
        for key in keys and self.items.keys():
            self.items.pop(key)
            deletion = True
        if deletion:
            self.notifyAllDel(keys)

    def notifyAll(self,**kwargs):
        for observer in self.observers:
            observer.notify(self,**kwargs)


class ConcreteObserver(Observer):
    def _init__(self):
        super.__init__(self)

    def notify(self,subject,*args, **keys):
        print(type(self).__name__,':: Got', args,'From',subject,'with',keys,'as keys')

    def notifyDel(self,subject,**keys):
        print(type(self).__name__,':: Items with', keys, 'as key deleted from',subject)


sub = ConcreteSubject()
obs = ConcreteObserver(sub)
sub.register(obs)

keywords = ["First","Middle","Last"]
data = ["Hayden","Eli","Coble"]

sub.append(data,keywords)
    