
# Instructions
Run tests
```
#This create the docker image for criterion
make image
#Running `make test` inside the container
docker run --rm -v $(pwd):/src -w /src minishell-criterion make test
```
