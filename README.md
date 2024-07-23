# diningPhilosophers README

##### To compile with `-fsanitize=address` or `-fsanitize=threads`

`CC = gcc`

`CFLAGS = -Wall -Wextra -g -fsanitize=address -fsanitize=undefined`

`LDFLAGS = -fsanitize=address -fsanitize=undefined`

---

##### To run with `fsanitize`

`$0` is for this shell

`uname -m` to see arch

`setarch $(uname -m) -R $0` or `setarch x86_64 -R zsh`
