# Docker file that shows current time

Build image:

```bash
docker image build -t cron-image .
```

Run it:

```bash
docker run -d \
    -e CRON_SCHEDULE="* * * * *" \
    -e FLIPDOT_HOST="http://192.168.178.61" \
    -e TZ="Europe/Berlin" \
    cron-image:latest
```
