#!/bin/sh
set -e

MYSQL_PASSWORD=$(cat /run/secrets/db_password)
WP_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_password)
WP_USER_PASSWORD=$(cat /run/secrets/wp_user_password)

if [ ! -d /var/www/html/wordpress ]; then
    cd /var/www/html
    wget https://wordpress.org/latest.tar.gz
    tar -xzf latest.tar.gz
    rm latest.tar.gz
fi

cd /var/www/html/wordpress

if [ ! -f wp-config.php ]; then
    cp wp-config-sample.php wp-config.php
    sed -i "s/database_name_here/$MYSQL_DATABASE/" wp-config.php
    sed -i "s/username_here/$MYSQL_USER/" wp-config.php
    sed -i "s/password_here/$MYSQL_PASSWORD/" wp-config.php
    sed -i "s/localhost/mariadb/" wp-config.php
fi

until mariadb-admin ping -h mariadb -u"$MYSQL_USER" -p"$MYSQL_PASSWORD" --silent; do
    sleep 1
done

if ! wp core is-installed --path=/var/www/html/wordpress --allow-root; then
    wp core install \
        --path=/var/www/html/wordpress \
        --url="https://$DOMAIN_NAME" \
        --title="$WP_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASSWORD" \
        --admin_email="$WP_ADMIN_EMAIL" \
        --skip-email \
        --allow-root

    wp user create "$WP_USER" "$WP_USER_EMAIL" \
        --path=/var/www/html/wordpress \
        --role=author \
        --user_pass="$WP_USER_PASSWORD" \
        --allow-root
fi

mkdir -p /run/php
php-fpm8.2 -F
