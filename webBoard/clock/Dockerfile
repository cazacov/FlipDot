FROM alpine:3.7docker ps


RUN apk --no-cache add curl tzdata

ADD *.sh /
RUN chmod +x /*.sh

ENTRYPOINT ["/start.sh"]
CMD [""]