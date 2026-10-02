COMPOSE = docker compose -f srcs/docker-compose.yml

all: up

build:
	$(COMPOSE) build

up:
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

stop:
	$(COMPOSE) stop

start:
	$(COMPOSE) start

restart: down up

clean: down
	docker system prune -af

fclean: down
	docker system prune -af --volumes
	sudo rm -rf /home/$(USER)/data/mariadb/*
	sudo rm -rf /home/$(USER)/data/wordpress/*

logs:
	$(COMPOSE) logs -f

ps:
	$(COMPOSE) ps -a

re: fclean up

.PHONY: all build up down stop start restart clean fclean logs ps re
