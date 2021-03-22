
NAME = "Tiffany-Ellen Vo"
COLLABORATORS = ""

# Let me define the function I use for testing.  Don't change this cell. 

def check_equal(x, y, msg=None):
    if x == y:
        if msg is None:
            print("Success")
        else:
            print(msg, ": Success")
    else:
        if msg is None:
            print("Error:")
        else:
            print("Error in", msg, ":")
        print("    Your answer was:", x)
        print("    Correct answer: ", y)
    assert x == y, "%r and %r are different" % (x, y)

"""## Problem 1: common word pairs

The goal is to find the set of consecutive word pairs in common between two sentences. 
We will get there in steps, guiding you to the solution. 
"""

def word_pairs(sentence):
    splitWords = (sentence.split()) #split sentence, put into separate list
    result = []
    if len(splitWords) < 1: #if less than 2 words 
            return result
    for x in range(len(splitWords) -1):
            #result[x] = splitWords[x:(x+1)] 
            y,z = splitWords[x], splitWords[x+1]
            result.append((y,z))
    return result

# Base cases.  5 points.

check_equal(word_pairs(" "), [])
check_equal(word_pairs("woohoo"), [])
check_equal(word_pairs("I am"), [("I", "am")])

# Longer sentences.  5 points. 

check_equal(word_pairs("I love bananas"), [("I", "love"), ("love", "bananas")])
check_equal(word_pairs("a b c d e"), [("a", "b"), ("b", "c"), ("c", "d"), ("d", "e")])

"""Good.  Now, the idea is to use the `word_pair` function to compute the _set_ of consecutive word pairs common to two sentences.  The idea is to compute the word pairs of each list, turn the list into a set, and take the instersection."""

def common_word_pairs(sentence1, sentence2):
    """Returns the set of common consecutive word pairs in two sentences."""
    commonWords = set()
    s1 = word_pairs(sentence1)
    s2 = word_pairs(sentence2)
    for x in s1:
        for y in s2:
            if x == y:
                commonWords.add(x)
    return commonWords

s1 = "I love bananas"
s2 = "I love to eat bananas"
s3 = "Nobody truly dislikes to eat bananas"
s4 = "I love to eat anything but bananas"
s5 = "I like mangos more than bananas"

check_equal(common_word_pairs(s1, s2), {("I", "love")})
check_equal(common_word_pairs(s2, s3), {("to", "eat"), ("eat", "bananas")})
check_equal(common_word_pairs(s3, s4), {("to", "eat")})
check_equal(common_word_pairs(s1, s5), set())

"""## Problem 2: Composing dictionaries

A dictionary $f$ with a set of keys $K$ can be thought of a mapping from keys to values, that is, as a one-to-many partial function $f: K \mapsto V$ from $K$ to a set $V$ of values.  The [_domain_](https://en.wikipedia.org/wiki/Domain_of_a_function) ${\rm Dom}(f) = K$ of $f$ is the set of keys of the dictionary $f$. 

Given two functions $f$ and $g$, their [composition](https://en.wikipedia.org/wiki/Function_composition) $g \circ f$ is obtained by applying first $f$, then $g$:

$$
  (g \circ f) (x) = g(f(x)) \; .
$$

Note that an element $x$ that is in the domain (set of keys) of $f$ is also in the domain of $g \circ f$ only if $f(x)$ is in the domain of $g$ (otherwise, we cannot apply $g$ to $f(x)$. 
We can write this in formulas, stating that the domain ${\rm Dom}(g \circ f)$ consists of all $x \in \mathrm{Dom}(f)$ such that $f(x) \in \mathrm{Dom}(g)$, or: 

$$
  \mathrm{Dom}(g \circ f) = \{ x \in \mathrm{Dom}(f) \mid f(x) \in \mathrm{Dom}(g) \} \; .
$$

Your task is, given two dictionaries $f$ and $g$, to compute the dictionary of $g \circ f$.


"""

def compose(f, g):
    """Given two dictionaries f and g, returns the dictionary of g \circ f."""
    # This can be done in a single line shorter than this comment.
    # You can use more lines; if you use more than half a dozen lines, you are doing it
    # in too complicated a fashion.
    # YOUR CODE HERE
    #gOfF = dict(f.get(g) for a in f) 
    result = {k: g.get(v) for k, v in f.items()} 
    for k, v in dict(result).items():
        if v is None:
            del result[k]
    return result

# Tests for composition. 10 points.

f = {'cat': 4, 'dog': 4, 'bird': 2, "centipede": 100}
g = {4: "quadruped", 2: "biped"}

check_equal(compose(f, g), {"cat": "quadruped", "dog": "quadruped", "bird": "biped"})

f = {0: 1, 1: 2}
g = {10: 11, 11: 12}
check_equal(compose(f, g), {})

