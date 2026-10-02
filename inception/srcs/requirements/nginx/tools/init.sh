#!/bin/sh
set -e

mkdir -p /etc/nginx/ssl

openssl req -x509 -nodes -days 365 \
    -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/lde-sutt.key \
    -out /etc/nginx/ssl/lde-sutt.crt \
    -subj "/C=BE/ST=Brussels/L=Brussels/O=42/OU=Inception/CN=lde-sutt.42.fr"

chmod 600 /etc/nginx/ssl/lde-sutt.key

nginx -g "daemon off;"
