---
tags: class_note, class_note_online_course
---

[toc]

# Category Thoery Note

Lecture Videos (Youtube): https://www.youtube.com/watch?v=I8LbkfSSR58&list=PLbgaMIhjbmEnaH_LTkxLI7FMa2HsnawM_


# 1. What is category

CATEGORY = (set of objects, set of morphisms)
EMPTY CATEGORY = (Empty set, empty set)

## Objects & Morphisms

In categort theory, objects is any thing in the objects set. Like nodes & arrows in graph, a morphism is a relationship from an object to an other object.

## Properties of Morphisms

Morphisms in category must be associative:
  - associative: $f, g, h$ are morphisms, $f \circ (g \circ h) = (f \circ g) \circ h$

## Some special morphisms

A morphism $f: X → Y$ is called a **monomorphisms** if $f \circ g1 = f \circ g2$ implies $g1 = g2$ for all morphisms $g1, g2: Z → X$. Monomorphisms has a **left inverse** if there is a morphism $g: Y → X$ such that $g \circ f = id_X$.

A morphism $f: X → Y$ is called an **epimorphism** if $g1 \circ f = g2 \circ f$ implies $g1 = g2$ for all morphisms $g1, g2: Y → Z$. Epimorphism has a **right inverse** if there is a morphism $g: Y → X$ such that $f \circ g = id_Y$.

A morphism $f: X → Y$ is called an **isomorphism** if there exists a morphism $g: Y → X$ such that $f \circ g = id_Y$ and $g \circ f = id_X$. $g$ is called simply the **inverse** of $f$.

## Pure vs. Dirty Function

In programming, a pure function is a function that is stable from its input types to output types, it can not be effected by anything out of its scope and have no side effect outside its scope.


# 2. Some Categories

## Free Categories

A category is free category iff $∀$ morphisms $f, g$ , $(f \circ g)$ is also in its morphisms. Example: `funciton-composition.cpp`

## Monoid

Monoid(單群/么群) is a kind of group that is simplest category
Monoid $(S, ⊕)$ has:

- A binary operation ⊕
    + closed
    + associative
- The identity

The group $(Z^+_N, +)$ is a monoid where $Z^+_N$ is set of positive finite integers smaller than $N$, $N$ is a prime number, and $+$ is a binary operation of addition modulo N.

A monoid can be defined by only two element: 
1. the identity element
2. the bianry operation 


# 3. Kleisli Categories

Consider following function:

``` C++
std::string logger;
bool neg(bool b) {
    logger += "Neg!";
    return !b;
}
```

This function is not a pure function as it is not stable AND have side effect. To rewrite it as a pure function, we let the output type of function be an *embellished type* made of `bool b` and `string logger`:

``` C++
typedef pair<bool, string> bool_writer;
bool_writer neg(bool n) {
    return bool_writer(!n.first, "Neg!");
}
```

## Definition

We want to define a function composition operater that *chain up* our log strings together. There is a category out of it: Kleisli category:

- Let $m$ be a morphism that make the input/output of a function into *embellished type*.  
- $m$ is a part of so-called *monad*. (Detailed in latter chapter.)  
- Let f, g be morphisms in Kleisli Category:  
  - $f: T_1 → m(T_2)$
  - $g: T_2 → m(T_3)$
- The composition under Kleisli is $(g \circ f): T1 → m(T3)$

## Comparison table

Let's say there is a category $C$, object $X, Y ,Z$ and two morphisms $f: X → Y$ and $g: Y → Z$.

Their Kleisli counterpart over morphism $m$ are category $C_k$, object $X', Y', Z'$ and two morphisms $f': X' → Y'$ and $g': Y' → Z'$.

