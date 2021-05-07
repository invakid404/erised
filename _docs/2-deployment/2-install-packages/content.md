---
Title: Install packages
---
To deploy Erised, you need [*docker*](https://www.docker.com), [*docker-compose*](https://docs.docker.com/compose/), and [*Xorg*](https://www.x.org).

Docker is the officially supported way of deploying Erised. It is used for running the project in an isolated environment with all the dependencies provided. Our Docker images are based on [*Alpine Linux*](https://alpinelinux.org), as it is minimal, lightweight, and has up-to-date packages.

Docker Compose is mostly used for easier deployment. It allows us to provide a ready-to-use `docker-compose.yml` file, so the users don't have to run long and complicated Docker commands to run Erised. All the configuration needed is contained in the YAML file.

Since Erised is a graphical application, it requires a window server to be running on the machine. Xorg is the de facto standard window system implementation for Unix-based systems, so we recommend using it. To actually show windows on the screen, a window manager needs to be running. We've chosen Matchbox - it is minimal and is intended for embedded systems, so it fits our use case.
