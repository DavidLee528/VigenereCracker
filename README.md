# VigenereCracker
Crack Vigenere Ciphertext using statistic method (Index of Coincidence and Chi-square), the steps from ciphertext to possible key are as follow:

### Step 1

- Use `ic.cpp` to calculate index of coincidence of each possible period of key. 
- Guess the period according to the i.c result

### Step 2

- Use your guess period to calculate `Chi-square` using `chi-sq.cpp`
- Program will give you a most possible key

### Step 3

- Use the most possible key to decipher the ciphertext using `decipher.cpp`
- Observe the plaintext, if seems normal, accept it, if not, back to step 1 or 2
