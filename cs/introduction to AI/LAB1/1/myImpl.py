import util

"""
Data sturctures we will use are stack, queue and priority queue.

Stack: first in last out
Queue: first in first out
    collection.push(element): insert element
    element = collection.pop() get and remove element from collection

Priority queue:
    pq.update('eat', 2)
    pq.update('study', 1)
    pq.update('sleep', 3)
pq.pop() will return 'study' because it has highest priority 1.

"""

"""
problem is a object has 3 methods related to search state:

problem.getStartState()
Returns the start state for the search problem.

problem.isGoalState(state)
Returns True if and only if the state is a valid goal state.

problem.getChildren(state)
For a given state, this should return a list of tuples, (next_state,
step_cost), where 'next_state' is a child to the current state, 
and 'step_cost' is the incremental cost of expanding to that child.

"""
def myDepthFirstSearch(problem):
    visited = {}
    frontier = util.Stack()

    frontier.push((problem.getStartState(), None))

    while not frontier.isEmpty():
        state, prev_state = frontier.pop()

        if problem.isGoalState(state):
            solution = [state]
            while prev_state != None:
                solution.append(prev_state)
                prev_state = visited[prev_state]
            return solution[::-1]                
        
        if state not in visited:
            visited[state] = prev_state

            for next_state, step_cost in problem.getChildren(state):
                frontier.push((next_state, state))

    return []

def myBreadthFirstSearch(problem):
    visited = {}
    frontier = util.Queue()

    frontier.push((problem.getStartState(), None))
    
    while not frontier.isEmpty():
        state, prev_state = frontier.pop()

        if problem.isGoalState(state):
            solution = [state]
            while prev_state != None:
                solution.append(prev_state)
                prev_state = visited[prev_state]
            return solution[::-1]                
        
        if state not in visited:
            visited[state] = prev_state

            for next_state, step_cost in problem.getChildren(state):
                frontier.push((next_state, state))
    
    return []

def myAStarSearch(problem, heuristic):
    visited={}
    pri={}
    frontier=util.PriorityQueue()
    g1=0
    pri[problem.getStartState()]=g1+heuristic(problem.getStartState())
    frontier.update((problem.getStartState(), None),g1+heuristic(problem.getStartState()))
    while not frontier.isEmpty():
        
        state, prev_state = frontier.pop()
        if problem.isGoalState(state):
            solution=[state]
            while prev_state!=None:
                solution.append(prev_state)
                prev_state = visited[prev_state]
            return solution[::-1]
        
        if state not in visited:
            visited[state] = prev_state
            
            for next_state, step_cost in problem.getChildren(state):
                pri[next_state]=heuristic(next_state)+pri[state]-heuristic(state)+step_cost
                frontier.update((next_state, state),pri[next_state])
    return []

"""
Game state has 4 methods we can use.

state.isTerminated()
Return True if the state is terminated. We should not continue to search if the state is terminated.

state.isMe()
Return True if it's time for the desired agent to take action. We should check this function to determine whether an agent should maximum or minimum the score.

state.getChildren()
Returns a list of legal state after an agent takes an action.

state.evaluateScore()
Return the score of the state. We should maximum the score for the desired agent.

"""
class MyMinimaxAgent():

    def __init__(self, depth):
        self.depth = depth

    def minimax(self, state, depth):
        if state.isTerminated():
            return None, state.evaluateScore()        

        best_state, best_score = None, -float('inf') if state.isMe() else float('inf')
        for child in state.getChildren():
            if state.isMe() and not child.isMe():
                    _,n_score=self.minimax(child,depth)
                    if n_score>=best_score:
                        best_state=child
                        best_score=n_score
            if not state.isMe() and not child.isMe():
                _,n_score=self.minimax(child,depth)
                if n_score<best_score:
                    best_state=child
                    best_score=n_score
            if not state.isMe() and child.isMe():
                if depth==1:
                    n_score=child.evaluateScore()
                    if n_score<best_score:
                        best_state=child
                        best_score=n_score 
                else:
                    _,n_score=self.minimax(child,depth-1)
                    if n_score<best_score:
                        best_state=child
                        best_score=n_score
                    
            
        
        return best_state, best_score

    def getNextState(self, state):
        best_state, _ = self.minimax(state, self.depth)
        return best_state

class MyAlphaBetaAgent():

    def __init__(self, depth):
        self.depth = depth

    
    def getNextState(self, state):
        
        def alphabetacut(state,alpha,beta,depth):
            if state.isTerminated():
                return None, state.evaluateScore(),alpha,beta
            best_state, best_score = None, -float('inf') if state.isMe() else float('inf')
            alpha1=alpha
            beta1=beta
            for child in state.getChildren():
                
                if state.isMe() and not child.isMe():
                    _,n_score,alpha1,beta1=alphabetacut(child,alpha1,beta,depth)
                    if n_score>=best_score:
                        best_state=child
                        best_score=n_score
                    if best_score>beta:
                        return best_state, best_score, alpha1, beta1
                    alpha1=max(alpha1,best_score)
            
                
                if not state.isMe() and not child.isMe():
                    _,n_score,alpha1,beta1=alphabetacut(child,alpha,beta1,depth)
                    if n_score<best_score:
                        best_state=child
                        best_score=n_score
                    if best_score<alpha1:
                        return best_state, best_score, alpha1, beta1
                    beta1=min(beta1,best_score)
                if not state.isMe() and child.isMe():
                    if depth==1:
                        n_score=child.evaluateScore()
                        if n_score<best_score:
                            best_state=child
                            best_score=n_score 
                        if best_score<alpha1:
                            return best_state, best_score, alpha1, beta1
                        beta1=min(beta1,best_score)
                    else:
                        _,n_score,alpha1,beta1=alphabetacut(child,alpha,beta1,depth-1)
                        if n_score<best_score:
                            best_state=child
                            best_score=n_score
                        if best_score<alpha1:
                            return best_state, best_score, alpha1, beta1
                        beta1=min(beta1,best_score)
                    
           
            return best_state, best_score, alpha1, beta
            
        alpha=-float('inf')
        beta=float('inf')
        best_state, a, b, c= alphabetacut(state,alpha,beta,self.depth)
        return best_state
