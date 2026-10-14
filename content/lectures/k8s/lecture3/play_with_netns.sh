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
ip netns exec parham ping -c 3 192.168.2.2
ip -n parham neigh # parham learned mohammad's MAC address
ip neigh # the host has no 192.168.2.x entry: it is not on this cable

## cleanup
ip -n parham link del head1 # head2 will be deleted automatically

## setup bridge
ip link add my-bridge type bridge
ip addr add 192.168.2.254/24 dev my-bridge # the namespaces' gateway
ip link set my-bridge up

ip link add parham-end type veth peer name parham-br
ip link add mohammad-end type veth peer name mohammad-br

ip link set parham-end netns parham
ip link set mohammad-end netns mohammad

ip link set mohammad-br master my-bridge up
ip link set parham-br master my-bridge up

ip -n parham addr add 192.168.2.1/24 dev parham-end
ip -n parham link set parham-end up
ip -n mohammad addr add 192.168.2.2/24 dev mohammad-end
ip -n mohammad link set mohammad-end up

ip netns exec parham ping -c 3 192.168.2.2 # now through the bridge
ip netns exec parham ping -c 3 192.168.2.254 # and the host

## access outside from inside
ip -n parham route add default via 192.168.2.254
ip -n mohammad route add default via 192.168.2.254
sysctl -w net.ipv4.ip_forward=1
iptables -t nat -A POSTROUTING -s 192.168.2.0/24 ! -o my-bridge -j MASQUERADE
# docker sets the FORWARD policy to DROP; let the bridge's traffic through
iptables -A FORWARD -i my-bridge -j ACCEPT
iptables -A FORWARD -o my-bridge -j ACCEPT

ip netns exec parham ping -c 3 1.1.1.1

## access from outside
iptables -t nat -A PREROUTING -p tcp --dport 80 -j DNAT --to-destination 192.168.2.2:80
# from another machine, port 80 of this host now reaches the mohammad namespace
