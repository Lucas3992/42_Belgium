*This project has been created as part of the 42 curriculum by lde-sutt.*

# Inception

## Description

Inception is a System Administration project that consists of setting up a small, containerized infrastructure using Docker and Docker Compose. The goal is to virtualize several services — a database, a web application, and a reverse proxy — each running in its own dedicated container, built from scratch using custom Dockerfiles rather than pre-made images.

The stack deployed here provides a fully functional WordPress website, served securely over HTTPS, backed by a MariaDB database, with the entire setup automated so that a single command brings the whole infrastructure up from nothing.

## Architecture

HTTPS (443, TLS 1.2/1.3)
Browser ─────────────────────────────▶ NGINX
│
│ FastCGI (9000)
▼
WordPress
(PHP-FPM)
│
│ MySQL (3306)
▼
MariaDB



All three containers communicate through a dedicated Docker network (`inception_network`). NGINX is the only container exposed to the host, on port 443. WordPress and MariaDB are only reachable from within the network.

## Instructions

### Prerequisites
- A virtual machine running Debian (bookworm) or Alpine.
- Docker and Docker Compose installed.
- A `secrets/` folder at the repository root containing the required password files.

### Installation and Execution

Clone the repository, make sure the `.env` file and `secrets/` folder are correctly filled in, then run:

```bash
make up
```

This single command builds the three custom images, creates the Docker network and volumes, and starts every container in the correct order. WordPress is automatically installed and configured — no manual setup through the browser is required.

To stop the project:

```bash
make down
```

To fully reset the project (containers, volumes, and data):

```bash
make fclean
```

See `USERDOC.md` for day-to-day usage and `DEVDOC.md` for detailed developer setup instructions.

## Quick Database Check Tutorial

Once the stack is running, you can verify that WordPress data was correctly written to MariaDB.

**1. Connect to the MariaDB container:**

```bash
docker exec -it mariadb sh
```

**2. Connect to the database using the root credentials (from your secrets):**

```bash
mariadb -u root -p
# paste the content of secrets/db_root_password.txt when prompted
```

**3. List the available databases:**

```sql
SHOW DATABASES;
```

You should see the `wordpress` database (or the name set in `MYSQL_DATABASE`).

**4. Switch to it and list its tables:**

```sql
USE wordpress;
SHOW TABLES;
```

You should see WordPress's default tables, including `wp_users`, `wp_options`, `wp_posts`, etc.

**5. Check that the two required users exist:**

```sql
SELECT ID, user_login, user_email FROM wp_users;
```

This should return exactly two rows: the administrator account (with a username that does not contain "admin"/"administrator") and the second, non-administrator user.

**6. Exit the database and the container:**

```sql
EXIT;
```
```bash
exit
```

## Resources

- [Docker documentation](https://docs.docker.com/)
- [Docker Compose documentation](https://docs.docker.com/compose/)
- [WordPress Codex](https://codex.wordpress.org/)
- [WP-CLI documentation](https://wp-cli.org/)
- [NGINX documentation](https://nginx.org/en/docs/)
- [MariaDB Knowledge Base](https://mariadb.com/kb/en/)

**AI usage**: AI assistance was used throughout this project to help debug container startup issues (e.g. a 502 Bad Gateway caused by a PHP-FPM `listen.allowed_clients` misconfiguration), to design the Docker Compose volume and secrets structure. Every suggestion was tested, reviewed, and understood before being integrated, and discussed with peers where relevant.

## Project Description

This project relies entirely on Docker to isolate each service (NGINX, WordPress/PHP-FPM, MariaDB) into its own container, built from custom Dockerfiles based on Debian bookworm. No pre-built images were pulled from Docker Hub, in line with the subject's requirements.

### Virtual Machines vs Docker

A Virtual Machine virtualizes an entire operating system, including its own kernel, which makes it heavier and slower to start. Docker containers share the host's kernel and only package the application and its dependencies, making them significantly lighter and faster to start — while still providing process and filesystem isolation between services.

### Docker Secrets vs Environment Variables

Environment variables (stored in `.env`) are used for non-sensitive configuration (usernames, domain name, database name). Docker Secrets are used for all passwords, mounted at runtime as files inside `/run/secrets/` in each container. Unlike environment variables, secrets are not visible via `docker inspect` or in the container's process list, which reduces the risk of credential leakage.

### Docker Network vs Host Network

A dedicated bridge network (`inception_network`) connects the three containers, allowing them to resolve each other by service name (e.g. `wordpress` can reach `mariadb` directly) without exposing internal ports (3306, 9000) to the host machine. Using the host network instead would remove this isolation and expose every container port directly on the VM, which is explicitly forbidden by the subject.

### Docker Volumes vs Bind Mounts

Named Docker volumes are used for persistent data (`mariadb_volume`, `wordpress_volume`), configured with `driver_opts` to physically store their contents in `/home/lde-sutt/data/`. This satisfies both the subject's requirement to use named volumes (not raw bind mounts) and the requirement that data be stored under the learner's home directory, combining the management benefits of named volumes with a predictable host-side location.
