## image tar
mount --make-rprivate /
sudo docker export $(docker run -d centos true) -o centos.tar

mkdir mycontainer
tar -C mycontainer -xf centos.tar

unshare --mount --uts --ipc --net --pid --fork bash
hostname mohammad


mount --bind mycontainers/
moun --move mycontainers /mycontainers


#### Pivot root
cd /mycontainers
mkdir oldroot
pivot_root . oldroot/
umount -a
unmount -l /oldroot/ # soft removing old mount to clean everything up
mount -t proc none /proc


## ensure you are isolated
exec bash
hostname # uts ns
ps aux # pid ns
ip a # net ns

