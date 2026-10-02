# Règles du Parsing — Webserv

## Fonctionnement général

Le parser lit le fichier de configuration ligne par ligne et fonctionne par **niveaux de profondeur (depth)** :

- `depth 0` → on attend le mot-clé `server {`
- `depth 1` → on est dans un bloc `server`, on lit ses directives
- `depth 2+` → on est dans un bloc `location`, on lit ses directives

Les données sont d'abord stockées dans des **structs temporaires** (`cTmp` pour le serveur, `lTmp` pour la location), puis ajoutées au vecteur final lors de la fermeture de l'accolade `}`.

Une fois tout le fichier lu, une passe de **validation sémantique** vérifie que les valeurs sont cohérentes et que les champs obligatoires sont présents.

---

## Format général

- Extension du fichier obligatoire : `.conf`
- Les commentaires commencent par `#` et sont ignorés
- Chaque directive se termine par un `;`
- Les blocs sont délimités par `{` et `}`

---

## Bloc `server`

```nginx
server {
    listen       8080;
    server_name  monsite.com;
    root         ./www;
    index        index.html;
    max_body_size 1048576;
    error_page   404 /errors/404.html;

    location / {
        ...
    }
}
```

### Directives disponibles

| Directive | Obligatoire | Valeur | Défaut |
|---|---|---|---|
| `listen` | ✅ oui | `port` ou `host:port` | — |
| `root` | non | chemin (`.` ou `./...`) | `.www` |
| `server_name` | non | alphanumérique + `-` + `.` | catch-all |
| `index` | non | nom de fichier | `index.html` |
| `max_body_size` | non | entier positif ≤ 1 073 741 824 (1 GB) | 1 MB |
| `error_page` | non | code (400–599) + chemin | — |

### Règles sur `listen`

- Port obligatoirement entre **1 et 65535**
- Host : `localhost` ou format `x.x.x.x` (chaque octet entre 0 et 255)
- Si pas de host précisé → écoute sur `0.0.0.0` (toutes interfaces)
- Exemple : `listen 8080;` ou `listen 127.0.0.1:8080;`

### Règles sur `server_name`

- Peut être absent → le serveur devient un **catch-all** (répond aux requêtes qui ne correspondent à aucun autre serveur)
- Caractères autorisés : lettres, chiffres, `-`, `.`

### Règles sur `error_page`

- Le code doit être entre **400 et 599**
- Le chemin doit commencer par `/`
- Exemple : `error_page 404 /errors/404.html;`

---

## Bloc `location`

```nginx
location /upload {
    methods      POST;
    root         ./uploads;
    autoindex    off;
    upload_dir   ./uploads/;
    client_max_body_size 1000;
}
```

### Directives disponibles

| Directive | Valeur | Défaut |
|---|---|---|
| `methods` | `GET`, `POST`, `DELETE` | `GET` |
| `root` | chemin du dossier servi | — |
| `index` | fichier par défaut | — |
| `autoindex` | `on` ou `off` | `off` |
| `cgi_path` | chemin de l'interpréteur CGI | — |
| `upload_dir` | chemin du dossier d'upload | — |
| `redirect` | chemin de redirection | — |
| `client_max_body_size` | limite locale en octets (écrase celle du serveur) | — |

### Règles sur les chemins (`root`, `upload_dir`, `redirect`, `cgi_path`)

- Doivent commencer par `.` ou `./`
- Exemple valide : `./www`, `./uploads/`
- Exemple invalide : `www`, `/var/www`

### Règles sur `methods`

- Valeurs autorisées uniquement : `GET`, `POST`, `DELETE`
- Si absent → `GET` par défaut
- Exemple : `methods GET POST;`

---

## Contraintes globales de validation

- Deux blocs `location` d'un même serveur ne peuvent **pas avoir le même chemin**
- Un bloc `server` sans directive `listen` est **invalide**
- Un fichier de configuration **vide** est invalide
- La `max_body_size` doit être **strictement positive** et ne pas dépasser 1 GB
- Si `max_body_size` vaut 0 (non définie) → le parser applique **1 MB par défaut** (comme nginx)

---
