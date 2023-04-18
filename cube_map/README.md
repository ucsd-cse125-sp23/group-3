## How to: install dependencies using homebrew

---

1. install homebrew
    ```
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

2. install `glm` and `glfw`
    ```
    brew install glm glfw
    ```

3. check installation using
    ```
    brew info glm glfw
    ```
    if you are on Intel chip (you can check this by `arch` in terminal, if it returns `i386`, you are), you should expect libraries installed in `/usr/local/...`. Otherwise, libraries should be installed in `/opt/homebrew/...`

4. email TA Peter (bwu@ucsd.edu) for further complications during setup. 
