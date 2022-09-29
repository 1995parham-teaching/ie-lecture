### create network namespaces
ip netns add mohammad
ip netns add parham
ip netns
ip a
ip r
ip -n parham a
ip -n parham r

### setup network in a netns
####
ip link add head1 type veth peer name head2
ip link set head1 netns parham
ip link set head2 netns mohammad

ip -n parham addr add 192.168.2.1/24 dev head1
ip -n parham link set head1 up
ip -n mohammad addr add 192.168.2.2/24 dev head2
ip -n mohammad link set head2 up


### some checks
ip netns exec parham ping 192.168.2.2
ip netns exec parham arp
arp

## cleanup
ip -n parham link del head1 # head2 will be deleted automatically

## setup bridge
ip link add  my-bridge type bridge
ip link set my-bridge up

ip link add parham-end type veth peer name parham-br
ip link add mohammad-end type veth peer name mohammad-br

ip link set parham-end netns parham
ip link set mohammad-end netns mohammad

ip link set  mohammad-br master my-bridge up
ip link set  parham-br master my-bridge up


## access outside from inside
iptables -t nat -A POSTROUTING -s 192.168.2.0/24 -j MASQUERADE


## access from outside
iptables -t nat -A PREROUTING --dport 80 --to-destination 192.168.2.2:80 -j DNAT




