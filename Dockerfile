FROM debian:stable-slim
RUN apt-get update && \
    apt-get install -y build-essential valgrind libcriterion-dev && \
    rm -rf /var/lib/apt/lists/*
