FROM gcc:latest
RUN apt-get update && apt-get install -p make
WORKDIR /usr/src/app
COPY ..
RUN make
CMD ["./bin/programa"]
