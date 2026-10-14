## image tar
# docker hub no longer has a centos image; stream9 from quay.io lacks ps, ip and hostname
sudo docker run --name centos quay.io/centos/centos:stream9 \
    dnf install -y procps-ng iproute hostname
sudo docker export centos -o centos.tar

mkdir mycontainer
sudo tar -C mycontainer -xf centos.tar

sudo unshare --mount --uts --ipc --net --pid --fork bash
mount --make-rprivate / # unshare already does this; it keeps our mounts from leaking out
hostname mohammad

# pivot_root needs the new root to be a mount point, so bind it onto itself
mount --bind mycontainer mycontainer

#### Pivot root
cd mycontainer
mkdir oldroot
pivot_root . oldroot/
mount -t proc none /proc # umount reads /proc/self/mounts, so this comes first
umount -l /oldroot/ # lazily detach the host's root and every mount under it
rmdir /oldroot


## ensure you are isolated
exec bash
hostname # uts ns
ps aux # pid ns
ip a # net ns

ls / # mnt ns: the image, not the host
