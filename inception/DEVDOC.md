# Developer Documentation

## Setting Up the Environment From Scratch

### Prerequisites
- A virtual machine running Debian or Alpine (penultimate stable version).
- Docker and Docker Compose installed on the VM.
- A `secrets/` folder at the repository root containing the required password files (see below).

### Required Files

**`.env`** (at the repository root) — non-sensitive configuration:

DOMAIN_NAME=login.42.fr
MYSQL_DATABASE=wordpress
MYSQL_USER=wp_user
WP_ADMIN_USER=your_non_admin_name
WP_ADMIN_EMAIL=admin@login.42.fr
WP_TITLE=Inception
WP_USER=second_user
WP_USER_EMAIL=user@login.42.fr


**`secrets/`** (at the repository root) — one file per secret, containing only the password value:

secrets/db_root_password.txt
secrets/db_password.txt
secrets/wp_admin_password.txt
secrets/wp_user_password.txt


These files must never be committed to Git with real values.

## Building and Launching the Project

From the repository root:

```bash
make up
```

This runs `docker compose -f srcs/docker-compose.yml up -d --build`, which:
1. Builds three custom images (`mariadb`, `wordpress`, `nginx`) from their respective Dockerfiles.
2. Creates the `inception_network` Docker network.
3. Creates two named volumes (`mariadb_volume`, `wordpress_volume`), bind-mounted to `/home/<login>/data/`.
4. Starts the containers in dependency order (`mariadb` → `wordpress` → `nginx`).

## Container Startup Logic

- **mariadb**: on first launch, initializes the database, reads root and user passwords from `/run/secrets/`, creates the WordPress database and user.
- **wordpress**: downloads WordPress core, configures `wp-config.php` using `.env` values and the DB password secret, waits for MariaDB to be reachable, then runs `wp core install` and `wp user create` via WP-CLI to fully automate setup (admin + second user), and finally starts `php-fpm`.
- **nginx**: generates a self-signed TLS certificate on first launch, then starts NGINX in the foreground as the sole entry point on port 443.

## Managing Containers and Volumes

```bash
make down      # stop and remove containers (keep data)
make fclean    # stop, remove containers, volumes, and images
make logs      # follow logs of all services
make ps        # list container status
```

To inspect a running container:

```bash
docker exec -it <container_name> sh
```

## Data Persistence

WordPress files and the MariaDB database are stored as Docker named volumes, physically located on the host at:

/home/<login>/data/mariadb
/home/<login>/data/wordpress


This ensures data survives container recreation (`docker compose down` without `-v`), but is fully reset with `make fclean`.

