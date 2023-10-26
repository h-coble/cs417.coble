import abc

#implement ABC Worker class
class Doer(abc.ABC):
    @abc.abstractmethod
    def work():
        pass

#Add Robot Doer subclass
class Robot(Doer):
    def work():
        print("Steals Job")

#Change Worker to subclass of Doer
class Worker(Doer):
    def work():
        print("works")
     # ... does some work
    def eat():
        print("eats")
     # ... takes a lunch break

#No change
class DedicatedWorker(Worker):
    def work():
        print("Works More") 
     # ... works much more
    def eat():
        print("Eats At Desk")
     # ... but eats lunch at their desk

class Manager:
    def setWorker(w):
        worker = w
    def manage():
        worker.work()