| $C$        | $Ck$       |
| ---        | ---        |
| $m$        | $id_{X'}$  |
| $m \circ f$    | $f'$       |
| $m \circ g$    | $g'$       |
| $m \circ g \circ f$| $g' \circ f'$  |

### Example Code

`kleisli.cpp`


# 4. Initial, Terminal Object & Duality

## Initial and Terminal Object

- An object $I$ is a inital object in $C$ if for every object $X$ in $C$, there exists exactly one morphism $I → X$.
- An object $T$ is a terminal object in $C$ if for every object $X$ in $C$, there exists exactly one morphism $X → T$.  

Initial & terminal objects are *unique up to unique isomorphism*.

### Example

- The empty set is the unique initial object in *the category of sets*. Because there is exactly one empty function for each set, thus the empty function $\varnothing → X$ is not equal to $\varnothing → Y$ if and only if $X \ne Y$
- Every one-element set (singleton) is a *terminal object* in *the category of sets*.

## Opposite Category

$C_{op}$ of a given category $C$ is formed by reversing the morphisms, i.e. interchanging the source and target of each morphism.

## Duality

Given a statement regarding the category $C$, by interchanging the source and target of each morphism as well as interchanging the order of composing two morphisms, a corresponding dual statement is obtained regarding the opposite category $C_{op}$. In other words, if a statement is true about $C$, then its dual statement is true about $C_{op}$.

Applying duality, this means an *initial object* in a category $C$ is a *terminal object* the category $C_{op}$


# 5. Product & Coproudct

## Definition

A **product** of object $A$ and $B$ is a object $C$ equipped with two morphisms $p_1: C → A$ and $p_2: C → B$ satisfying the following universal property:
- For every object $D$ and every pair of morphisms $q_1: D → A$ and $q_2: D → B$ there is a *unique* morphism $m: D → C$ such that $q_1 = p_1 \circ m$ and $q_2 = p_2 \circ m$. ($m$ factorize $q_1$ and $q_2$)

```
 D (any product candidate)
    |        |         |
(q1)| (exist unique m) |(q2)
    v        v         v 
    A  <-p1- C -p2->   B 
```

```mermaid
graph TD
    D -->|q1| A
    C -->|p1| A
    C -->|p2| B
    D -->|q2| B
    D -.->|!m| C
```

We denote the product of $A$ and $B$ as $A \times B$

Whether a product exists may depend on the category or on $A$ and $B$. If it does exist, *it is unique up to canonical isomorphism*, so one may speak of *the* product.  
The product is the terminal object in the category of product candidates.

The morphisms $p1$ and $p2$ are called the **canonical projections** or **projection morphisms**.

## Examples of Product

The classic example of product is a **pair**. But to make a clearer example, let's say we want a class for the product of `int` and `bool`. This class `Product` will have two method:

``` C++
class Product {
    int toInt(); // Product -> int
    bool toBool(); // Product -> bool
}
```

How do we know whether a implementation of `Product` is the product of not? 

``` C++
class BadProduct {
    int data;
    int toInt() { return data; }
    bool toBool() { return true; }
}

class CounterBadProduct {
    int data1
    bool data2;
    int toInt() { return data1; }
    bool toBool() { return data2; }
    BadProduct toBadProduct(); // does not exist
}
```

Here, `BadProduct` is not a product of `int` and `bool`, because there is a `CounterBadProduct` such that there is no morphism `toBadProduct: CounterBadProduct → BadProduct`.  

We expect for every instance `p` of `CounterBadProduct`, it holds that `p.toBool() == p.toBadProduct().toBool()`. But apparently it is not the case if `p.toBool() == false`.

``` C++
class BadProduct2 {
    int data1;
    int data2;
    bool data3;
    BadProduct2(int d1, int d2, bool d3) :
        data1(d1), data2(d2), data3(d3) {};
    int toInt() { return data1; }
    bool toBool() { return data3; }
}

class CounterBadProduct2 {
    int data1;
    bool data2;
    int toInt() { return data1; }
    bool toBool() { return data2; }
    BadProduct2 toBadProduct2() { // is not unique
        return BadProduct2(data1, /* can be any integer */, data2);
    }; 
}
```

In ths case, there exists `toBadProduct2()` such that, for every instance `p` of `CounterBadProduct2`, it holds that `p.toBool() == p.toBadProduct2().toBool()` and `p.toInt() == p.toBadProduct2().toInt()`. However, `toBadProduct2()` is not unique. So `BadProduct2` is not the product of `int` and `bool`.

``` C++
class PossibleProduct {
    int data1;
    int toInt() { return data1 / 2; }
    bool toBool() { return data % 2 > 0; }
}

class CounterPossibleProduct {
    int data1;
    bool data2;
    int toInt() { return data1; }
    bool toBool() { return data2; }
    BadProduct CounterPossibleProduct(); // could exist if int is a infinite set
}
```

If cardinality of `int` is infinite, then this `PossibleProduct` is a product of `int` and `bool`. However, in C++, cardinality of `int` is at most $2^{64} - 1$. So it can't be the product in this programming language, considering an instance `p` of `CounterPossibleProduct` where `p.toInt() == pow(2, 62)`.

## What is "unique up to isomorphism"

Unique up to isomorphism means that all the objects satisfying a given definition are isomorphic -- there must exist an isomorphism between those objects.  

if every isomorphism between those objects are unique, it is called **"unique up to *unique* isomorphism"**

### Why are they "unique"?

All isomorphic objects have the same relationship with other objects.   

Suppose $A \simeq B$ with isomorphism $α: A → B$, then for all object $Y$, there are $Hom(A, Y)$ and $Hom(B, Y)$ and a bijection function $ϕ: Hom(A, Y) → Hom(B, Y)$.  

$Hom(A, Y)$ means the set of all morphism from $A$ to $Y$

Because for all $f: A → Y$ and $g: B → Y$:
$$
\begin{aligned}
    ϕ(f) &= g = f \circ α^{-1} \\
    ϕ^{-1}(g) &= f = g \circ α \\
\end{aligned}
$$

we show that $ϕ^{-1} \circ ϕ: Hom(A, Y) → Hom(A,Y)$ is the identity function:

$$
\begin{aligned}
    (ϕ^{-1} \circ ϕ)(f) &= ϕ^{-1}(ϕ(f)) \\
    &= ϕ^{-1}(f \circ α^{-1}) \\
    &= f \circ α^{-1} \circ α \\
    &= f \circ id_A \\
    &= f \\
\end{aligned}
$$

Strictly speaking we should also show that $ϕ \circ ϕ^{−1}$ is also the identity function, but the proof is almost identical so we’ll omit it.

So we have shown that **there is a bijection between sets of morphisms of isomorphic objects**, and therefore they are formally of the same shape.

## Coproduct: Dual of Product 

Coproduct is basically the product with reverse direction of morphisms in the definition.

Let object $C$ be the product of object $A$ and $B$, the coproduct of $C$ is $C_{op}$ equipped with two morphisms $p_1: A → C$ and $p_2: B → C$ satisfying the following universal property:  
 - For every object $D$ and every pair of morphisms $q_1: A → D$ and $q_2: B → D$ there is a *unique* morphism $m: C → D$ such that $q_1 = (m \circ p_1)$ and $q_2 = (m \circ p_2)$. ($m$ factorize $q_1$ and $q_2$)

We denote the product of $A$ and $B$ as $A \oplus B$

The programming counterpart of a coproduct is a **tagged-union**. Consider a structure `Either` that can be either a type A or type B but not both. We can implement it in this way:


``` C++
// The object Either is the coproduct of type A and type B
template <typename A, typename B>
class Either {
    private:
    enum {isLeft, isRight} tag;
    A left;
    B right;

    public:
    // mapping from A -> Either
    Either set(A a) {
        this.tag = isLeft;
        left = a;
    }

    // mapping from B -> Either
    Either set(B a) {
        this.tag = isRight;
        right = b;
    }

    // return defaultValue if Either is not type A currently
    A getLeft(A defaultVal) {
        return (this.tag == isLeft) ? this.left : defaultVal;
    }

    // return defaultValue if Either is not type B currently
    B getRight(B defaultVal) {
        return (this.tag == isRight) ? this.right : defaultVal;
    }
}
```

## Product and Coproduct as Algebra

A category and product/coproduct forms symmetric monoid.

Commutativity: it is pretty obvious that there existed a unique isomorphism from $A \times B$ to $B \times A$, which is $Swap()$.

Associativity: we can find a isomorphism from $A \times (B \times C)$ to $(A \times B) \times C$. To show that, consider the function that turns $(a, (b, c))$ into $((a, b), c)$. This function exists and has inverse.

Identity:
- For product, it is the terminal object $T$.
- For coproduct, it is the initial object $I$.

Let $P = A \times T$, $p_1: P → A$, and $p_2: P → T$. Let any object $Q$ with $q_1: Q → A$ and $q_2: Q → T$. By the universal property of the product, there exist an unique the morphism $m: Q → P$ such that $q_1 = p_1 \circ m$ and $q_2 = p_2 \circ m$. And because $T$ is the terminal object, $p_2$ and $q_2$ are unique.

Let $Q = A$, $q_1 = id_A$ and $q_2: A → T$, it gives that $q_1 = p_1 \circ m = id_A$. We thus have:

$$
\begin{aligned}
    id_A &= p_1 \circ m \\
    id_A \circ p_1  &= p_1 \circ m \circ p_1 \\
    p_1  &= p_1 \circ m \circ p_1 \\
\end{aligned}
$$

Also consider:

$$
\begin{aligned}
    q_2 &= p_2 \circ m \\
    q_2 \circ p_1 &= p_2 \circ m \circ p_1 \\
\end{aligned}
$$

since $q_2 \circ p_1$ is morphism from $P → T$, it is unique, thus $q_2 \circ p_1 = p_2$. We have:

$$
p_2 = p_2 \circ m \circ p_1 \\
p_1 = p_1 \circ m \circ p_1
$$

By uniqueness of identity, $m \circ p_1 = id_P$

Since $m$ is inverse of $p_1$, and vice versa. $p_1$ is an isomorphism. Thus $P \simeq A$.

In similar way, we can prove the identityness of initial object $I$ in coproduct operation.

Product is **distributive** with respect to coproduct. It makes the category equipped with product and coproduct a **semi-ring**.

In C++17 `std::optional<T>` is the coproduct of a initial object `nullopt_t` and the type `T`. We can write it in algebra as $optional(T) = 1 \oplus T$

In Haskell, the `List` type is recursively defined as:

```Haskell
data List x = Empty | x : (List x)
```

We can write down the difinition in algebra:

$$
\begin{aligned}
List(X) &= 1 + X \times List(X) \\
List(X) &= 1 + X \times (1 + X \times List(X)) \\
List(X) &= 1 + X \times 1 + X \times X \times List(X) \\
\vdots \\
List(X) &= 1 + X + X^2 + X^3 \cdots
\end{aligned}
$$

# Functors

**Functor** is the mapping from category to category.

To map two categorys $C$ and $D$:
- Map the set of objects in $C$ to the set of objects in $D$
- Map the set of morphisms from $C$ to the set of morphisms in $D$, in the way that **structure is preserved**

For a functor $F: C → D$, for all $f: X → Y$ and $g: Y → Z$ in $C$, it holds that:
- $F(f): F(X) → F(Y)$
- $F(g \circ f): F(X) → F(Z) = F(g) \circ F(f)$
- $F(id_X) = id_{F(X)}$

![](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b3/Commutative_diagram_of_a_functor.svg/260px-Commutative_diagram_of_a_functor.svg.png)


**Functors are morphisms.** They can do compositions too. For categories $C, D, E$, if there are functor $F: C → D$ and $G: D → E$, we can have composed functor $H = G \circ F: C → E$.

Functors and categories make a **category of categories**.

## Special Functors

- **Faithful functor**: injective on the morphism sets
- **Full functor**: surjective on the morphism sets.
- **Constant functor**: Constant functor at $X$, denoted as $\Delta_X: C → D$, maps all objects from category $C$ to a fixed object $X \in D$ and maps all the morphisms to the identity morphism $id_X$.
- **Identity functor**: maps $C$ to itself. Nothing is changed.

## Examples of functor in programming

### Function Mapper

Let say we have some functions that input and output numbers (`int`, `float`, `double`, etc.). But at certain point, we want these functions to work on numbers encoded as `string`. In this case, a functor to wrap the functions is useful. See example code: `functor.cpp`

### Safe `list::pop_front`

A standard C++ `list::pop_front` function has undefined behavior when the input list is empty. It is good that we return a `optional<list<T>>` object for safety. However, we don't want to re-write the functions working on `list` for `optional<list>`. We can simply write the functor `optionalized()` to transform the original function from category of `T` to the category of `optional<T>`.

``` C++
template <typename T>
std::optional<std::list<T>> safe_get_tail(std::list<T> list) {
    if (list.size() == 0)
        return std::nullopt;
    std::list<T> resultList(list);
    resultList.pop_front();
    return resultList;
}

template <typename T, typename U>
auto optionalized(T (*func)(U)) {
    return [func] (std::optional<U> input) {
        if (input)
            return func(input);
        return std::nullopt;
    }
}

double square_map(list<double> list) {
    std::list<double> resultList;
    std::transform(list.begin(),list.end(),resultList.begin(),
        [](double x) {return x * x;}
    );
    return resultList;
}

int main() {
    std::list<double> goodList = {1, 3, 5, 7, 9};
    std::list<double> emptyList = {};
    auto goodTail = safe_get_tail(goodList);
    auto emptyTail = safe_get_tail(emptyList);
    auto goodSquaredTail optionalized(square_map)(goodListTail);
    auto emptySquardTail optionalized(square_map)(emptyTail);
    return 0;
}
```

## Bifunctors

A **bifunctor** is a functor
- from a **product category**
- to a category

### Product Category

Let there be two category $C, D$, the product of $C$ and $D$ contains all possible the pairs of objects and morphisms between $C$ and $D$, that is
- $obj(C \times D) = \{ (x, y) \mid x \in obj(C), y \in obj(D) \}$
- $mor(C \times D) = \{ (f, g) \mid f \in mor(C), g \in mor(D) \}$


The morphism composition works like vectors.

So a bifunctor takes the form of $F: (C \times D) → E$.

### Pair of Objects and Morphisms?

Actually, we can construct a new category $C'$ that
- $obj(C') = \{ x \times y \mid x \in obj(C), y \in obj(D) \}$
- $mor(C') = \{ f \times g \mid x \in mor(C), y \in mor(D) \}$

Same with coproduct:
- $obj(C'') = \{ x \oplus y \mid x \in obj(C), y \in obj(D) \}$
- $mor(C'') = \{ f \oplus g \mid x \in mor(C), y \in mor(D) \}$

And there are obvious bifunctors $F': (C \times D) → C'$ and $F'': (C \times D) → C''$

### Wait... What is the Product and Coproduct of Morphism?

The product of morphisms $f: A → A'$ and $g: B → B'$, denoted by $f \times g$, is the unique morphism that

$$
f \times g: (A \times B) → (A' \times B')
$$

$f \times f'$ is unique because
- As the definition of product of objects says, object $(A \times B)$ has morphism $p: (A \times B) → A$ and $q: (A \times B) → B$
- We have composite morphisms $f \circ p: (A \times B) → A'$ and $g \circ q: (A \times B) → B'$
- The definition of product of objects also says that, for any object that has morphism to $A'$ and $B'$, there exists an unique morphism from that object to $A' \times B'$
- So, $(A \times B) → (A' \times B')$ is unique.

Similar proof goes with coproduct.

### Examples of Bifunctor in Programming

In Haskell, bifunctor looks like

``` haskell
class Bifunctor f where
    bimap (a -> a') -> (b -> b') -> (f a b -> f a' b')
```

The `Either` class, defined earlier in C++ to explain coproduct, is a bifunctor if it is applied on functions

``` C++
// The object Either is the coproduct of type A and type B
template <typename A, typename B>
class Either {

    /* ... */

    template <typename P, typename Q>
    auto either_do(
        P (*funcLeft)(A),
        Q (*funcRight)(B)
    ) {
        return [funcLeft, funcRight] (Either<A, B> input, A leftDefault, B rightDefault) {
            Either<P, Q> result;
            if (input.tag == isLeft)
                result.set(
                    funcLeft(input.getLeft(leftDefault))
                );
            else
                result.set(
                    funcRight(input.getRight(rightDefault))
                );
            return result;
        }
    }
}
```
