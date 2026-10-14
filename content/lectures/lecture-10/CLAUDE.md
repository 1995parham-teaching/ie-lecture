# Lecture 10 — Virtualization

39 slides (plus the generated title), 3 vertical stacks. Topics (TOC
indices): `0` IaaS, PaaS, SaaS · `1` Virtual Machine · `2` Containers.

Arc: the NIST cloud-computing definition → IaaS/PaaS/SaaS → virtualization
techniques → hypervisors → CPU and IO virtualization → QEMU → containers →
containers vs VMs → namespaces → container engines → Docker (images,
containers, Dockerfile, layers, CLI, volumes, Compose).

## Facts worth not re-deriving

- **VirtualBox and VMware are not IaaS providers.** They are hypervisors. The
  deck used to list them under IaaS.
- The runtime is **rkt**, not "rtk", and it is discontinued. containerd and
  CRI-O are the current ones and are on the slide.
- The Compose sample **must parse**. The one in the deck was unparseable —
  `db` indented three spaces, `wordpress` two. Run any YAML you add through a
  parser.

## The Dockerfile sample

Rewritten and pinned; do not casually update it:

- Base is `ubuntu:24.04`, **not** `ubuntu:latest` — a moving base makes the
  layer-caching slide meaningless.
- `apt-key` was removed in Ubuntu 22.04. The sample uses `/etc/apt/keyrings`
  with `signed-by=`.
- MongoDB is 8.0 (was 3.2).
- `apt-get update` runs **before** `apt-get install`, in the same layer.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                     | Slide                                                   |
| ------------------------ | ------------------------------------------------------- |
| `vm-vs-container.svg`    | Virtualization Techniques — VM stack vs container stack |
| `hypervisor-types.svg`   | Hypervisors — type 1 vs type 2                          |
| `cpu-virtualization.svg` | CPU Virtualization — binary translation, PV, VT-x       |
| `vcpu-scheduling.svg`    | Virtual CPUs — 6 vCPUs on 4 CPUs                        |
| `io-virtualization.svg`  | IO Virtualization — emulated e1000 vs virtio            |
| `qemu-kvm.svg`           | The Quick Emulator (QEMU) — threads, `/dev/kvm`         |
| `namespaces.svg`         | Namespaces — one process seen from inside and outside   |
| `container-runtimes.svg` | Who Runs the Container? — docker/kubelet/podman to runc |
| `image-layers.svg`       | Image Layers — the deck's Dockerfile as layers          |

- `namespaces.svg` is a real run: `docker run -d --hostname web alpine:3.20
sleep 300`, then `ps`, `hostname`, `ip addr` and `readlink /proc/1/ns/*`
  inside and (with `--pid=host --net=host --uts=host`) outside. It was taken on
  Docker Desktop, so "the host" is its Linux VM. The user namespace is the
  initial one (`4026531837`); the others are new.
- `container-runtimes.svg`: the dockerd → containerd → `containerd-shim-runc-v2`
  chain and "the container process is a child of the shim, runc has exited"
  come from `ps -o pid,ppid,args` on Docker 29.8 (`docker info`: default
  runtime runc).
- `image-layers.svg` sizes come from building the deck's Dockerfile
  (`docker build --platform linux/amd64`) and reading the uncompressed layer
  tars from `docker save`. `EXPOSE` and `ENTRYPOINT` produced no layer. If the
  Dockerfile changes, build it again and redraw.
- The rest (hypervisor types, ring diagrams, virtio, QEMU threads) is textbook
  material with no command to run; dates are VMware Workstation 1999, Xen 2003,
  Intel VT-x 2005, AMD-V 2006.
- Removed: `overview-vm-1.png`, `overview-vm-2.png`, `overview-container.png`
  and `image-layers.png` (screenshots with no source). `xaas.png` and
  `docker-growth.png` are still the old images.
