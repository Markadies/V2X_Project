include recipes-core/images/core-image-base.bb


IMAGE_FEATURES += "ssh-server-dropbear"
IMAGE_INSTALL += "bluez5 i2c-tools dhcpcd iptables wpa-supplicant lane-detection"
