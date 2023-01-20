FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential

COPY . /app
WORKDIR /app
RUN chmod +x install.sh && ./install.sh
RUN make

EXPOSE 3000

ENTRYPOINT ["./bin/server"]
CMD ["3000"]
