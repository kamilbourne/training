FROM ubuntu
LABEL maintainer="Kamil Nowak"
LABEL cycle="Kurs"

USER root
COPY ./002.serv.bash /

RUN chmod 755 /002.serv.bash
RUN apt -y update
RUN apt -y install bash

USER nobody

ENTRYPOINT [ "/002.serv.bash" ]
