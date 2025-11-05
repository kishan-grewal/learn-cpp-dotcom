## Modern C++ Golden Rules

1. **Const everything**
   All variables should be `const` unless they truly need to change.

   * Use `constexpr` when the compiler can *see* the result before the program runs — it’s evaluated at compile time.
   * Use `const` when the value is fixed *after the program starts* but can’t be computed at compile time (e.g. user input, function return, or runtime math).

   ```cpp
   constexpr int monthsInYear{12};     // known at compile time
   constexpr double pi{3.14159};       // compile-time constant

   const double taxRate{a * b};          // fixed after start, still const
   const double result{a + b};         // runtime expression → must be const, not constexpr
   ```

   Rule of thumb:

   > If the compiler can’t *see* the final value (even something like `a + b`), it must be `const`.

---

2. **Use `{}` for all initialisation**
   Always use brace initialisation — it’s safe, clear, and allows full expressions inside.

   ```cpp
   double savings{(income - expenses) * 0.8};
   int total{getCount() + offset()};
   ```

   Only exceptions:

   * `auto` variables → use `=`
   * Explicit lists → use `= {}`

   ```cpp
   auto total = income - expenses;
   std::vector<int> nums = {1, 2, 3};
   ```

---

3. **Use `std::size_t` for sizes and loops**
   Always use `std::size_t` for `.size()`, `.length()`, and counters.

   ```cpp
   for (std::size_t i{0}; i < vec.size(); ++i)
       std::cout << vec[i] << '\n';
   ```

---

4. **Prefer `emplace_back()` over `push_back()`**
   `emplace_back()` constructs elements directly inside containers — no extra copies.

   ```cpp
   entries.emplace_back(value, unit);
   ```

---

5. **Use `explicit`, `enum class`, and `= default`**

   * `explicit` stops automatic conversions.

     ```cpp
     explicit WeightEntry(double v);
     ```
   * `enum class` is the modern, scoped version of `enum`.

     ```cpp
     enum class Colour { Red, Blue, Green };
     ```
   * `= default` clearly requests the compiler’s normal implementation.

     ```cpp
     MyClass() = default;
     MyClass(const MyClass&) = default;
     ```

---

6. **Throw, don’t exit**
   Don’t use `exit()` in normal functions — throw exceptions instead.

   ```cpp
   throw std::runtime_error("Invalid data input");
   ```

7. **\n for prints, endl for debug**
   Use \n unless you are printing a debug log and need the buffer to be flushed quickly (endl = \n + flush).

   ```cpp
   std::cout << '\n' << std::flush;
   ```
   is equivalent to
   ```cpp
   std::cout << std::endl;
   ```