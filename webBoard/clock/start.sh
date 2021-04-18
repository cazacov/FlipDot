#!/bin/sh
set -e

echo "$CRON_SCHEDULE /curl.sh" >> /var/spool/cron/crontabs/root
crond -l 2 -f
