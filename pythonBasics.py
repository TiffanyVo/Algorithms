# -*- coding: utf-8 -*-
"""CSE_30_Fall_2020_Homework_1.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1zZwgloBRkIUr6QBcPBWcoj1dNOXbWVL6

Before you turn this problem in, make sure everything runs as expected. First, **restart the kernel** (in the menubar, select Kernel$\rightarrow$Restart) and then **run all cells** (in the menubar, select Cell$\rightarrow$Run All).

Make sure you fill in any place that says `YOUR CODE HERE` or "YOUR ANSWER HERE", as well as your name and collaborators below:
"""

NAME = "Tiffany-Ellen Vo"
COLLABORATORS = ""

"""---

# Homework 1: Python Basics
## CSE 20 Fall 2020

## Luca de Alfaro
Copyright Luca de Alfaro, 2020.  CC-BY-NC License.

# Instructions

## The Format of a Python Notebook

*This* is a Python Notebook homework.  It consists of various types of cells: 

* Text: you can read them :-) 
* Code: you should run them, as they may set up the problems that you are asked to solve.
* **Solution:** These are cells where you should enter a solution.  You will see a marker in these cells that indicates where your work should be inserted.  

```
    # YOUR CODE HERE
```    

* Test: These cells contains some tests, and are worth some points.  You should run the cells as a way to debug your code, and to see if you understood the question, and whether the output of your code is produced in the correct format.  The notebook contains both the tests you see, and some secret ones that you cannot see.  This prevents you from using the simple trick of hard-coding the desired output.
"""



"""## Working on Your Notebook in Colab

Please work on your notebook directly on Colab.  Please don't download it and work directly on your laptop.  Working on Colab has two key features: 

* The notebook is shared with the TAs, tutors, and with the instructor.  So when you report that you have difficulties, they can open your notebook and help you. 
* The notebook preserves the revision history, which is useful for many reasons, among which that none of your work can be lost, and we can see how you reached the solution.

### Using Colab for the first time (in this class)

**Set indent to 4 spaces.**
If this is the first time you use Colab, click on the gear icon on the top right, then on Editor.  There, set the indentation width to 4 spaces: this will keep your code correctly indented, which is very important.  You can configure the other options at your pleasure. 

### Running your notebook

**Running a cell.**
To run a cell of the notebook, either click on the icon to its top left, or press shift-ENTER (or shift-Return). 

**Disconnections.**
When you open a notebook, Google automatically connects a server to the web page, so that you can type code in your browser, and the code is run on that server.  If you are idle for more than a few minutes, Google keeps all you typed (none of your work is lost), but the server may be disconnected due to inactivity.  When the server is disconnected, it loses all memory of anything you have defined (functions, classes, variables, etc). 

If you do get disconnected, select Runtime > Run All (or Runtime > Run before) to ensure everything is defined as it should. 

### DO NOT

* **Do not add, delete, reorder, remove cells.**  This breaks the relationship between your work, and the grading system, making it impossible to grade your work.

### Debugging
To debug, you can add print statements to your code.  They should have no effect on the tests.  Just be careful that if you add too many of them inside loops and similar, you may cause for some of the tests we will do such an enormous amount of output that grading might timeout (and you may not get credit for an answer). 

### Asking for help
The tutors and TAs should have access to the notebook; otherwise, you can always share a link with them.  In this way, they can take a look at your work and help you with debugging and with any questions you might have.
"""



"""## Submitting Your Notebook

To submit:
* **Check your work.** Before submitting, select Runtime > Run All, and check that you don't get any unexpected error. 
* **Download the notebook.** Click on File > Download .ipynb . **Do not download the .py file.**
* **Upload.** Upload the .ipynb file to [this Google form](https://forms.gle/V55pDXK7CheXycgdA). 
* **Deadline:** Friday October 9, **11pm (NOT midnight)**.

## What Happens Next? 
In 2-3 days, the instructor will autograde all submitted homework.  You will find, in a Google Drive folder shared with you, a version of your notebook annotated with your total grade for the assignment, and the details of the grading for each question.

## The Test

Here the real homework begins!
"""

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

# First, notice that .split() splits a sentence according to white space, returning a list.

print("I love eating bananas".split())

# Second, recall that in Python, a[i:k] gives you the sub-list of a consisting 
# of a[i], a[i+1], ..., a[k-1].
a = "I love eating bananas".split()
print(a[2:4])

"""### Problem 1 part 1: generating the list of consecutive words in a sentence.

You are given a sentence, with words separated by white space.  You need to write a function `word_pairs` that outputs the list of consecutive words.  For example, if the input is: 

    "I love eating bananas"
    
Then the function `word_pairs` should output:

    [("I", "love"), ("love", "eating"), ("eating", "bananas")]
    
If the input sentence consists of fewer than two words, then `word_pairs` should output the empty list. 
**Be careful:** the result should be a list of tuples, not a list of lists.
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