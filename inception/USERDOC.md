# User Documentation

## What This Stack Provides

This infrastructure runs a complete WordPress website secured with HTTPS, composed of three services:

- **NGINX**: the single entry point to the website, serving traffic over HTTPS (TLS 1.2/1.3) on port 443.
- **WordPress (PHP-FPM)**: the content management system powering the website.
- **MariaDB**: the database storing all WordPress content and users.

## Starting and Stopping the Project

From the root of the repository:

```bash
make up      # builds and starts all services
make down    # stops and removes all containers
make restart # restarts everything
```

## Accessing the Website

Once the stack is running, open a browser and go to:
https://login.42.fr (https://lde-sutt.42.fr)
You will see a warning about the certificate — this is expected, as it is self-signed. Click "Advanced" then "Continue" to proceed.

## Accessing the Administration Panel

The WordPress admin panel is available at:
https://login.42.fr/wp-admin


Two accounts exist in the database:
- An **administrator** account (full access to manage the site).
- A **regular user** account (limited permissions, e.g. author role).

## Locating and Managing Credentials

All passwords are stored as Docker secrets, located in the `secrets/` folder at the root of the repository:

| File | Purpose |
|---|---|
| `db_root_password.txt` | MariaDB root password |
| `db_password.txt` | MariaDB WordPress user password |
| `wp_admin_password.txt` | WordPress administrator password |
| `wp_user_password.txt` | WordPress regular user password |

Usernames and non-sensitive settings (domain, database name, titles) are defined in the `.env` file at the root of the repository.

## Checking That Services Are Running Correctly

To check container status:

```bash
docker ps -a
```

All three containers (`nginx`, `wordpress`, `mariadb`) should show status `Up`. If a container shows `Restarting`, check its logs:

```bash
docker compose -f srcs/docker-compose.yml logs <service_name>
```

To verify the website responds correctly:

```bash
curl -kv https://localhost
```

A successful response returns HTTP 200 with WordPress HTML content.