"""## Problem 3: Classes

Here is a class that represents a square in the plane.  You create a square by specifying the center, and the edge.  Then, you can ask for the coordinates of the four quarters.  It's given here just as an example.
"""

class Square(object):
    
    def __init__(self, center, edge):
        assert isinstance(center, tuple)
        assert len(center) == 2
        self.center = center
        self.semiedge = edge / 2
        
    @property
    def edge(self):
        return 2 * semiedge
    
    @property
    def ur(self):
        """Returns the coordinates of the upper right corner."""
        (x, y) = self.center
        return x + self.semiedge, y + self.semiedge
    
    @property
    def lr(self):
        """Returns the coordinates of the upper right corner."""
        (x, y) = self.center
        return x + self.semiedge, y - self.semiedge

    @property
    def ul(self):
        """Returns the coordinates of the upper right corner."""
        (x, y) = self.center
        return x - self.semiedge, y + self.semiedge

    @property
    def ll(self):
        """Returns the coordinates of the upper right corner."""
        (x, y) = self.center
        return x - self.semiedge, y - self.semiedge
    
    def contains(self, point):
        """Returns whether the point is in the square."""
        x, y = point
        cx, cy = self.center
        return abs(x - cx) < self.semiedge and abs(y - cy) < self.semiedge

# Let's try it. 

s = Square((2, 2), 3)
print("UR corner:", s.ur)
print(s.contains((1, 1)))
print(s.contains((3, 4)))

"""Here is a hint for you: to test the type of a variable in Python, you can use the `isinstance` function."""

print(isinstance(s, Square)) # This prints True
print(isinstance(s, tuple)) # False
print(isinstance((1, 2), tuple)) # True

"""### Defining a Circle

Now it's your turn.  Define a `Circle` class.  A circle is created similarly to a square, specifying center and radius, as in: 

    Circle((2, 3), 4)
    
(a circle of radius 4 with center in (2, 3)). 

For a circle `c`, you should implement the following methods: 

* `c.contains_point(p)`: returns True/False according to whether the circle contains a given point `p`, specified as a pair (x, y) of coordinates, as in `p = (2, 3)`.  
* `c.contains_square(s)`: returns True/False according to whether the square `s` is completely contained in the circle `c`.
* `contains(x)`: returns True/False according to whether the circle contains the argument `x`, which can be either a square a point, or another Circle. 

_A little geometry reminder:_  

* A circle contains a square iff it contains all four corners of the square. 
* A circle $c_1$ contains a circle $c_2$ iff the distance between the centers of $c_1$ and $c_2$, plus the radius of $c_2$, is smaller than the radius of $c_1$. 

"""

import math # In case you need it.

class Circle(object):
    # YOUR CODE HERE
    def __init__(self, center, radius):
        assert isinstance(center, tuple)
        self.center = center
        self.radius = radius

    def contains_point(self,p):
        distance = ((self.center[0] - p[0])**2 + (self.center[1] - p[1])**2)**(0.5) #calculate distance from center of circle to point
        return distance < self.radius
        #reference: https://stackoverflow.com/questions/481144/equation-for-testing-if-a-point-is-inside-a-circle#:~:text=If%20the%20distance%20between%20them,point%20is%20outside%20the%20circle

    def contains_square(self,s):
        result = self.contains_point(s.lr) and self.contains_point(s.ll) and self.contains_point(s.ul) and self.contains_point(s.ur) 
        return result

    def contains(self,x):
        if type(x) is Square:
            return self.contains_square(x)
        elif type(x) is tuple:
            return self.contains_point(x)
        else:
            return (((((x.center[0] - self.center[0])**2 + (x.center[1] - self.center[1])**2)**(0.5)) + x.radius) <= self.radius)

# Let us test point containment first.  5 points. 

c = Circle((1, 2), 4)
check_equal(c.contains_point((2, 2)), True)
check_equal(c.contains_point((10, 20)), False)

# Then, let us check square containment.  5 points. 
c = Circle((1, 2), 4)
s1 = Square((2, 2), 1)
s2 = Square((3, 2), 6)
check_equal(c.contains_square(s1), True)
check_equal(c.contains_square(s2), False)

# Lastly, we check the contain method. 10 points. 
c1 = Circle((1, 2), 4)
c2 = Circle((1, 2), 4)
c3 = Circle((2, 2), 3)
c4 = Circle((2, 2), 4)
s1 = Square((2, 2), 1)
s2 = Square((3, 2), 6)
p1 = (2, 3)
p2 = (3, 4)
p3 = (4, 5)

check_equal(c1.contains(p1), True, msg="a")
check_equal(c1.contains(p2), True, msg="b")
check_equal(c1.contains(p3), False, msg="c")
check_equal(c1.contains(s1), True, msg="d")
check_equal(c1.contains(s2), False, msg="e")
check_equal(c1.contains(c2), True, msg="f")
check_equal(c1.contains(c3), True, msg="g")
check_equal(c1.contains(c4), False, msg="h")
