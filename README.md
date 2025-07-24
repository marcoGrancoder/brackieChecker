# brackieChecker
## Automate your brackie checking (as well as quotes)

**brackieChecker** is an easy tool to use if you want to check for faulty brackets and quotes. Want the ease of bracket and quote checking without the heavy baggage of IDEs? **brackieChecker** is for you!

---

**brackieChecker** checks a file for brackets or quotes whithout a matching opening or closing counterpart.

---

Below is a guide to setup your **brackieChecker**, only in 2 steps!

1. Install *GNU C++ Compiler*!
   * If you hadn't already, install [*GNU C++ Compiler*](https://gcc.gnu.org/), **brackieChecker** will not be able to compute correctly!
2. Set it up!
   * Go into a *Unix-Based Terminal* and run your `setup.sh` file. It will setup for you automatically, give it some time.
3. You're ready to go!
   * Go into the directory where the file you want to bracket check is, and run `balanced (file here)`

It will print out a copy of the file along with BALANCED or UNBALANCED and, if so, a line describing the first faulty bracket/quote.

There is one issue: if you use an escape character and a quote, it will break. We'll get to fixing that later, hehe...

Thank you for using **brackieChecker**!
