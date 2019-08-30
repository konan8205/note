<!--
http://syrcose.ispras.ru/2009/files/02_paper.pdf
-->

# Binary Compatibility of Shared Libraries Implemented in C++ on GNU/Linux Systems.

Pavel Shvedm\
*Institute for System Programming, RAS*\
*email: shved@ispras.ru*

Denis Silakov\
*Institute for System Programming, RAS*\
*email: silakov@ispras.ru*

## How to Keep Compatibility

We call the code compiled into application *userspace code*; it includes inline functions of library headers and application code itself. The classes that are allowed to be instantiated in userspace code are called *userspace classes*, other classes are *internal*. The functions
that can be called from the userspace code are referred to as *userspace functions*.

Let us have *L* library that we’re going to alternate and get *L'* library, the new version. Then, *L'* will be binary compatible with L, if all following rules apply:

1. **any userspace function with ,,external linkage” shall retain its external name**. Therefore, you should keep true arguments type as they appear after all `typedef` substitutions and their number.
2. **no userspace function may be removed or made inline, either member or global, virtual or nonvirtual; no virtual function may be removed even for internal class**.
3. **no function implementation defined in cpp file may be changed in incompatible way**, i.e. if user calls new functions in an old way, that must be plausible and behavior must be the same. A special exception holds for bugfixes, but note, that they may break workarounds;
4. **layout of the first `sizeof(T)` bytes of types of directly accessible userspace global data must be the same**; this holds for both static class variables and for internal classes;
5. **the size of userspace class must be the same** if it has non-inline constructors; if all constructors are inline, you should use symbol versioning of sorts to prevent access to new part of the type layout from the new function;
6. **classes in hierarchy of all userspace classes must be the same and in the same order** unless the classes being moved through hierarchy are empty bases of non-dynamic class (but you still need an experiment to ensure that sizes are the same).
7. **dynamicity of classes in hierarchy of userspace class must be the same except for userspace class without virtual bases, where you can make non-dynamic class after all dynamic classes in preorder**;
8. **you can introduce new virtual functions overloading the old ones, except for the case of covariant overloading and overloading of function of a virtual base**. You should be assured that the call to this function will yield the same results as if it were called in a way allowed by *L* specifications;
9. **a completely new virtual function may be added to the end of the most derived class if its hierarchy doesn’t contain any virtual base**.

## Conclusion

The current C++ ABI is incapable to provide more compatibility even with additional restrictions upon the use of C++ constructs provided by library’s headers.

We should also note that the current `gcc` ABI is influenced by the desire to keep away from inserting elements of interpreted languages into ABI and by ,,incremental” way of binary representation (the architecture when the most common cases — single inheritance and simple virtual functions — induce more simple and fast binary representation). As a result, complex concepts are both considered unsafe and their uncareful use causes incompatibility.

## References

1. Urlich Drepper. [*How To Write Shared Libraries. 2006.*](https://software.intel.com/sites/default/files/m/a/1/e/dsohowto.pdf)
2. E. Gamma et. all [*Design Patterns: Elements of Reusable Object-Oriented Software*](https://github.com/dieforfree/edsebooks/blob/master/ebooks/Design%20Patterns%2C%20Elements%20of%20Reusable%20Object-Oriented%20Software.pdf)
3. [*Binary Compatibility Issues With C++*.](https://community.kde.org/Policies/Binary_Compatibility_Issues_With_C%2B%2B)
4. [*Using the GNU Compiler Collection (GCC)*, chapter 9](http://gcc.gnu.org/onlinedocs/gcc/Compatibility.html)
