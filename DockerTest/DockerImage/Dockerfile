FROM ubuntu:16.04

MAINTAINER Lniper

COPY apt.conf /etc/apt/apt.conf

RUN apt-get update -y

RUN apt-get install apache2 -y

EXPOSE 8080

ENTRYPOINT ["/app/tomcat7.sh"]
