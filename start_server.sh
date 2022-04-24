#!/bin/bash

rm -rf /server/mouli
cp -r mouli server

ip=$(hostname -I | awk '{print $1}')

echo "Served on $ip:8888"

php -S 0.0.0.0:8888 -t server