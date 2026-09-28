
# Instructions
Run tests
```sh
#This create the docker image for criterion
make image
#Running `make test` inside the container
docker run --rm -v $(pwd):/src -w /src minishell-criterion make test
```
Check memory leak
```sh
valgrind --suppressions=readline.supp --leak-check=full \
--show-leak-kinds=all --track-fds=yes ./minishell
```

Note:
To close HEREDOC fd (pipe read end) after consuming
