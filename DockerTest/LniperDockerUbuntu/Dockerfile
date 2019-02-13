FROM testubuntu:v1
# FROM gcc:latest

RUN apt-get update
RUN apt-get install -y x11-apps
RUN apt-get install net-tools -y
RUN apt-get install iputils-ping -y
# RUN /bin/bash
# RUN apt-get install gcc -y


COPY DHW /home/lniper/Lniper_World/MyPro/MyPostgrade/DockerTest/DockerImage/

WORKDIR /home/lniper/Lniper_World/MyPro/MyPostgrade/DockerTest/DockerImage/

# RUN gcc DockerHW.c

CMD ["./DHW"]

