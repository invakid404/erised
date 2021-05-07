#! Installation commands
```bash
# Make sure the system is up-to-date
sudo apt update
sudo apt upgrade

# Install docker
curl -fsSL https://get.docker.com | sudo sh - # Install docker

# Install docker-compose
sudo apt install -y python3 python3-pip
sudo python3 -m pip install -IU docker-compose

# Install a window manager, e.g. matchbox
sudo apt install matchbox-window-manager xorg
```
